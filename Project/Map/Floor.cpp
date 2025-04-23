#include "Floor.h"
#include "Camera.h"

Floor::Floor():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	//3D���f���̓ǂݍ���
	m_handle = MV1LoadModel("data/model/tileHigh_forest.mv1");
	// �R�c���f���̃X�P�[����1.8�{����
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
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_handle, m_pos);

	//��ʊO�ɏo���Ƃ���x���W���ړ�������
	//�������[�v����悤�ɂ���
	if (camera.GetLeftEnd() - 4.0f > m_pos.x)
	{
		m_pos.x += 49.0f;
	}
}

void Floor::Draw()
{
	//�`��
	MV1DrawModel(m_handle);
}

void Floor::SetPos(VECTOR pos)
{
	m_pos = pos;
}
