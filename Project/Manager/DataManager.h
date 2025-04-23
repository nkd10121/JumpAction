#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// �G�l�~�[�̐�����csv����擾����p
/// ���炤���:�����^�C�~���O�A���������ꏊ
/// </summary>
class DataManager
{
public:
	void LoadInfo();


private:
	struct Header
	{
		char id[4] = "inf";	//�Ō��\n�������Ă��邽�߂����4�������Ǝv���Ă���(4�o�C�g)
		float version = 1.0f;	//4�o�C�g
		size_t dataCount = 0;	//4�o�C�g
		//�󔒂�4�o�C�g�������Ă���(�p�f�B���O)
	};

	struct EnemyInfo
	{
		int second;
		std::vector<float> posY;
	};

	std::unordered_map<std::string, EnemyInfo> m_enemyData;

	/// �����֐�
	/// </summary>
	/// <param name="str">���̕�����</param>
	/// <param name="del">�������镶��</param>
	/// <returns>�������������Q</returns>
	std::vector<std::string> Split(std::string& str, char del);

	void Load(std::vector<std::string>& inputInfo);
};

