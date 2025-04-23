#pragma once
#include "SceneBase.h"
#include "../Collision.h"
#include <memory>
#include <vector>
#include "DxLib.h"

class Stage;
class Player;
class Enemy;
class Camera;

class SceneGame :
    public SceneBase
{
public:
	SceneGame();
	virtual ~SceneGame();

	/// <summary>
	/// �V�[���ɓ���Ƃ��̏���������
	/// </summary>
	virtual void Init();

	/// <summary>
	/// ���t���[���s���X�V����
	/// </summary>
	virtual std::shared_ptr<SceneBase> Update(Input& input);

	/// <summary>
	/// ���t���[���s���`�揈��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �V�[���𔲂���Ƃ��̏���
	/// </summary>
	virtual void End();

private:
	bool m_isStart;
	int m_countDown;

	int m_frame;
	int m_enemyGenerateFrame;
	int m_time;
	int m_onesPlaceTimer;
	int m_tensPlaceTimer;

	void DrawTimer();

	std::shared_ptr<Player> m_pPlayer;
	Collision m_playerCol;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::shared_ptr<Stage> m_stage;
	std::shared_ptr<Camera> m_pCamera;

	void CreateObstruct(VECTOR pos);

	void ObstructGenerator(int frame);
};

