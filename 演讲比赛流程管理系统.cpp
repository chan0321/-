#include<iostream>
#include<string>
#include"speechManager.h"
#include<ctime>
using namespace std;

int main()
{
	//�������������
	srand((unsigned int)time(NULL));

	//ʵ��������
	SpeechManager sm;
	cout << "ѡ���б�" << endl;
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << " ���: " << it->first << " ����: " << it->second.m_Name << " ����: " << (*it).second.m_Score[0] << endl;
	}

	int choice = 0;//�洢�û�������
	while (true)
	{
		sm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();	//��ʼ�ݽ�����
			break;
		case 2:
			sm.showRecord();	//�鿴�����¼
			break;
		case 3:
			sm.clearRecord();	//��ձ�����¼
			break;
		case 0:
			sm.exitSystem();	//�˳�ϵͳ
			break;
		default:
			system("cls");		//����
			break;
		}
	}
	
	system("pause");
	return 0;
}