#pragma once
#include "DxLib.h"
#include <memory>

class Player;

class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.

	void Update(const std::shared_ptr<Player> player);	// �X�V.

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }

	const float GetLeftEnd()const { return pos.x - 21.0f; }
	const float GetRightEnd()const { return pos.x + 20.0f; }
private:
	VECTOR	pos;			// �|�W�V����.

};
