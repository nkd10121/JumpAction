#pragma once
#include "DxLib.h"

class Collision
{
public:
	Collision();
	virtual ~Collision();

	/// <summary>
	/// �l�p�̓����蔻��̐ݒ�
	/// </summary>
	/// <param name="left">����x���W</param>
	/// <param name="top">���y���W</param>
	/// <param name="right">�E��x���W</param>
	/// <param name="bottom">����y���W</param>
	void SetBox(float left, float top, float right, float bottom);

	void SetSquare(VECTOR pos, float width,float height);

	void DrawCollision(const VECTOR& pos)const;

	bool isCollision(const Collision& col);

private:
	int m_handle;

	float m_left;
	float m_top;
	float m_right;
	float m_bottom;
};

