#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
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
	// z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
	pos = VGet(player->GetPos().x + 8.0f, 8.0f, -20.0f);
#else
	// lerp���g�p���Ď���.
	// lerp(VECTOR a, VECTOR b, float t)��
	// answer = a + ((b-a) * t)
	VECTOR aimPos = VGet(0, player.GetPos().y + 20.0f, player.GetPos().z - 30.0f);
	VECTOR posToAim = VSub(aimPos, m_pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	m_pos = VAdd(m_pos, scaledPosToAim);
#endif

	pos.x += 0.2f;

	VECTOR target = VGet(player->GetPos().x + 8.0f, /*player->GetPos().y + */8.0f, player->GetPos().z);
	// �J�����Ɉʒu�𔽉f.
	SetCameraPositionAndTarget_UpVecY(pos, target);

#ifdef DEBUG
	//��ʒ[�T��
	DrawLine3D(VGet(pos.x - 20.9f, -3.6f, 0.0f), VGet(pos.x - 20.9f, 19.6f, 0.0f), 0xff0000);
	DrawLine3D(VGet(pos.x + 20.1f, -3.6f, 0.0f), VGet(pos.x + 20.1f, 19.6f, 0.0f), 0xff0000);
#endif // DEBUG

}
