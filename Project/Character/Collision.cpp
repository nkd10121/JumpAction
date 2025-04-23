#include "Collision.h"
#include <cassert>

Collision::Collision():
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{
	m_handle = LoadGraph("data/Frame.png");
}

Collision::~Collision()
{
	DeleteGraph(m_handle);
}

void Collision::SetBox(float left, float top, float right, float bottom)
{
	m_left = left;
	m_top = top;
	m_right = right;
	m_bottom = bottom;
}

void Collision::SetSquare(VECTOR pos,float width, float height)
{
	m_left = pos.x - width;
	m_right = pos.x + width;
	m_top = pos.y + height;
	m_bottom = pos.y - height;
}

void Collision::DrawCollision(const VECTOR& pos)const
{
	//�����蔻��̃f�o�b�O�\��
	DrawModiBillboard3D(pos,
		m_left, m_top,
		m_right, m_top,
		m_right, m_bottom,
		m_left, m_bottom,
		m_handle, TRUE);

	DrawRotaGraph(pos.x, pos.y, 1.4f, 0.0f, m_handle, true);
}

bool Collision::isCollision(const Collision& col)
{
	//��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > col.m_right)	return false;
	if (m_top < col.m_bottom)	return false;
	if (m_right < col.m_left)	return false;
	if (m_bottom > col.m_top)	return false;

	//������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
