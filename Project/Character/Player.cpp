#include "Player.h"
#include "Input.h"

namespace
{
	constexpr float kMoveSpeed = 0.08f;			//�ړ����x
	constexpr float kPlayerBasePosY = -0.4f;	//�v���C���[�̊�{y���W
	constexpr float kInitVelocity = 0.4f;		//�W�����v�̏���
	constexpr float kGravity = 0.008f;			//�d��

	constexpr float kHitBoxOffsetX = 0.8f;		//�����蔻��̍���
	constexpr float kHitBoxOffsetY = 1.8f;		//�����蔻��̍���
}

Player::Player() :
	m_isStart(false),
	m_pos(VGet(0.0f, kPlayerBasePosY, 0.0f)),
	m_isJump(false),
	m_isFirstJump(false),
	m_isSecondJump(false),
	m_jumpKeyPushFrame(0),
	m_moveForce(VGet(kMoveSpeed, 0.0f, 0.0f)),
	m_animTime(0),
	m_animTotalTime(0),
	m_attachAnimHandle(0)
{

}

Player::~Player()
{
	//�n���h���̍폜
	MV1DeleteModel(m_handle);
}

void Player::Init()
{

	//3D���f���̓ǂݍ���
	//m_handle = MV1LoadModel("data/model/character_dog.mv1");
	m_handle = MV1LoadModel("data/model/Dragon.mv1");

	// �R�c���f���̃X�P�[����1.8�{����
	MV1SetScale(m_handle, VGet(0.012f, 0.012f, 0.012f));
	//MV1SetScale(m_handle, VGet(1.8f, 1.8f, 1.8f));

	// �R�c���f����Y���̉�]�l��-45�x�ɃZ�b�g����
	MV1SetRotationXYZ(m_handle, VGet(0.0f, -60.0f * DX_PI_F / 180.0f, 0.0f));

	/*�A�j���[�V�����̐ݒ�*/
	//m_attachAnimHandle = MV1AttachAnim(m_handle, 1);
	m_attachAnimHandle = MV1AttachAnim(m_handle,3, -1, FALSE);
	m_animTotalTime = MV1GetAnimTotalTime(m_handle, m_attachAnimHandle);

}

void Player::Update(Input& input)
{
	if (!m_isStart)
	{
		return;
	}

#ifdef _DEBUG
	// �v���C���[����.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �E�������Ă�����E�ɐi��
	if (key & PAD_INPUT_RIGHT) 
	{
		m_pos.x += kMoveSpeed;
	}

	// ���������Ă����獶�ɐi��
	if (key & PAD_INPUT_LEFT)
	{
		m_pos.x -= kMoveSpeed;
	}
#endif

	MV1SetAttachAnimTime(m_handle, m_attachAnimHandle, m_animTime);
	m_animTime += 1.0f;
	if (m_animTime >= m_animTotalTime) 
	{
		m_animTime = 0.0f;
	}

	/*�W�����v�֌W*/
	if (input.IsTriggered("JUMP"))
	{
		m_jumpKeyPushFrame++;

		//���������Ă���񂵂��Ă΂�Ȃ��悤��
		if (m_jumpKeyPushFrame == 1)
		{
			//���ڂ̃W�����v�t���O��false(�W�����v���Ă��Ȃ�)�̂Ƃ�
			if (!m_isFirstJump)
			{
				//������^����
				m_moveForce.y = kInitVelocity;
				//���ڂ̃W�����v�t���O��true(�W�����v���Ă���)�ɂ���
				m_isFirstJump = true;
			}
			//���ڂ̃W�����v�t���O��true����
			//���ڂ̃W�����v�t���O��false�̂Ƃ�
			else if (!m_isSecondJump)
			{
				//������������x�^����
				m_moveForce.y = kInitVelocity;
				//���ڂ̃W�����v�t���O��true�ɂ���
				m_isSecondJump = true;
			}
		}
	}
	//�W�����v�L�[�������Ă��Ȃ��Ƃ�
	else
	{
		//�����Ă��鎞�Ԃ����Z�b�g����
		m_jumpKeyPushFrame = 0;
	}


	if (m_moveForce.y == kInitVelocity)
	{
		m_isJump = true;
	}
	else
	{
		m_isJump = false;
	}

	//�W�����v�t���O��true�̊�
	if (m_isFirstJump)
	{
		//�W�����v�֐����Ă�
		Jump();
	}

	//�n�ʂɂ������̏���
	if(m_pos.y < kPlayerBasePosY)
	{
		//�W�����v�֌W�̕ϐ������Z�b�g����
		m_isFirstJump = false;
		m_isSecondJump = false;
		m_moveForce.y = 0.0f;
		m_pos.y = kPlayerBasePosY;
	}

	//���W�̍X�V
	m_pos = VAdd(m_pos,m_moveForce);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_handle, m_pos);

	//�����蔻��̍��W���X�V
	m_pHitBox.SetBox(m_pos.x - kHitBoxOffsetX / 2, m_pos.y + kHitBoxOffsetY, m_pos.x + kHitBoxOffsetX, m_pos.y + kHitBoxOffsetY / 4);
}

void Player::Draw()const
{
	//�v���C���[�`��
	MV1DrawModel(m_handle);

#ifdef _DEBUG
	//�����蔻��̃f�o�b�O�\��
	m_pHitBox.DrawCollision(m_pos);
#endif
}

void Player::Start()
{
	m_isStart = true;
}

void Player::Jump()
{
	//Y�����̑��x�ɉ����x��������
	m_moveForce.y -= kGravity;

	m_moveForce.y *= 0.99f;
}