#pragma once
#include "DxLib.h"
#include "Collision.h"

class Input;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update(Input& input);
	void Draw()const;

	void Start();

	const VECTOR GetPos()const { return m_pos; }
	const bool IsJump()const { return m_isJump; }
	Collision GetCol()const { return m_pHitBox; };

private:
	bool m_isStart;
	VECTOR m_pos;
	VECTOR m_move;
	Collision m_pHitBox;
	int m_handle;

	int m_tempHandle;

	bool m_isJump;
	bool m_isFirstJump;
	bool m_isSecondJump;
	int m_jumpKeyPushFrame;
	VECTOR m_moveForce;
	void Jump();

	/*アニメーション関係*/
	float m_animTime;
	float m_animTotalTime;
	int m_attachAnimHandle;
};

