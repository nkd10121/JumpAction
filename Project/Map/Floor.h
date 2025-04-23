#pragma once
#include "DxLib.h"

class Camera;

class Floor
{
public:
	Floor();
	virtual ~Floor();

	void Init();
	void Update(Camera& camera);
	void Draw();

	void SetPos(VECTOR pos);

private:
	int m_handle;
	VECTOR m_pos;
};

