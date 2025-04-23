#pragma once
#include "DxLib.h"
#include "Camera.h"
#include <memory>
#include <vector>

class Floor;
class WorldSprite;

class Stage
{
public:
	Stage();
	virtual ~Stage();

	void Init(int handle1, int handle2, int handle3);
	void Update(Camera& camera);
	void Draw();



private:
	std::vector<std::shared_ptr<Floor>> m_pFloor;

	int m_bgHandle1;
	int m_bgHandle2;

	float m_bgPosX1;
	float m_bgPosX1_2;
	float m_bgPosX2;
	float m_bgPosX2_2;

	int m_moveCount;

	bool m_isFirst;
	float m_cameraPosX;

	// �}�b�v�`�b�v�̃T�C�Y
	float	ChipSize;
	int	ChipPixelSize;
	static const int	StageDataColNum = 16;		// �}�b�v�s
	static const int	StageDataRowNum = 20;		// �}�b�v��

	// �}�b�v�����ۂɕ\�����邽�߂�WorldSprite�N���X����
	std::vector<WorldSprite*> sprites;	// StageDataColNum��StageDataRowNum��vector�R���e�i�i���ꎟ���z��j

	// �}�b�v�`�b�v�̌��摜�n���h��
	int chipGraph;
};

