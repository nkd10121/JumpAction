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
	/// シーンに入るときの初期化処理
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 毎フレーム行う更新処理
	/// </summary>
	//virtual void Update() = 0;
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;	//シーンを変更する場合は遷移先のシーンのポインタ
	//シーンを変更しない場合は自身のポインタ

	/// <summary>
	/// 毎フレーム行う描画処理
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// シーンを抜けるときの処理
	/// </summary>
	virtual void End() = 0;

protected:
	//void MyLoadGraph(std::string name, std::string path) { m_graphManager->Load(name, path); };
	std::shared_ptr<GraphManager> m_graphManager;
	std::shared_ptr<SoundManager> m_soundManager;

private:
};

