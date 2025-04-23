#include "SceneGame.h"
#include "SceneGameover.h"
#include "SceneClear.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Camera.h"

namespace
{
	constexpr float kUpperPosY = 14.0f;
	constexpr float kMiddlePosY = 8.0f;
	constexpr float kLowerPosY = 2.0f;
}

SceneGame::SceneGame() :
	m_isStart(false),
	m_countDown(3),
	m_frame(0),
	m_enemyGenerateFrame(0),
	m_time(0),
	m_onesPlaceTimer(0),
	m_tensPlaceTimer(0)
{

}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_graphManager->Load("TimerText", "data/SpringBreakGame_UI_TimerText.png");
	m_graphManager->Load("Map", "data/BackGround/map.png");

	m_graphManager->Load("0", "data/Number/SpringBreakGame_UI_0.png");
	m_graphManager->Load("1", "data/Number/SpringBreakGame_UI_1.png");
	m_graphManager->Load("2", "data/Number/SpringBreakGame_UI_2.png");
	m_graphManager->Load("3", "data/Number/SpringBreakGame_UI_3.png");
	m_graphManager->Load("4", "data/Number/SpringBreakGame_UI_4.png");
	m_graphManager->Load("5", "data/Number/SpringBreakGame_UI_5.png");
	m_graphManager->Load("6", "data/Number/SpringBreakGame_UI_6.png");
	m_graphManager->Load("7", "data/Number/SpringBreakGame_UI_7.png");
	m_graphManager->Load("8", "data/Number/SpringBreakGame_UI_8.png");
	m_graphManager->Load("9", "data/Number/SpringBreakGame_UI_9.png");

	m_soundManager->Load("Jump", "data/SE/ジャンプ.mp3",false);
	m_soundManager->Load("CountDown", "data/SE/カウントダウン.mp4",true);
	m_soundManager->Load("Start", "data/SE/スタート.mp3",true);

	auto tempHandle1 = m_graphManager->GetHandle("BG1");
	auto tempHandle2 = m_graphManager->GetHandle("BG2");
	auto tempHandle3 = m_graphManager->GetHandle("Map");

	m_stage = std::make_shared<Stage>();
	m_stage->Init(tempHandle1, tempHandle2, tempHandle3);

	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->Init();

	m_pCamera = std::make_shared<Camera>();

	m_pEnemy.resize(20);

	//VECTOR temp = VGet(12.0f, 2.0f, 0.0f);
	//CreateObstruct(temp);

	//temp = VGet(12.0f, 8.0f, 0.0f);
	//CreateObstruct(temp);

	//temp = VGet(12.0f, 14.0f, 0.0f);
	//CreateObstruct(temp);


	m_soundManager->PlayBGM("CountDown", true);
}

