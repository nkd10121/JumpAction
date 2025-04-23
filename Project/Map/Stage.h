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

	// マップチップのサイズ
	float	ChipSize;
	int	ChipPixelSize;
	static const int	StageDataColNum = 16;		// マップ行
	static const int	StageDataRowNum = 20;		// マップ列

	// マップを実際に表示するためのWorldSpriteクラスたち
	std::vector<WorldSprite*> sprites;	// StageDataColNum＊StageDataRowNum個のvectorコンテナ（≒一次元配列）

	// マップチップの元画像ハンドル
	int chipGraph;
};

