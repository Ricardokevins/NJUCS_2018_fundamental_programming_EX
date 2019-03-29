#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <functional>
#include <conio.h>
#include<cstring> 
#include <stdio.h>
#include<string>
#include<cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <Windows.h>
//#include <stdlib.h>
using namespace std;
class song {//打算是在用一个类的数组来保存很多的歌曲对象实体
public:
	string songname;//歌的名字
	string pinyin;
	string singername;//歌手的名
	int serialnum;//序列号，就是在歌单里的序列
	int ranknum;//排行的位置
	//int playingnum;//在播放列表里的位置？感觉不是很有必要
	int playstatus;//是否处于播放状态
	int frequence;//播放的次数，作为计算的根据
	int totalscore;//总分，也是计算的根据
	int starnum;//评分数
};

class admin
{
public:
	admin();
	friend class ktvsystem;
	vector<song> mysong;
	int changepassword();//这两个返回值都是表示状态，改成功和登陆成功

	int login();//登陆函数

	int add_song();//加歌

	int delete_song();//删除歌曲，成功返回1

	int file_in();//加载外面文件的歌曲，加载成功就返回1

	int file_out();

	int search_song();//找歌的函数，返回歌曲的位置

	int sort_song();//对歌曲排序

	int admenu();//显示管理员的专用界面，并接受输入的操作值
private:
	string ID;
	string password;//保存密码
	int adopnum;//作为管理员的操作值，作为判断执行函数的参数

};

class user {
public:
	//user();
	friend class ktvsystem;
	int usmenu();//显示用户界面并返回操作值

	int ordersong(vector<song> A);//点歌

	int see_playingqueue(vector<song> A);//查看待播放队列里歌曲

	int make_song_top(vector<song> A);//置顶

	int change_song(vector<song> A);//切歌

	int delete_song_inqueue(vector<song> A);//删除播放队列中的歌

	int judge_song(vector<song> A);//评分

private:
	int usopnum;//操作值
	vector<int>playing_queue;//正在播放的队列，保存所有的播放的歌曲
};

class ktvsystem {
public:
	admin A;
	user B;
	int pmainmenu();
	void selectoperation();
	void run();
	vector<song> mysong;
private:
	int syoperationnum;//system的操作代码
};

admin::admin(void)
{
	ID = "NJUCS";
	password = "CSNB";
	system("cls");
	system("color f1");
	cout << "创建新的管理员成功,正在跳转页面" << endl;
	Sleep(2000);
}

int admin::admenu()
{
	system("cls");
	system("color f1");
	cout<<"\n\n\t\t\t＋==============================＋\n";
	cout<<"\t\t\t｜ ｜\n";
	cout<<"\t\t\t｜ 1->查看所有的歌曲  ｜\n";
	cout<<"\t\t\t｜ 2->添加歌曲       ｜\n";
	cout<<"\t\t\t｜ 3->批量的导入歌曲  ｜\n";
	cout<<"\t\t\t｜ 4->批量的导出歌曲  ｜\n";
	cout<<"\t\t\t｜ 5->删除歌曲       ｜\n";
	cout<<"\t\t\t｜ 6->歌曲排序       ｜\n";
	cout<<"\t\t\t｜ 7->修改密码       ｜\n";
	cout<<"\t\t\t｜ 8->退出           ｜\n";
	cout<<"\t\t\t｜                   ｜\n";
	cout<<"\t\t\t＋==============================＋\n";
	fflush(stdin);
	int adnumtemp = 100;
	while (adnumtemp != 8)
	{
		cin >> adnumtemp;
		if (adnumtemp != 3 && adnumtemp != 4 && adnumtemp != 8)
		{
			cout << "输入错了，请输入合法的字符！！！" << endl;
			adnumtemp = 100;
			fflush(stdin);
			continue;
		}
		switch (adnumtemp)
		{
		case 8:cout << "再见" << endl; return 0 ;
		case 3:this->file_in(); break;
		case 4:this->file_out(); break;
		}
	}
	return 1;
}

