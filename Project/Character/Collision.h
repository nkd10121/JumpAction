#pragma once
#include "DxLib.h"

class Collision
{
public:
	Collision();
	virtual ~Collision();

	/// <summary>
	/// 四角の当たり判定の設定
	/// </summary>
	/// <param name="left">左のx座標</param>
	/// <param name="top">上のy座標</param>
	/// <param name="right">右のx座標</param>
	/// <param name="bottom">下のy座標</param>
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

