#include "Floor.h"
#include "Camera.h"

Floor::Floor():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	//3Dモデルの読み込み
	m_handle = MV1LoadModel("data/model/tileHigh_forest.mv1");
	// ３Ｄモデルのスケールを1.8倍する
	MV1SetScale(m_handle, VGet(1.4f, 1.4f, 1.4f));
}

Floor::~Floor()
{
	MV1DeleteModel(m_handle);
}

void Floor::Init()
{
}

void Floor::Update(Camera& camera)
{
	// ３Dモデルのポジション設定
	MV1SetPosition(m_handle, m_pos);

	//画面外に出たときにx座標を移動させて
	//床がループするようにする
	if (camera.GetLeftEnd() - 4.0f > m_pos.x)
	{
		m_pos.x += 49.0f;
	}
}

void Floor::Draw()
{
	//描画
	MV1DrawModel(m_handle);
}

void Floor::SetPos(VECTOR pos)
{
	m_pos = pos;
}
