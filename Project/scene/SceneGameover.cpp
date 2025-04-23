#include "SceneGameover.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "DxLib.h"

enum ItemName : int
{
	Retry,
	ToTitle
};

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

SceneGameover::SceneGameover() :
	m_angle(0),
	m_buttonScale(0)
{
	m_textPosY[Retry] = 460;
	m_textPosY[ToTitle] = 600;
}

SceneGameover::~SceneGameover()
{
}

void SceneGameover::Init()
{
	m_graphManager->Load("GameoverText", "data/SpringBreakGame_UI_Gameover.png");
	m_graphManager->Load("RetryText", "data/SpringBreakGame_UI_Retry.png");
	m_graphManager->Load("ToTitleText", "data/SpringBreakGame_UI_ToTitle.png");
	m_graphManager->Load("Gameover", "data/Gameover.png");

	m_soundManager->Load("Gameover", "data/SE/‚µ‚Á‚Ï‚¢.mp3", false);

	m_selectButtonPos = kButtonPosY[Select];
	m_noSelectButtonPos = kButtonPosY[NoSelect];

	m_soundManager->StopBGM("BGM");
	m_soundManager->PlaySE("Gameover");
}

std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
{
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
			m_soundManager->PlaySE("OK");
			return std::make_shared<SceneTitle>();
		}
	}

	return shared_from_this();	//Ž©g‚Ìshared_ptr‚ð•Ô‚·
}

void SceneGameover::Draw()
{
	DrawRotaGraph(640, 360, 1.0f, 0.0f, m_graphManager->GetHandle("Gameover"), true);

	DrawRotaGraph(640, 180, 1.0f, 0.0f, m_graphManager->GetHandle("GameoverText"), true);

	DrawRotaGraph(640, m_selectButtonPos, 0.88f + m_buttonScale, 0.0f, m_graphManager->GetHandle("SelectionCursol"), true);
	DrawRotaGraph(640, m_noSelectButtonPos, 0.88f, 0.0f, m_graphManager->GetHandle("NotSelectionCursol"), true);

	DrawRotaGraph(640, m_textPosY[Retry], 0.4f, 0.0f, m_graphManager->GetHandle("RetryText"), true);
	DrawRotaGraph(640, m_textPosY[ToTitle], 0.4f, 0.0f, m_graphManager->GetHandle("ToTitleText"), true);
#ifdef _DEBUG
	DrawString(0, 0, "SceneGameover", 0xffffff);
#endif
}

void SceneGameover::End()
{
}
