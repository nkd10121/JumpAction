#pragma once
#include <memory>
#include "../SoundManager.h"
#include "../GraphManager.h"

//プロトタイプ宣言
class Input;
class SceneBase;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	/// <summary>
	/// シーンに入るときの初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 毎フレーム行う更新処理
	/// </summary>
	void Update(Input& input);

	/// <summary>
	/// 毎フレーム行う描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンを抜けるときの処理
	/// </summary>
	void End();

	bool GetGameEndFlag() { return m_isGameEnd; };

private:
	std::shared_ptr<SceneBase> m_pScene;
	std::shared_ptr<GraphManager> m_graphManager;
	std::shared_ptr<SoundManager> m_soundManager;

	bool m_isGameEnd;
};

