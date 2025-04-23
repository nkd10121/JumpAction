#include "DxLib.h"
#include "scene/SceneManager.h"
#include "Input.h"
#include <memory>

namespace
{
	//ウィンドウサイズ
	constexpr int kWindowWidth = 1280;
	constexpr int kWindowHeight = 720;
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	SetGraphMode(kWindowWidth, kWindowHeight, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 10.0f, -20.0f), VGet(0.0f, 0.0f, 0.0f));

	SetDrawScreen(DX_SCREEN_BACK);

	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	pScene->Init();

	Input input;

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
		input.Update();
		pScene->Update(input);
		pScene->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		if (pScene->GetGameEndFlag())
		{
			break;
		}


		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}