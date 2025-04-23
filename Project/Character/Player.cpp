#include "Player.h"
#include "Input.h"

namespace
{
	constexpr float kMoveSpeed = 0.08f;			//移動速度
	constexpr float kPlayerBasePosY = -0.4f;	//プレイヤーの基本y座標
	constexpr float kInitVelocity = 0.4f;		//ジャンプの初速
	constexpr float kGravity = 0.008f;			//重力

	constexpr float kHitBoxOffsetX = 0.8f;		//当たり判定の差分
	constexpr float kHitBoxOffsetY = 1.8f;		//当たり判定の差分
}

Player::Player() :
	m_isStart(false),
	m_pos(VGet(0.0f, kPlayerBasePosY, 0.0f)),
	m_isJump(false),
	m_isFirstJump(false),
	m_isSecondJump(false),
	m_jumpKeyPushFrame(0),
	m_moveForce(VGet(kMoveSpeed, 0.0f, 0.0f)),
	m_animTime(0),
	m_animTotalTime(0),
	m_attachAnimHandle(0)
{

}

Player::~Player()
{
	//ハンドルの削除
	MV1DeleteModel(m_handle);
}

void Player::Init()
{

	//3Dモデルの読み込み
	//m_handle = MV1LoadModel("data/model/character_dog.mv1");
	m_handle = MV1LoadModel("data/model/Dragon.mv1");

	// ３Ｄモデルのスケールを1.8倍する
	MV1SetScale(m_handle, VGet(0.012f, 0.012f, 0.012f));
	//MV1SetScale(m_handle, VGet(1.8f, 1.8f, 1.8f));

	// ３ＤモデルのY軸の回転値を-45度にセットする
	MV1SetRotationXYZ(m_handle, VGet(0.0f, -60.0f * DX_PI_F / 180.0f, 0.0f));

	/*アニメーションの設定*/
	//m_attachAnimHandle = MV1AttachAnim(m_handle, 1);
	m_attachAnimHandle = MV1AttachAnim(m_handle,3, -1, FALSE);
	m_animTotalTime = MV1GetAnimTotalTime(m_handle, m_attachAnimHandle);

}

void Player::Update(Input& input)
{
	if (!m_isStart)
	{
		return;
	}

#ifdef _DEBUG
	// プレイヤー制御.
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 右を押していたら右に進む
	if (key & PAD_INPUT_RIGHT) 
	{
		m_pos.x += kMoveSpeed;
	}

	// 左を押していたら左に進む
	if (key & PAD_INPUT_LEFT)
	{
		m_pos.x -= kMoveSpeed;
	}
#endif

	MV1SetAttachAnimTime(m_handle, m_attachAnimHandle, m_animTime);
	m_animTime += 1.0f;
	if (m_animTime >= m_animTotalTime) 
	{
		m_animTime = 0.0f;
	}

	/*ジャンプ関係*/
	if (input.IsTriggered("JUMP"))
	{
		m_jumpKeyPushFrame++;

		//長押ししても一回しか呼ばれないように
		if (m_jumpKeyPushFrame == 1)
		{
			//一回目のジャンプフラグがfalse(ジャンプしていない)のとき
			if (!m_isFirstJump)
			{
				//初速を与えて
				m_moveForce.y = kInitVelocity;
				//一回目のジャンプフラグをtrue(ジャンプしている)にする
				m_isFirstJump = true;
			}
			//一回目のジャンプフラグがtrueかつ
			//二回目のジャンプフラグがfalseのとき
			else if (!m_isSecondJump)
			{
				//初速をもう一度与えて
				m_moveForce.y = kInitVelocity;
				//二回目のジャンプフラグをtrueにする
				m_isSecondJump = true;
			}
		}
	}
	//ジャンプキーを押していないとき
	else
	{
		//押している時間をリセットする
		m_jumpKeyPushFrame = 0;
	}


	if (m_moveForce.y == kInitVelocity)
	{
		m_isJump = true;
	}
	else
	{
		m_isJump = false;
	}

	//ジャンプフラグがtrueの間
	if (m_isFirstJump)
	{
		//ジャンプ関数を呼ぶ
		Jump();
	}

	//地面についた時の処理
	if(m_pos.y < kPlayerBasePosY)
	{
		//ジャンプ関係の変数をリセットする
		m_isFirstJump = false;
		m_isSecondJump = false;
		m_moveForce.y = 0.0f;
		m_pos.y = kPlayerBasePosY;
	}

	//座標の更新
	m_pos = VAdd(m_pos,m_moveForce);

	// ３Dモデルのポジション設定
	MV1SetPosition(m_handle, m_pos);

	//当たり判定の座標を更新
	m_pHitBox.SetBox(m_pos.x - kHitBoxOffsetX / 2, m_pos.y + kHitBoxOffsetY, m_pos.x + kHitBoxOffsetX, m_pos.y + kHitBoxOffsetY / 4);
}

void Player::Draw()const
{
	//プレイヤー描画
	MV1DrawModel(m_handle);

#ifdef _DEBUG
	//当たり判定のデバッグ表示
	m_pHitBox.DrawCollision(m_pos);
#endif
}

void Player::Start()
{
	m_isStart = true;
}

void Player::Jump()
{
	//Y方向の速度に加速度を加える
	m_moveForce.y -= kGravity;

	m_moveForce.y *= 0.99f;
}