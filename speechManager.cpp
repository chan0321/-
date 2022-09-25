#include"speechManager.h"


//���캯��
SpeechManager::SpeechManager() 
{
	this->initSpeech();
	this->createSpeeker();
	this->loadRecord();
}

//��������
SpeechManager::~SpeechManager()
{
}

//�˵�
void SpeechManager::Show_Menu()
{
	cout << "*****************************************" << endl;
	cout << "*********** ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*********** 1.��ʼ�ݽ�����   ************" << endl;
	cout << "*********** 2.�鿴�����¼   ************" << endl;
	cout << "*********** 3.��ձ�����¼   ************" << endl;
	cout << "*********** 0.�˳���������   ************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "�˳��ɹ�����ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

//��������ѡ��
void SpeechManager::createSpeeker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//��ѡ�ֱ�ŷ���map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void  SpeechManager::startSpeech()
{

	//��һ�ֱ�����ʼ
	//��ǩ
	this->speechDraw();

	//����
	this->speechContest();

	//��ʾ�������
	this->showScore();

	//�ڶ��ֱ�����ʼ
	this->m_Index++;

	//��ǩ
	speechDraw();

	//����
	speechContest();

	//��ʾ���ս��
	showScore();

	//�����¼���ļ�
	this->saveRecord();

	//��ʼ������
	this->initSpeech();

	//����ѡ��
	this->createSpeeker();

	//��ȡ�����¼
	this->loadRecord();

	cout << "���α��������" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------------" << endl;
	cout << "��ǩ�������" << endl;
	if (this->m_Index == 1)
	{
		//��һ�ֱ��� ����˳��
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ��� ����˳��
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "----------------------------" << endl;
	system("pause");
}

//����
void SpeechManager::speechContest()
{

	cout << "��" << this->m_Index << "�ֱ�����ʽ��ʼ" << endl;

	//׼����ʱ���������С��ɼ�
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//��¼��Ա���� 6��һ��
	vector<int>v_Src;	//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		cout << "���" << *it << this->m_Speaker[*it].m_Name<<"�ķ�������" << endl;
		deque<double>d;
		num++;

		//ʮλ��ί���
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();	//ȥ����߷�
		d.pop_back();	//ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0f);	//�ܷ�
		double avg = sum / (double)d.size();	//ƽ����
		cout << "ѡ�����÷�: " << avg << endl;
		cout << endl;

		//��ƽ���ַŽ�map����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//��������ݷ�����ʱС��������
		groupScore.insert(make_pair(avg, *it));	//key��ƽ���֣�value��ѡ�ֱ��

		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���" 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}
			groupScore.clear();
		}
	}
	cout << "--------------��" << this->m_Index << "�ֱ������--------------" << endl;
	system("pause");
}

void SpeechManager::showScore()		//��ʾ����
{
	if (this->m_Index == 1)
	{
		cout << "----------��" << this->m_Index << "�ֽ���ѡ����������----------" << endl;
	}
	else
	{
		cout << "---------���α�����ʤ��������------------"<< endl;

	}
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ��:" << *it << " ����:" << this->m_Speaker[*it].m_Name << " �÷�:" 
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	
	system("pause");
	system("cls");
	this->Show_Menu();
}

void SpeechManager::saveRecord()		//�����¼���ļ�
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�

	//��ÿ��ѡ������д�뵽�ļ���
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��ѱ���"<<endl;


	//�����ļ���Ϊ�յ�״̬
	this->fileIsEmpty = false;
	m_Record.clear();
	this->loadRecord();
}

void SpeechManager::loadRecord()		//�������¼
{
	ifstream ifs("speech.csv", ios::in);	//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);	//��������ߵ��ַ��Ż�
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;	//�������string�ַ���
		int pos = -1;
		int start = 0;
		pos = data.find(",", start);
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

}

void SpeechManager::showRecord()		//��ʾ�����¼
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "��" << "�ھ����:" << this->m_Record[i][0] << "�÷�:" << this->m_Record[i][1] << " "
			<< "�Ǿ����:" << this->m_Record[i][2] << "�÷�:" << this->m_Record[i][3] << " "
			<< "�������:" << this->m_Record[i][4] << "�÷�:" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()		//��������¼
{
	cout << "�Ƿ�ȷ������ļ�����Y/N��" << endl;
	char s;
	cin >> s;
	if (s == 'Y')
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeeker();
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	else if (s == 'N')
	{
		cout << "ȡ���ɹ�" << endl;
	}
	system("pause");
	system("cls");
}
