#include "Enemy.h"
#include "Camera.h"
#include "DxLib.h"

namespace
{
	constexpr float kHitBoxOffsetX = 1.0f;
	constexpr float kHitBoxOffsetY = 1.0f;
}


Enemy::Enemy() :
	m_isExist(false)
{
	m_handle = MV1LoadModel("data/model/obstacle.mv1");
	tempHandle = LoadGraph("data/Frame.png");
	// ３ＤモデルのY軸の回転値を９０度にセットする
	MV1SetRotationXYZ(m_handle, VGet(-90.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	MV1SetScale(m_handle, VGet(1.6f,1.6f,1.6f));
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_handle);
}

void Enemy::Init(VECTOR pos)
{
	m_isExist = true;
	m_pos = pos;
}

void Enemy::Update(Camera& camera)
{
	if (!m_isExist)
	{
		return;
	}

	// ３Dモデルのポジション設定
	MV1SetPosition(m_handle, m_pos);

	//当たり判定の座標を更新
	//m_col.SetBox(m_pos.x - kHitBoxOffsetX, m_pos.y + kHitBoxOffsetY, m_pos.x + kHitBoxOffsetX, m_pos.y);
	m_col.SetSquare(m_pos,kHitBoxOffsetX, kHitBoxOffsetY);

	if (camera.GetLeftEnd() - 2.0f > m_pos.x)
	{
		m_isExist = false;
	}
}

void Enemy::Draw()const
{
	if (!m_isExist)
	{
		return;
	}

	//描画
	MV1DrawModel(m_handle);

#ifdef _DEBUG
	//当たり判定のデバッグ表示
	DrawModiBillboard3D(m_pos,
		-kHitBoxOffsetX, kHitBoxOffsetY,
		kHitBoxOffsetX, kHitBoxOffsetY,
		kHitBoxOffsetX, -kHitBoxOffsetY,
		-kHitBoxOffsetX, -kHitBoxOffsetY,
		tempHandle, TRUE);
#endif
	m_col.DrawCollision(m_pos);
}
