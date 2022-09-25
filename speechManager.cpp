#include"speechManager.h"


//构造函数
SpeechManager::SpeechManager() 
{
	this->initSpeech();
	this->createSpeeker();
	this->loadRecord();
}

//析构函数
SpeechManager::~SpeechManager()
{
}

//菜单
void SpeechManager::Show_Menu()
{
	cout << "*****************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 ************" << endl;
	cout << "*********** 1.开始演讲比赛   ************" << endl;
	cout << "*********** 2.查看往届记录   ************" << endl;
	cout << "*********** 3.清空比赛记录   ************" << endl;
	cout << "*********** 0.退出比赛程序   ************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "退出成功，欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

//创建比赛选手
void SpeechManager::createSpeeker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		//创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号
		this->v1.push_back(i + 10001);

		//将选手编号放入map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//抽签
void  SpeechManager::startSpeech()
{

	//第一轮比赛开始
	//抽签
	this->speechDraw();

	//比赛
	this->speechContest();

	//显示晋级结果
	this->showScore();

	//第二轮比赛开始
	this->m_Index++;

	//抽签
	speechDraw();

	//比赛
	speechContest();

	//显示最终结果
	showScore();

	//保存记录到文件
	this->saveRecord();

	//初始化属性
	this->initSpeech();

	//创建选手
	this->createSpeeker();

	//获取往届记录
	this->loadRecord();

	cout << "本次比赛已完成" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "----------------------------" << endl;
	cout << "抽签结果如下" << endl;
	if (this->m_Index == 1)
	{
		//第一轮比赛 打乱顺序
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛 打乱顺序
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

//比赛
void SpeechManager::speechContest()
{

	cout << "第" << this->m_Index << "轮比赛正式开始" << endl;

	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//记录人员个数 6人一组
	vector<int>v_Src;	//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		cout << "编号" << *it << this->m_Speaker[*it].m_Name<<"的分数如下" << endl;
		deque<double>d;
		num++;

		//十位评委打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();	//去除最高分
		d.pop_back();	//去除最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f);	//总分
		double avg = sum / (double)d.size();	//平均分
		cout << "选手最后得分: " << avg << endl;
		cout << endl;

		//将平均分放进map容器
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据放入临时小组容器中
		groupScore.insert(make_pair(avg, *it));	//key是平均分，value是选手编号

		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name << " 成绩：" 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//取走前三名
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
	cout << "--------------第" << this->m_Index << "轮比赛完毕--------------" << endl;
	system("pause");
}

void SpeechManager::showScore()		//显示分数
{
	if (this->m_Index == 1)
	{
		cout << "----------第" << this->m_Index << "轮晋级选手名单如下----------" << endl;
	}
	else
	{
		cout << "---------本次比赛获胜名单如下------------"<< endl;

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
		cout << "选手编号:" << *it << " 姓名:" << this->m_Speaker[*it].m_Name << " 得分:" 
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	
	system("pause");
	system("cls");
	this->Show_Menu();
}

void SpeechManager::saveRecord()		//保存记录到文件
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件

	//将每个选手数据写入到文件中
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件已保存"<<endl;


	//更改文件不为空的状态
	this->fileIsEmpty = false;
	m_Record.clear();
	this->loadRecord();
}

void SpeechManager::loadRecord()		//读往届记录
{
	ifstream ifs("speech.csv", ios::in);	//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);	//将上面读走的字符放回
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;	//存放六个string字符串
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

void SpeechManager::showRecord()		//显示往届记录
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届" << "冠军编号:" << this->m_Record[i][0] << "得分:" << this->m_Record[i][1] << " "
			<< "亚军编号:" << this->m_Record[i][2] << "得分:" << this->m_Record[i][3] << " "
			<< "季军编号:" << this->m_Record[i][4] << "得分:" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()		//清空往届记录
{
	cout << "是否确定清空文件？（Y/N）" << endl;
	char s;
	cin >> s;
	if (s == 'Y')
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->initSpeech();
		this->createSpeeker();
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	else if (s == 'N')
	{
		cout << "取消成功" << endl;
	}
	system("pause");
	system("cls");
}
