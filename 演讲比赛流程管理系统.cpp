#include<iostream>
#include<string>
#include"speechManager.h"
#include<ctime>
using namespace std;

int main()
{
	//创建随机数种子
	srand((unsigned int)time(NULL));

	//实例化对象
	SpeechManager sm;
	cout << "选手列表" << endl;
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << " 编号: " << it->first << " 姓名: " << it->second.m_Name << " 分数: " << (*it).second.m_Score[0] << endl;
	}

	int choice = 0;//存储用户的输入
	while (true)
	{
		sm.Show_Menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();	//开始演讲比赛
			break;
		case 2:
			sm.showRecord();	//查看往届记录
			break;
		case 3:
			sm.clearRecord();	//清空比赛记录
			break;
		case 0:
			sm.exitSystem();	//退出系统
			break;
		default:
			system("cls");		//清屏
			break;
		}
	}
	
	system("pause");
	return 0;
}