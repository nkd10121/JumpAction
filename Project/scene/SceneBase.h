#pragma once
#include "../SoundManager.h"
#include "../GraphManager.h"
#include <memory>

#include "../Input.h"

class SceneBase : public std::enable_shared_from_this<SceneBase>
{
public:
	SceneBase() {};
	virtual ~SceneBase() {};

	void Assign(std::shared_ptr<GraphManager> graphManager, std::shared_ptr<SoundManager> soundManager)
	{
		m_graphManager = graphManager;
		m_soundManager = soundManager;
	};

	/// <summary>
	/// �V�[���ɓ���Ƃ��̏���������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// ���t���[���s���X�V����
	/// </summary>
	//virtual void Update() = 0;
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;	//�V�[����ύX����ꍇ�͑J�ڐ�̃V�[���̃|�C���^
	//�V�[����ύX���Ȃ��ꍇ�͎��g�̃|�C���^

	/// <summary>
	/// ���t���[���s���`�揈��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �V�[���𔲂���Ƃ��̏���
	/// </summary>
	virtual void End() = 0;

protected:
	//void MyLoadGraph(std::string name, std::string path) { m_graphManager->Load(name, path); };
	std::shared_ptr<GraphManager> m_graphManager;
	std::shared_ptr<SoundManager> m_soundManager;

private:
};

