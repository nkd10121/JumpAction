#pragma once
#include "Collision.h"

class Camera;

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Init(VECTOR pos);
	void Update(Camera& camera);
	void Draw()const;

	Collision GetCol()const { return m_col;};

	bool IsExist() { return m_isExist; };

private:
	int m_isExist;

	int m_handle;
	VECTOR m_pos;
	Collision m_col;

	int tempHandle;
};