int admin::login()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ *********************管理员登陆**********************  ｜\n");
	printf("\t\t\t｜ 管理员ID：       ｜\n");
	printf("\t\t\t｜ 管理员密码：  ｜\n");
	printf("\t\t\t＋==============================＋\n");
	fflush(stdin);

	string IDtemp;
	string passwordtemp;
	int IDlegal(1);
	int passwordlegal(1);
	int boolsuccess(0);
	char  temp = 's';
	int times(0);
	while (!boolsuccess&&times < 3)
	{
		fflush(stdin);
		IDtemp.clear();
		passwordtemp.clear();
		cout << "*****输入你的账号，请注意输入格式*****" << endl;
		while (IDlegal)
		{
			IDlegal = 0;
			temp = 's';
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9'))
				{
					//putchar('*');
					putchar(temp);
					IDtemp += temp;
				}
				else
				{
					if (temp != '\r' && temp != '\n')
					{
						if ((temp & 0xff) == 8)
						{
							if (IDtemp.length() > 0) 
							{
								cout << temp << " " << temp;
								IDtemp.pop_back();
							}
							fflush(stdin);
							continue;
						}
						else
						{
							IDlegal = 1;
							cout << '\r';
							cout << "*****输入了非法字符，请重新输入*****" << endl;
							fflush(stdin);
							continue;
						}
					}
					else
					{
						IDlegal = 0;
						cout << endl;
					}

				}
			}
			if (IDtemp.length() >= 12)
			{
				cout << "*****输入过长，请重新输入*****" << endl;
				IDlegal = 1;
				IDtemp.clear();
				fflush(stdin);
			}
		}
		IDlegal = 1;
		cout << "*****输入你的密码，请注意输入格式*****" << endl;
		while (passwordlegal)
		{
			temp = 's';
			passwordlegal = 0;
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9'))
				{
					putchar('*');
					passwordtemp += temp;
				}
				else
				{
					if (temp != '\r' && temp != '\n')
					{
						if ((temp & 0xff) == 8)
						{
							if (passwordtemp.length() > 0)
							{
								cout << temp << " " << temp;
								passwordtemp.pop_back();
							}
							fflush(stdin);
							continue;
						}
						else
						{
							passwordlegal = 1;
							cout << '\r';
							cout << "*****输入了非法字符，请重新输入*****" << endl;
							fflush(stdin);
							continue;
						}
					}
					else
					{
						passwordlegal = 0;
						cout << endl;
					}

				}
			}
			if (passwordtemp.length() >= 12)
			{
				cout << '\r';
				cout << "*****输入过长，请重新输入*****" << endl;
				passwordlegal = 1;
				passwordtemp.clear();
				fflush(stdin);
			}
		}
		passwordlegal = 1;
		if (IDtemp.length() != ID.length())//先判断长度，不一样就一定是错的
		{
			boolsuccess = 0;
			times++;
			cout << "没有这个ID" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		if (passwordtemp.length() != password.length())
		{
			boolsuccess = 0;
			times++;
			cout << "密码不对吧" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		for (int i = 0; i < IDtemp.length(); i++)//接着进行遍历比对
		{
			if (IDtemp[i] != ID[i])
			{
				boolsuccess = 0;
				times++;
				cout << "没有这个ID" << endl;
				cout << "你还有" << 3 - times << "次的机会" << endl;
				break;
			}
		}
		for (int i = 0; i < passwordtemp.length(); i++)
		{
			if (passwordtemp[i] != password[i])
			{
				boolsuccess = 0;
				times++;
				cout << "密码不对吧" << endl;
				cout << "你还有" << 3 - times << "次的机会" << endl;
				break;
			}
		}
		boolsuccess = 1;
	}
	if (times == 3)
	{
		cout << "*****你根本就不是管理员，再见！*****" << endl;
		return 0;
	}
	cout << "小伙子，没想到你也是管理员啊" << endl;
	admenu();
	return 1;
}

int admin::file_out()
{
	fstream myoperate;
	myoperate.open("ktvsong.txt", ofstream::app);
	if (myoperate.fail())
	{
		cout << "error" << endl;
		return 0;
	}
	myoperate << "歌手" << " ";
	cout << "input singer name" << endl;
	string singer;
	cin >> singer;
	myoperate << singer <<" ";
	cout << "input song name" << endl;
	myoperate << "歌曲名" <<" ";
	fflush(stdin);
	string songname ;
	cin >> songname;
	myoperate << songname << endl;
	cout << "input success" << endl;
	return 1;
	
}

int admin::file_in()
{
	string data;
	ifstream infile;
	infile.open("ktvsong.txt");
	if (infile.fail())
	{
		cout << "some error!!!" << endl;
		return 0;
	}
	for (; !infile.eof();)
	{
		song temp;
		string tempsingername;
		string tempsongname;
		infile >> tempsingername;
		infile >> temp.singername;
		infile >> tempsongname;
		infile >> temp.songname;
		mysong.push_back(temp);
	}
	for (int j(0); j<mysong.size(); j++)
	{
		cout << mysong[j].songname << " ";
		cout << mysong[j].singername << endl;
	}
	return 1;
}

int ktvsystem::pmainmenu()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ 1->用户直达 ｜\n");
	printf("\t\t\t｜ 2->管理员登陆 ｜\n");
	printf("\t\t\t｜ 0->退出系统 ｜\n");
	printf("\t\t\t｜ 请输入选项[ ]｜\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t＋==============================＋\n");
	cin >> syoperationnum;
	return syoperationnum;
}

void ktvsystem::selectoperation()
{
	if (syoperationnum == 1)
	{
		A.admenu();
	}
	else
		B.usmenu();
}

void ktvsystem::run()
{
	int opnumtemp = 100;
	while (opnumtemp != 3)
	{
		opnumtemp = pmainmenu();
		if (opnumtemp != 3 && opnumtemp != 1 && opnumtemp != 2)
		{
			cout << "输入错了，请输入合法的字符！！！" << endl;
			opnumtemp = 111;
			fflush(stdin);
			continue;
		}
		switch (opnumtemp)
		{
		case 3:cout << "再见" << endl; break;
		case 1:B.usmenu(); break;
		case 2:A.login(); break;
		}
	}
}

int user::usmenu()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ 1->歌手搜索  ｜\n");
	printf("\t\t\t｜ 2->歌曲搜索       ｜\n");
	printf("\t\t\t｜ 3->拼音点歌  ｜\n");
	printf("\t\t\t｜ 4->所有歌曲       ｜\n");
	printf("\t\t\t｜ 5->已点歌曲       ｜\n");
	printf("\t\t\t｜ 6->切歌       ｜\n");
	printf("\t\t\t｜ 0->退出           ｜\n");
	printf("\t\t\t｜                   ｜\n");
	printf("\t\t\t＋==============================＋\n");
	fflush(stdin);
	cin >> usopnum;
	return usopnum;
}

int main()
{
	/*
	ktvsystem cursys;
	cursys.run();
	return 0;
	*/
	admin A;
	//A.file_out();
	A.file_in();
}
