#include "DataManager.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>


#include <DxLib.h>

void DataManager::LoadInfo()
{
	// �ꎞ�ۑ��pstring
	std::string strBuf;
	// �J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	// �t�@�C���ǂݍ���
	std::ifstream ifs("csvTest.csv");
	if (!ifs)
	{
		assert(false);
		return;
	}

	// �ŏ��͑Ή��\��񂪓����Ă��邾���Ȃ̂Ŗ�������
	std::getline(ifs, strBuf);
	// ����ǂݐ؂�܂Ń��[�v
	while (std::getline(ifs, strBuf))
	{
		strConmaBuf = Split(strBuf, ',');

		Load(strConmaBuf);		
	}
}

std::vector<std::string> DataManager::Split(std::string& str, char del)
{
	// ��؂�J�n�ʒu
	int first = 0;
	// ��؂�ŏI�ʒu
	int last = str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size())
	{
		// ��؂������̂����ʂɓ���Ă���
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		// �ʒu�X�V
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
