#pragma once
#include "SceneBase.h"

class SceneTitle :
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

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
	int m_selectButtonPos;
	int m_noSelectButtonPos;

	float m_angle;
	float m_buttonScale;

};