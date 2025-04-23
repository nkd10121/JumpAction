#include "SceneClear.h"
#include "SceneTitle.h"
#include "DxLib.h"

namespace
{
	constexpr int kFrame = 60;
}

SceneClear::SceneClear() :
	m_angle(0),
	m_buttonScale(0)
{

}

SceneClear::~SceneClear()
{
	//ハンドルの削除
	MV1DeleteModel(m_modelHandle);
}

void SceneClear::Init()
{
	m_graphManager->Load("ClearText", "data/SpringBreakGame_UI_Clear.png");
	m_graphManager->Load("ToTitleText", "data/SpringBreakGame_UI_ToTitle.png");
	m_graphManager->Load("Clear", "data/Clear.png");

	m_soundManager->Load("Clear", "data/SE/クリア.mp3", false);

	//3Dモデルの読み込み
	m_modelHandle = MV1LoadModel("data/model/Dragon.mv1");

	// ３Ｄモデルのスケールを1.8倍する
	MV1SetScale(m_modelHandle, VGet(4.0f, 4.0f, 4.0f));

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, VGet(2.0f, 1.0f, -8.0f));

	// ３ＤモデルのY軸の回転値を-45度にセットする
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, -30.0f * DX_PI_F / 180.0f, 0.0f));

	m_soundManager->StopBGM("BGM");
	m_soundManager->PlaySE("Clear");

}

std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	m_angle += DX_TWO_PI_F / kFrame;
	m_buttonScale = sinf(m_angle) * 0.04f;

	if (input.IsTriggered("OK"))
	{
		m_soundManager->PlaySE("OK");
		//SceneTitleに切り替え
		//SceneTitleのメモリを確保してそのポインタを返す
		return std::make_shared<SceneTitle>();
	}



	return shared_from_this();	//自身のshared_ptrを返す
}

void SceneClear::Draw()
{
	DrawRotaGraph(640, 360, 1.0f, 0.0f, m_graphManager->GetHandle("Clear"), true);

	//プレイヤー描画
	MV1DrawModel(m_modelHandle);

	DrawRotaGraph(640,180,1.0f,0.0f, m_graphManager->GetHandle("ClearText"), true);
	DrawRotaGraph(640,520,1.0f + m_buttonScale,0.0f, m_graphManager->GetHandle("SelectionCursol"),true);
	DrawRotaGraph(640,520,0.4f,0.0f, m_graphManager->GetHandle("ToTitleText"),true);


#ifdef _DEBUG
	DrawString(0, 0, "SceneClear", 0xffffff);
#endif
}

void SceneClear::End()
{
}
