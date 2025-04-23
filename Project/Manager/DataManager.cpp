#include "DataManager.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>


#include <DxLib.h>

void DataManager::LoadInfo()
{
	// 一時保存用string
	std::string strBuf;
	// カンマ分け一時保存用string
	std::vector<std::string> strConmaBuf;

	// ファイル読み込み
	std::ifstream ifs("csvTest.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	// 最初は対応表情報が入っているだけなので無視する
	std::getline(ifs, strBuf);
	// 情報を読み切るまでループ
	while (std::getline(ifs, strBuf))
	{
		strConmaBuf = Split(strBuf, ',');

		Load(strConmaBuf);		
	}
}

std::vector<std::string> DataManager::Split(std::string& str, char del)
{
	// 区切り開始位置
	int first = 0;
	// 区切り最終位置
	int last = str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size())
	{
		// 区切ったものを結果に入れていく
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		// 位置更新
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

void DataManager::Load(std::vector<std::string>& inputInfo)
{

}
