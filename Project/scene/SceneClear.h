#pragma once
#include "SceneBase.h"
class SceneClear : public SceneBase
{
public:
	SceneClear();
	virtual ~SceneClear();

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
	float m_angle;			//�{�^���̓����p
	float m_buttonScale;	//�{�^���̊g�嗦

	int m_modelHandle;		//�v���C���[�̃n���h��
};