std::shared_ptr<SceneBase> SceneGame::Update(Input& input)
{
	if (!m_soundManager->isPlayingSound("BGM"))
	{
		m_soundManager->PlayBGM("BGM", true);
	}

	m_frame++;

	if (!m_isStart)
	{
		if (m_frame % 60 == 0)
		{
			m_countDown -= 1;
		}

		if (m_countDown == -1)
		{
			m_isStart = true;
			m_pPlayer->Start();
			m_frame = 0;
		}
		else if (m_countDown == 0)
		{
			m_soundManager->PlayBGM("Start",true);
		}
	}
	else
	{
		ObstructGenerator(m_enemyGenerateFrame);
		m_enemyGenerateFrame++;

		m_onesPlaceTimer = m_frame / 60;
		if (m_onesPlaceTimer == 10)
		{
			m_frame = 0;
			m_onesPlaceTimer = 0;
			m_tensPlaceTimer++;
		}
	}

	//プレイヤーの更新処理
	m_pPlayer->Update(input);

	if (m_pPlayer->IsJump())
	{
		m_soundManager->PlaySE("Jump");
	}

	m_playerCol = m_pPlayer->GetCol();

	m_pCamera->Update(m_pPlayer);
	m_stage->Update(*m_pCamera);


	for (auto& obstruct : m_pEnemy)
	{
		if (obstruct)
		{
			obstruct->Update(*m_pCamera);

			if (!obstruct->IsExist())
			{
				//メモリを解放する
				obstruct = nullptr;
			}
			else
			{
				Collision obstructCol = obstruct->GetCol();
				if (m_playerCol.isCollision(obstructCol))
				{
					//SceneGameに切り替え
					//SceneGameのメモリを確保してそのポインタを返す
					return std::make_shared<SceneGameover>();
				}
			}
		}
	}

	////不要になった敵をここで削除処理する
	//auto lIt = remove_if(m_pEnemy.begin(), m_pEnemy.end(), [](auto& v) {
	//	return v == nullptr;
	//	});
	//m_pEnemy.erase(lIt, m_pEnemy.end());




#ifdef _DEBUG
	if (input.IsTriggered("OK"))
	{
		//SceneGameに切り替え
		//SceneGameのメモリを確保してそのポインタを返す
		return std::make_shared<SceneClear>();
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
	{
		//SceneGameに切り替え
		//SceneGameのメモリを確保してそのポインタを返す
		return std::make_shared<SceneClear>();
	}
#endif

	//経過時間で終了
	if (m_enemyGenerateFrame > 60 * 90)
	{
		//SceneGameに切り替え
		//SceneGameのメモリを確保してそのポインタを返す
		return std::make_shared<SceneClear>();
	}

	return shared_from_this();	//自身のshared_ptrを返す
}

void SceneGame::Draw()
{
	m_stage->Draw();

	m_pPlayer->Draw();
	//m_pEnemy->Draw();
	for (auto& obstruct : m_pEnemy)
	{
		if (obstruct)
		{
			obstruct->Draw();
		}
	}

	DrawTimer();


#ifdef _DEBUG
	DrawString(0, 0, "SceneGame", 0xffffff);
	DrawFormatString(0, 16, 0xffffff, "%d", m_countDown);
	DrawFormatString(0, 32, 0xff0000, "%d", m_frame);
	DrawFormatString(680, 60, 0xffffff, "%d", m_tensPlaceTimer);
	DrawFormatString(696, 60, 0xffffff, "%d", m_onesPlaceTimer);
#endif
}

void SceneGame::End()
{
}

void SceneGame::DrawTimer()
{
	VECTOR temp = m_pPlayer->GetPos();

	if (!m_isStart)
	{
		if (m_countDown > 0)
		{
			auto countDown = std::to_string(m_countDown);
			DrawRotaGraph(640,360,0.4f,0.0f, m_graphManager->GetHandle(countDown),true);
		}
		else
		{
			DrawRotaGraph(640, 360, 1.0f, 0.0f, m_graphManager->GetHandle("Start"), true);
		}

	}
	else
	{
		DrawRotaGraph(560, 80, 0.48f, 0.0f, m_graphManager->GetHandle("TimerText"), true);


		auto onesPlaceTimer = std::to_string(m_onesPlaceTimer);
		auto tensPlaceTimer = std::to_string(m_tensPlaceTimer);

		auto time = stoi(tensPlaceTimer + onesPlaceTimer);
		float size = 0.4f;
		if (time != 0 && time % 20 == 0)
		{
			size = 0.6f;
		}

		DrawRotaGraph(800, 80, size, 0.0f, m_graphManager->GetHandle(onesPlaceTimer), true);
		DrawRotaGraph(720, 80, size, 0.0f, m_graphManager->GetHandle(tensPlaceTimer), true);
	}
}

void SceneGame::CreateObstruct(VECTOR pos)
{
	for (auto& obstruct : m_pEnemy)
	{
		if (!obstruct)
		{
			obstruct = std::make_shared<Enemy>();
			obstruct->Init(pos);
			return;
		}
	}
	return;
}

void SceneGame::ObstructGenerator(int frame)
{
	auto pos = m_pCamera->GetRightEnd();

	if (frame == 60 * 2)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 8)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 14)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}


	if (frame == 60 * 20)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 25)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 30)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 35)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}


	if (frame == 60 * 40)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 44)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 48)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 52)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 56)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}

	if (frame == 60 * 60)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kUpperPosY, 0.0f));
	}
	if (frame == 60 * 63)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 65)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 68)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 72)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
	if (frame == 60 * 74)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kUpperPosY, 0.0f));
	}
	if (frame == 60 * 78)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
	}
	if (frame == 60 * 81)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kUpperPosY, 0.0f));
	}
	if (frame == 60 * 83)
	{
		CreateObstruct(VGet(pos, kLowerPosY, 0.0f));
		CreateObstruct(VGet(pos, kMiddlePosY, 0.0f));
	}
}
