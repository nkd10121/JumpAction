#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"

SceneManager::SceneManager() :
	m_pScene(nullptr),
	m_isGameEnd(false)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	m_graphManager = make_shared<GraphManager>();
	m_soundManager = make_shared<SoundManager>();
	//�ŏ��̃V�[���̃��������m�ۂ���
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Assign(m_graphManager, m_soundManager);
	m_pScene->Init();
}

void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);
	
	if (pNext == nullptr)
	{
		//Update���Ԃ����V�����V�[���ɑJ�ڂ���
		//���ݏ������̃V�[���̏I������
		m_isGameEnd = true;
		return;
	}
	
	if (pNext != m_pScene)
	{
		//Update���Ԃ����V�����V�[���ɑJ�ڂ���
		//���ݏ������̃V�[���̏I������
		m_pScene->End();

		//Update���Ԃ����V�����V�[���̊J�n�������s��
		m_pScene = pNext;
		m_pScene->Assign(m_graphManager, m_soundManager);
		m_pScene->Init();
	}


}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

void SceneManager::End()
{
	m_pScene->End();
}
