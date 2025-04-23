#pragma once
#include "SceneBase.h"
class SceneGameover :
    public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover();

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
	int m_textPosY[2];

	int m_selectButtonPos;
	int m_noSelectButtonPos;

	float m_angle;
	float m_buttonScale;
};

