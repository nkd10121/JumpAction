#pragma once
#include "SceneBase.h"
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

	/// <summary>
	/// シーンに入るときの初期化処理
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 毎フレーム行う更新処理
	/// </summary>
	virtual std::shared_ptr<SceneBase> Update(Input& input);

	/// <summary>
	/// 毎フレーム行う描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// シーンを抜けるときの処理
	/// </summary>
	virtual void End();

private:
	float m_angle;			//ボタンの動き用
	float m_buttonScale;	//ボタンの拡大率

	int m_modelHandle;		//プレイヤーのハンドル
};