#include "Stage.h"
#include "DxLib.h"
#include "Floor.h"
#include "WorldSprite.h"

namespace
{
	constexpr int kFloorNum = 18;	//床の数

	constexpr float kFloorPosX = -12.0f;	//床の初期化X座標
	constexpr float kFloorPosY = -3.2f;		//床の初期化Y座標
	constexpr float kFloorPosZ = 0.0f;		//床の初期化Z座標

	constexpr float kFloorPosXOffset = 2.72f;		//床の初期化Z座標


	constexpr int kStageDataColNum = 16;
	constexpr int kStageDataRowNum = 32;

	const int kStage1Data[kStageDataColNum][kStageDataRowNum] =
	{
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{ 52, 53, 54, 55,  0,  0, 52, 53, 54, 55,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 52, 53, 54, 55,  0,  0,  0,  0,  0,  0},
		{ 68, 69, 70, 71,  0,  0, 68, 69, 70, 71,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 68, 69, 70, 71,  0,  0,  0,  0,  0,  0},
		{ 84, 85, 86, 87,  0,  0, 84, 85, 86, 87,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 84, 85, 86, 87,  0,  0,  0,  0,  0,  0},
		{100,101,102,103,  0,  0,100,101,102,103,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,100,101,102,103,  0,  0,  0,  0,  0,  0},
		{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};

	const float kChipSize = 1.32f;
	const int kChipPixelSize = 32;
}

Stage::Stage() :
	m_bgPosX1(640.0f),
	m_bgPosX1_2(640.0f + 1278.0f),
	m_bgPosX2(640.0f),
	m_bgPosX2_2(640.0f + 1278.0f),
	m_moveCount(1),
	m_isFirst(true),
	m_cameraPosX(0)
{

	m_pFloor.resize(kFloorNum);
	for (int i = 0;i < m_pFloor.size();i++)
	{
		m_pFloor[i] = std::make_shared<Floor>();
		m_pFloor[i]->SetPos(VGet(kFloorPosX + kFloorPosXOffset * i, kFloorPosY, kFloorPosZ));
	}

}

Stage::~Stage()
{
	for (const auto& sprite : sprites)
	{
		if (sprite != nullptr)
		{
			delete sprite;
		}
	}
	sprites.clear();
}

void Stage::Init(int handle1,int handle2,int handle3)
{
	m_bgHandle1 = handle1;
	m_bgHandle2 = handle2;
	// とりあえずマップロード
	chipGraph = handle3;

	// 「データ(Stage1Data)」を元に「実際に描画する人(WorldSprite)」に情報を渡していく
	// データと実際に描画する人を分離することで
	// データを外部ファイル化したり、描画時にちょっといじったりできる
	VECTOR chipLeftTopPos = VGet(0, kStageDataColNum * kChipSize, 0);			// マップの描画開始位置（左上）
	for (int i = 0; i < kStageDataColNum; i++)
	{
		for (int j = 0; j < kStageDataRowNum; j++)
		{
			auto sprite = new WorldSprite();
			sprite->Initialize(chipGraph, kChipPixelSize, kStage1Data[i][j]);
			VECTOR chipHalfOffset = VGet(-kChipSize * 0.5f, -kChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(j * kChipSize - 11.6f, (-i - 1) * kChipSize - 0.24f, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);
			sprite->SetTransform(chipPos, kChipSize);
			sprites.push_back(sprite);
		}
	}
}

void Stage::Update(Camera& camera)
{
	if (m_cameraPosX == 0)
	{
		m_cameraPosX = camera.GetPos().x;
	}

	//床の更新処理
	for (auto& floor : m_pFloor)
	{
		floor->Update(camera);
	}

	for (auto& sprite : sprites)
	{
		auto spritePos = sprite->GetPos();
		if (spritePos.x < camera.GetLeftEnd() - 2.0f)
		{
			spritePos.x += kChipSize * kStageDataColNum * 2.2f;
			sprite->SetTransform(spritePos, kChipSize);
		}
	}

	auto temp = camera.GetPos().x - m_cameraPosX;
	m_bgPosX1 -= temp * 4;
	m_bgPosX1_2 -= temp * 4;
	m_bgPosX2 -= temp * 2;
	m_bgPosX2_2 -= temp * 2;

	if (m_bgPosX1 + 328.0f + 1278.0f / 2 < camera.GetLeftEnd())
	{
		m_moveCount++;
		m_bgPosX1 += 1278.0f * 2;
	}

	m_cameraPosX = camera.GetPos().x;

}

void Stage::Draw()
{
	DrawRotaGraph(m_bgPosX2,360,1.0f,0.0f,m_bgHandle2,true);
	DrawRotaGraph(m_bgPosX2_2,360,1.0f,0.0f,m_bgHandle2,true);
	DrawRotaGraph(m_bgPosX1,360,1.0f,0.0f,m_bgHandle1,true);
	DrawRotaGraph(m_bgPosX1_2,360,1.0f,0.0f,m_bgHandle1,true);

	// ゆくゆくはカメラを持ってきて、カメラ範囲以外表示しないように
	for (const auto& sprite : sprites)
	{
		sprite->Draw();
	}

	//床の描画処理
	for (auto& floor : m_pFloor)
	{
		floor->Draw();
	}
}
