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
	//最初のシーンのメモリを確保する
	m_pScene = std::make_shared<SceneTitle>();
	m_pScene->Assign(m_graphManager, m_soundManager);
	m_pScene->Init();
}

void SceneManager::Update(Input& input)
{
	std::shared_ptr<SceneBase> pNext = m_pScene->Update(input);
	
	if (pNext == nullptr)
	{
		//Updateが返した新しいシーンに遷移する
		//現在処理中のシーンの終了処理
		m_isGameEnd = true;
		return;
	}
	
	if (pNext != m_pScene)
	{
		//Updateが返した新しいシーンに遷移する
		//現在処理中のシーンの終了処理
		m_pScene->End();

		//Updateが返した新しいシーンの開始処理を行う
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
