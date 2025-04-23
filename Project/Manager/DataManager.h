#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// エネミーの生成をcsvから取得する用
/// もらう情報:生成タイミング、生成される場所
/// </summary>
class DataManager
{
public:
	void LoadInfo();


private:
	struct Header
	{
		char id[4] = "inf";	//最後に\nが入っているためこれで4文字だと思っていい(4バイト)
		float version = 1.0f;	//4バイト
		size_t dataCount = 0;	//4バイト
		//空白の4バイトが入っている(パディング)
	};

	struct EnemyInfo
	{
		int second;
		std::vector<float> posY;
	};

	std::unordered_map<std::string, EnemyInfo> m_enemyData;

	/// 分割関数
	/// </summary>
	/// <param name="str">元の文字列</param>
	/// <param name="del">分割する文字</param>
	/// <returns>分割した文字群</returns>
	std::vector<std::string> Split(std::string& str, char del);

	void Load(std::vector<std::string>& inputInfo);
};

