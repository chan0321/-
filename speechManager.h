#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include"speaker.h"
#include<string>
#include<fstream>
using namespace std;

//设计演讲管理类
class SpeechManager {
public:
	//构造函数
	SpeechManager();

	//析构函数
	~SpeechManager();

	//展示菜单
	void Show_Menu();

	//退出系统
	void exitSystem();

	//初始化容器和属性
	void initSpeech();

	//创建比赛选手
	void createSpeeker();

	void startSpeech();		//开始比赛
	void speechDraw();		//抽签
	void speechContest();	//比赛打分
	void showScore();		//显示分数
	void saveRecord();		//保存记录到文件
	void loadRecord();		//加载往届记录
	void showRecord();		//显示往届记录
	void clearRecord();		//清空往届记录
	


	//成员属性
	vector<int>v1;	//保存第一轮比赛选手编号
	vector<int>v2;	//保存第二轮比赛选手编号
	vector<int>v3;	//保存胜出前三名选手编号
	map<int, Speaker>m_Speaker;	//保存编号以及姓名
	int m_Index;	//保存比赛轮数
	bool fileIsEmpty;		//判断文件是否为空
	map<int, vector<string>>m_Record;	//存放往届记录的容器
};