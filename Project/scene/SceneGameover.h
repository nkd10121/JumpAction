#pragma once
#include "SceneBase.h"
class SceneGameover :
    public SceneBase
{
public:
	SceneGameover();
	virtual ~SceneGameover();

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
	int m_textPosY[2];

	int m_selectButtonPos;
	int m_noSelectButtonPos;

	float m_angle;
	float m_buttonScale;
};

