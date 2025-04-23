#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);

	pos = VGet(0, 0, 0);

	SetLightDirection(VGet(-20.0f, -20.0f, 24.0f));

}

Camera::~Camera()
{
}

void Camera::Update(const std::shared_ptr<Player> player)
{
#if !USE_LERP_CAMERA
	// z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
	pos = VGet(player->GetPos().x + 8.0f, 8.0f, -20.0f);
#else
	// lerpを使用して実装.
	// lerp(VECTOR a, VECTOR b, float t)は
	// answer = a + ((b-a) * t)
	VECTOR aimPos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f);
	VECTOR posToAim = VSub(aimPos, m_pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	m_pos = VAdd(m_pos, scaledPosToAim);
#endif

	pos.x += 0.2f;

	VECTOR target = VGet(player->GetPos().x + 8.0f, /*player->GetPos().y + */8.0f, player->GetPos().z);
	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(pos, target);

#ifdef DEBUG
	//画面端探し
	DrawLine3D(VGet(pos.x - 20.9f, -3.6f, 0.0f), VGet(pos.x - 20.9f, 19.6f, 0.0f), 0xff0000);
	DrawLine3D(VGet(pos.x + 20.1f, -3.6f, 0.0f), VGet(pos.x + 20.1f, 19.6f, 0.0f), 0xff0000);
#endif // DEBUG

}
