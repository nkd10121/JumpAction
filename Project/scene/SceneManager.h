#pragma once
#include <memory>
#include "../SoundManager.h"
#include "../GraphManager.h"

//�v���g�^�C�v�錾
class Input;
class SceneBase;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	/// �V�[���ɓ���Ƃ��̏���������
	/// </summary>
	void Init();

	/// <summary>
	/// ���t���[���s���X�V����
	/// </summary>
	void Update(Input& input);

	/// <summary>
	/// ���t���[���s���`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���𔲂���Ƃ��̏���
	/// </summary>
	void End();

	bool GetGameEndFlag() { return m_isGameEnd; };

private:
	std::shared_ptr<SceneBase> m_pScene;
	std::shared_ptr<GraphManager> m_graphManager;
	std::shared_ptr<SoundManager> m_soundManager;

	bool m_isGameEnd;
};

