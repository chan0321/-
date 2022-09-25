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

//����ݽ�������
class SpeechManager {
public:
	//���캯��
	SpeechManager();

	//��������
	~SpeechManager();

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������������
	void initSpeech();

	//��������ѡ��
	void createSpeeker();

	void startSpeech();		//��ʼ����
	void speechDraw();		//��ǩ
	void speechContest();	//�������
	void showScore();		//��ʾ����
	void saveRecord();		//�����¼���ļ�
	void loadRecord();		//���������¼
	void showRecord();		//��ʾ�����¼
	void clearRecord();		//��������¼
	


	//��Ա����
	vector<int>v1;	//�����һ�ֱ���ѡ�ֱ��
	vector<int>v2;	//����ڶ��ֱ���ѡ�ֱ��
	vector<int>v3;	//����ʤ��ǰ����ѡ�ֱ��
	map<int, Speaker>m_Speaker;	//�������Լ�����
	int m_Index;	//�����������
	bool fileIsEmpty;		//�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>>m_Record;	//��������¼������
};