#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneGame.h"

enum ButtonType : int
{
	Select,
	NoSelect
};

namespace
{
	constexpr int kButtonPosY[2] = {460,600};
	constexpr int kFrame = 60;
}

SceneTitle::SceneTitle() :
	m_angle(0),
	m_buttonScale(0)
{

}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_graphManager->Load("Rogo", "data/SpringBreakGame_UI_Title.png");
	m_graphManager->Load("Start", "data/SpringBreakGame_UI_Start.png");
	m_graphManager->Load("Quit", "data/SpringBreakGame_UI_Quit.png");
	m_graphManager->Load("SelectionCursol", "data/Hover@2x.png");
	m_graphManager->Load("NotSelectionCursol", "data/Default@2x.png");

	m_graphManager->Load("BG1", "data/BackGround/Background_1.png");
	m_graphManager->Load("BG2", "data/BackGround/Background_2.png");

	m_soundManager->Load("Cursol","data/SE/‘I‘ð6.mp3",false);
	m_soundManager->Load("OK","data/SE/Œˆ’è13.mp3",false);

	m_soundManager->Load("BGM","data/BGM/BGM.mp3",true);

	m_selectButtonPos = kButtonPosY[Select];
	m_noSelectButtonPos = kButtonPosY[NoSelect];

	m_soundManager->ChangeBGMVolume(2);
	m_soundManager->PlayBGM("BGM", true);

}

std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	if (!m_soundManager->isPlayingSound("BGM"))
	{
		m_soundManager->PlayBGM("BGM", true);
	}

	//—\‘ªü‚Ì“_‚ð‰ñ“]‚³‚¹‚é‚½‚ß‚Éangle‚ðXV
	m_angle += DX_TWO_PI_F / kFrame;
	m_buttonScale = sinf(m_angle) * 0.04f;

	if (m_selectButtonPos == kButtonPosY[Select])
	{
		if (input.IsTriggered("DOWN"))
		{
			m_soundManager->PlaySE("Cursol");
			m_selectButtonPos = kButtonPosY[NoSelect];
			m_noSelectButtonPos = kButtonPosY[Select];
		}

		if (input.IsTriggered("OK"))
		{
			m_soundManager->PlaySE("OK");
			return  std::make_shared<SceneGame>();
		}
	}

	if (m_selectButtonPos == kButtonPosY[NoSelect])
	{
		if (input.IsTriggered("UP"))
		{
			m_soundManager->PlaySE("Cursol");
			m_selectButtonPos = kButtonPosY[Select];
			m_noSelectButtonPos = kButtonPosY[NoSelect];
		}

		if (input.IsTriggered("OK"))
		{
			return nullptr;
		}
	}

	return shared_from_this();
}

void SceneTitle::Draw()
{
	DrawRotaGraph(640,360,1.0f,0.0f, m_graphManager->GetHandle("BG2"), true);
	DrawRotaGraph(640,360,1.0f,0.0f, m_graphManager->GetHandle("BG1"), true);

	DrawRotaGraph(640,180,1.0f,0.0f, m_graphManager->GetHandle("Rogo"), true);

	DrawRotaGraph(640, m_selectButtonPos,0.8f + m_buttonScale,0.0f, m_graphManager->GetHandle("SelectionCursol"),true);
	DrawRotaGraph(640, m_noSelectButtonPos,0.8f,0.0f, m_graphManager->GetHandle("NotSelectionCursol"),true);

	DrawRotaGraph(640,460,0.4f,0.0f, m_graphManager->GetHandle("Start"),true);
	DrawRotaGraph(640,600,0.4f,0.0f, m_graphManager->GetHandle("Quit"),true);

#ifdef _DEBUG
	DrawString(0, 0, "SceneTitle", 0xffffff);
#endif
}

void SceneTitle::End()
{
}
