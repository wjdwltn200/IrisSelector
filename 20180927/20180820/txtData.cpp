#include "stdafx.h"
#include "txtData.h"


HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vecStr)
{
	char str[128];// = { 'h', 'e', 'l', 'l', 'o' };
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vecStr), 126);

	// ���� ���� (���� txt ������ ���������)
	HANDLE hFile;
	hFile = CreateFile(saveFileName,	// ���̺��� ���� ��� / �����̸�
		GENERIC_WRITE,			// ���� ��� ����
		0,						// ���� ���� ��� ���� (0) : ���� ����
								// FILE_SHARE_DELETE : ���� ���� ��û�� ����
		NULL,					// ���� ���� �ɼ�
		CREATE_ALWAYS,			// CREATE_ALWAYS : ���ο� ���� ����, ������ �̸��� ������ ������ �����
								// CREATE_NEW : ���ο� ���� ����
								// OPEN_EXISTING : ������ �����ϸ� ����, ������ �����ڵ� ����
		FILE_ATTRIBUTE_NORMAL,	// FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ��� ����
								// FILE_ATTRIBUTE_READONLY : �б� ���� ����
								// FILE_ATTRIBUTE_HIDDEN : ���� ���� ����
		NULL);

	// ���Ͽ� ������ ����
	WriteFile(hFile, str, 128, &write, NULL);

	// �� �� ���� �ڵ��� ����
	CloseHandle(hFile);
}

// string�� ���ҷ� ���� vector => �ϳ��� ���ڿ�
char * txtData::vectorArrayCombine(vector<string> vecArray)
{
	//�̼���
	//������
	//���ο�
	char str[128];
	ZeroMemory(str, sizeof(str));
	//memset(str, 0, sizeof(str));

	for (int i = 0; i < vecArray.size(); i++)
	{
		strncat_s(str, 128, vecArray[i].c_str(), 126);
		if (i + 1 < vecArray.size())
			strcat_s(str, ",");
	}

	//�̼���,������,���ο�

	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	char str[128];
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, str, 128, &read, NULL);

	CloseHandle(hFile);

	return charArraySeparation(str);
}

// �ϳ��� ���ڿ� => string�� ���ҷ� ���� vector
vector<string> txtData::charArraySeparation(char charArray[])
{
	//�̼���,������,���ο�
	vector<string> vecStr;
	const char* separator = ",";
	char* token;
	char* temp;

	token = strtok_s(charArray, separator, &temp);
	// token = "�̼���";
	vecStr.push_back(token);

	while ((token = strtok_s(NULL, separator, &temp)) != NULL)
	{
		vecStr.push_back(token);
	}

	return vecStr;
}

void txtData::mapSave(const char * saveFileName, tagTile* tiles,RECT* sample)
{
	DWORD write;


	// ���� ���� (���� txt ������ ���������)
	HANDLE hFile;
	hFile = CreateFile(saveFileName,	// ���̺��� ���� ��� / �����̸�
		GENERIC_WRITE,			// ���� ��� ����
		0,						// ���� ���� ��� ���� (0) : ���� ����
								// FILE_SHARE_DELETE : ���� ���� ��û�� ����
		NULL,					// ���� ���� �ɼ�
		CREATE_ALWAYS,			// CREATE_ALWAYS : ���ο� ���� ����, ������ �̸��� ������ ������ �����
								// CREATE_NEW : ���ο� ���� ����
								// OPEN_EXISTING : ������ �����ϸ� ����, ������ �����ڵ� ����
		FILE_ATTRIBUTE_NORMAL,	// FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ��� ����
								// FILE_ATTRIBUTE_READONLY : �б� ���� ����
								// FILE_ATTRIBUTE_HIDDEN : ���� ���� ����
		NULL);

	// ���Ͽ� ������ ����
	WriteFile(hFile, tiles, sizeof(tagTile) *TILE_X *TILE_Y, &write, NULL);
	WriteFile(hFile, sample, sizeof(RECT), &write, NULL);

	// �� �� ���� �ڵ��� ����
	CloseHandle(hFile);
}


void txtData::mapLoad(const char * loadFileName, tagTile* tiles, RECT* sample)
{
	DWORD read;

	HANDLE hFile;
	hFile = CreateFile(loadFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(hFile, tiles, sizeof(tagTile) *TILE_X *TILE_Y, &read, NULL);
	ReadFile(hFile, sample, sizeof(RECT), &read, NULL);

	CloseHandle(hFile);
}


txtData::txtData()
{
}


txtData::~txtData()
{
}