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
#include<iomanip>
//#include <stdlib.h>
using namespace std;
//备注歌曲的序列号和在数组里面的下标是不一样的


class song {//打算是在用一个类的数组来保存很多的歌曲对象实体
public:
	string songname;//歌的名字
	string pinyin;
	string singername;//歌手的名
	int serialnum;//序列号，就是在歌单里的序列
	int ranknum;//排行的位置
	int playstatus;//是否处于播放状态
	int frequence;//播放的次数，作为计算的根据
	int totalscore;//总分，也是计算的根据
	double starnum;//评分数
};

class admin
{
public:
	admin();

	friend class ktvsystem;

	friend class user;

	vector<song> mysong;

	int changepassword();//这两个返回值都是表示状态，改成功和登陆成功

	int login();//登陆函数

	int add_song();//加歌

	int delete_song();//删除歌曲，成功返回1

	int file_in();//加载外面文件的歌曲，加载成功就返回1

	int file_out();//导出文件

	int search_song();//找歌的函数，返回歌曲的位置

	int sort_song();//对歌曲排序

	int admenu();//显示管理员的专用界面，并接受输入的操作值

	int initialsong( song &temp);

	int printall();

	int printsong(song &temp);

	int legalID(string A);

	int legalpassword(string B);

	int realprintall();

private:
	string ID;
	string password;//保存密码
	int adopnum;//作为管理员的操作值，作为判断执行函数的参数

};

class user {
public:
	//user();
	friend class ktvsystem;

	friend class admin;

	int usmenu(admin &A);//显示用户界面并返回操作值

	int ordersong(admin &A);//点歌

	int see_playingqueue(admin &A);//查看待播放队列里歌曲

	int make_song_top(admin &A);//置顶

	int change_song(admin &A);//切歌

	int delete_song_inqueue(admin & A);//删除播放队列中的歌

	int judge_song(admin& A);//评分

	int realsee_playingqueue(admin &A);

private:
	int usopnum;//操作值
	vector<int>playing_queue;//正在播放的队列，保存所有的播放的歌曲
};

class ktvsystem {
public:
	admin A;
	user B;
	int pmainmenu();
	int initialsys();
	void run();
	vector<song> mysong;
private:
	int syoperationnum;//system的操作代码
};

bool comp_srerial(const song&A, const song&B)
{
	return A.starnum < B.starnum;
}

bool comp_starnum(const song&A, const song &B)
{
	return A.starnum < B.starnum;
}


admin::admin(void)
{
	ID = "NJUCS";
	password = "CSNB12";
}

int admin::admenu()
{
	system("cls");
	system("color f1");
	cout<<"\n\n\t\t\t＋==============================＋\n";
	cout<<"\t\t\t ｜ ｜\n";
	cout<<"\t\t\t ｜ 1->查看所有的歌曲  ｜\n";
	cout<<"\t\t\t ｜ 2->添加歌曲        |\n";
	cout<<"\t\t\t ｜ 3->批量的导入歌曲  ｜\n";
	cout<<"\t\t\t ｜ 4->批量的导出歌曲  ｜\n";
	cout<<"\t\t\t ｜ 5->删除歌曲       ｜\n";
	cout<<"\t\t\t ｜ 6->歌曲排序       ｜\n";
	cout<<"\t\t\t ｜ 7->修改密码       ｜\n";
	cout<<"\t\t\t ｜ 8->退出           ｜\n";
	cout<<"\t\t\t ｜                   ｜\n";
	cout<<"\t\t\t＋==============================＋\n";
	fflush(stdin);
	int adnumtemp = 100;
	while (1)
	{
		cin >> adnumtemp;
		switch (adnumtemp)
		{
		case 1:realprintall(); break;
		case 2:add_song(); break;
		case 3:file_in(); break;
		case 4:file_out(); break;
		case 5:delete_song(); break;
		case 6:sort_song(); break;
		case 7:changepassword(); break;
		case 8:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋==============================＋\n";
		cout << "\t\t\t ｜ ｜\n";
		cout << "\t\t\t ｜ 1->查看所有的歌曲  ｜\n";
		cout << "\t\t\t ｜ 2->添加歌曲       ｜\n";
		cout << "\t\t\t ｜ 3->批量的导入歌曲  ｜\n";
		cout << "\t\t\t ｜ 4->批量的导出歌曲  ｜\n";
		cout << "\t\t\t ｜ 5->删除歌曲       ｜\n";
		cout << "\t\t\t ｜ 6->歌曲排序       ｜\n";
		cout << "\t\t\t ｜ 7->修改密码       ｜\n";
		cout << "\t\t\t ｜ 8->退出           ｜\n";
		cout << "\t\t\t ｜                   ｜\n";
		cout << "\t\t\t＋==============================＋\n";
		fflush(stdin);
	}
	return 1;
}

int admin::login()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t ｜ ｜\n");
	printf("\t\t\t｜ *********************管理员登陆**********************  ｜\n");
	printf("\t\t\t ｜ 管理员ID：        ｜\n");
	printf("\t\t\t ｜ 管理员密码：      ｜\n");
	printf("\n\n\t\t\t＋==============================＋\n");
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
		boolsuccess=1;
		fflush(stdin);
		IDtemp.clear();
		passwordtemp.clear();
		cout << "|********输入你的账号，请注意输入格式********|" << endl;
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
							cout << "|*******输入了非法字符，请重新输入*******|" << endl;
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
				cout << "|*******输入过长，请重新输入*******|" << endl;
				IDlegal = 1;
				IDtemp.clear();
				fflush(stdin);
			}
		}
		IDlegal = 1;
		cout << "|*******输入你的密码，请注意输入格式*******|" << endl;
		while (passwordlegal)
		{	
			if (passwordlegal == 1)
			{
				passwordtemp.clear();
			}
			fflush(stdin);
			temp = 's';
			passwordlegal = 0;
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if (temp != '\r'&&temp != '\b'&&temp != '\n')
				{
					putchar('*');
					passwordtemp += temp;
				}
				if ((temp & 0xff) == 8)
				{
					if (passwordtemp.length() > 0)
					{
						cout << temp ;
						cout << " ";
						cout << temp;
						passwordtemp.pop_back();
					}
					fflush(stdin);
					continue;		
				}
			}
			cout << endl;
			if (legalpassword(passwordtemp))
			{
				passwordlegal = 0;
			}
			else
			{
				passwordlegal = 1;
				cout << "|***输入不合法，请重新输入***|" << endl;
			}
		}
		passwordlegal = 1;
		if (IDtemp.length() != ID.length())//先判断长度，不一样就一定是错的
		{
			boolsuccess = 0;
			times++;
			cout << "|***没有这个ID***|" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		if (passwordtemp.length() != password.length())
		{
			boolsuccess = 0;
			times++;
			cout << "|***密码不对吧***|" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		for (int i = 0; i < IDtemp.length(); i++)//接着进行遍历比对
		{
			if (IDtemp[i] != ID[i])
			{
				boolsuccess = 0;
				times++;
				cout << "|***没有这个ID***|" << endl;
				Sleep(1500);
				break;
			}
		}
		for (int i = 0; i < passwordtemp.length(); i++)
		{
			if (passwordtemp[i] != password[i])
			{
				boolsuccess = 0;
				times++;
				cout << "|***密码不对吧***|" << endl;
				break;
			}
		}
		if (times != 3)
		{
			cout << "你还有" << 3 - times << "次的机会" << endl;
		}
	}
	if (times == 3)
	{
		cout << "|*****你根本就不是管理员，再见！*****|" << endl;
		Sleep(1500);
		return 0;
	}
	cout << "小伙子，没想到你也是管理员啊" << endl;
	cout << "正在跳转页面" << endl;
	Sleep(1500);
	admenu();
	return 1;
}

int admin::file_out()
{
	fstream myoperate;
	myoperate.open("ktvsong.txt", ofstream::out);
	if (myoperate.fail())
	{
		cout << "文件导出失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int length(0);
	length = mysong.size();
	for (int i(0); i < length; i++)
	{
		string mysinger;
		mysinger=mysong[i].singername;
		myoperate << mysinger << " ";

		string mysongname;
		mysongname= mysong[i].songname;
		myoperate << mysongname << " ";

		string mypinyin;
		mypinyin = mysong[i].pinyin;
		myoperate << mypinyin << " ";
		myoperate << endl;
	}
	cout << "文件导出成功" << endl;
	Sleep(2000);
	return 0;
}

int admin::file_in()
{
	ifstream infile;
	string filesite;
	cin >> filesite;
	infile.open(filesite);
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int n = mysong.size();
	for (int j(1); !infile.eof();j++)
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.frequence = 0;
		temp.totalscore = 0;
		if (temp.frequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore/temp.frequence;
		temp.serialnum = j+n;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		mysong.push_back(temp);
	}
	mysong.pop_back();
	cout << "文件导入成功" << endl;
	return 1;
}

int admin::add_song()
{
	song temp;
	cout << "input singer name" << endl;
	string singer;
	cin >> singer;
	temp.singername = singer;

	cout << "input song name" << endl;
	fflush(stdin);
	string songname;
	cin >> songname;
	temp.songname = songname;

	cout << "input song pinyin" << endl;
	string mypinyin;
	fflush(stdin);
	cin >> mypinyin;
	temp.pinyin = mypinyin;

	int i = mysong.size();
	temp.serialnum = i + 1;
	initialsong(temp);
	mysong.push_back(temp);
	cout << "歌曲添加成功" << endl;
	Sleep(2000);
	return 0;
}

int admin::search_song()
{
	system("cls");
	system("color f1");
	cout << "\n\n\t\t\t＋==============================＋\n";
	cout << "\t\t\t｜ ｜\n";
	cout << "\t\t\t｜ 1->歌手名查找  ｜\n";
	cout << "\t\t\t｜ 2->歌曲名查找       ｜\n";
	cout << "\t\t\t｜ 3->拼音查找  ｜\n";
	cout << "\t\t\t｜ 4->退出  ｜\n";
	cout << "\t\t\t｜                   ｜\n";
	cout << "\t\t\t＋==============================＋\n";
	fflush(stdin);
	int opnum;
	cin >> opnum;
	fflush(stdin);
	int length = mysong.size();
	string temp;
	cout << "请输入查找的对象" << endl;
	cin >> temp;
	if (opnum == 1)
	{
		for (int i(0); i < length; i++)
		{
			if (mysong[i].singername == temp)
			{
				cout << "找到了" << endl;
				printsong(mysong[i]);
				Sleep(2000);
				return i;
			}
		}
		cout << "没有找到，即将返回上一级页面" << endl;
		Sleep(2000);
		return -1;
	}
	if (opnum == 2)
	{
		for (int i(0); i < length; i++)
		{
			if (mysong[i].songname == temp)
			{
				cout << "找到了" << endl;
				printsong(mysong[i]);
				Sleep(2000);
				return i;
			}
		}
		cout << "没有找到，即将返回上一级页面" << endl;
		Sleep(2000);
		return -1;
	}
	if (opnum == 3)
	{
		for (int i(0); i < length; i++)
		{
			if (mysong[i].pinyin == temp)
			{
				cout << "找到了" << endl;
				printsong(mysong[i]);
				Sleep(2000);
				return i;
			}
		}
		cout << "没有找到，即将返回上一级页面" << endl;
		Sleep(2000);
		return -1;
	}
	cout << "输入不合法，即将返回上一级页面" << endl;
	Sleep(2000);
	return -1;
}

int admin::delete_song()
{
	cout << "请输入你想删除的歌曲的编号" << endl;
	int serielnumber;
	cin >> serielnumber;
	if (serielnumber<1 || serielnumber>mysong.size())
	{
		cout << "输入不合法，即将返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	mysong.erase(mysong.begin() + serielnumber-1);
	for (int i(serielnumber-1); i < mysong.size(); i++)
	{
		mysong[i].serialnum--;
	}
	cout << "删除成功！！！" << endl;
	Sleep(2000);
	return 1;
}

int admin::initialsong(song&temp)
{
	temp.frequence = 0;
	temp.playstatus = 0;
	temp.ranknum = 0;
	temp.starnum = 0;
	temp.totalscore = 0;
	return 0;
}

int admin::printall()
{
	cout << left << setw(15) << "序列号" << "|";
	cout << left << setw(15) << "歌手" << "|";
	cout << left << setw(15) << "歌名" << "|";
	cout << left << setw(15) << "总分" << endl;
	int songlength = mysong.size();
	for (int i(0); i < songlength; i++)
	{
		song temp = mysong[i];
		printsong(temp);
	}
	return 0;
}

int admin::printsong(song&temp)
{
	cout << left << setw(15) << temp.serialnum << "|";
	cout << left << setw(15) << temp.singername << "|";
	cout << left << setw(15) << temp.songname << "|";
	cout << left << setw(15) << temp.starnum << "|";
	if (temp.playstatus == 1)
		cout << "--playing" << " ";
	cout << endl;
	return 0;
}

int admin::changepassword()
{
	int legalchange(1);
	while (legalchange)
	{
		cout << "请输入新的密码" << endl;
		fflush(stdin);
		string temp;
		cin >> temp;
		if (temp == password)
		{
			cout << "和旧密码一样，请重新输入" << endl;
			continue;
		}
		string confirm;
		cout << "请再输入一次确认密码" << endl;
		fflush(stdin);
		cin >> confirm;
		if (temp != confirm)
		{
			cout << "前后密码输入不一致请重新输入" << endl;
			temp.clear();
			confirm.clear();
			fflush(stdin);
			continue;
		}
		if (!legalpassword(temp))
		{
			cout << "输入的密码不合法" << endl;
			temp.clear();
			confirm.clear();
			fflush(stdin);
			continue;
		}
		cout << "密码更改成功，即将为你跳转页面" << endl;
		password = temp;
		legalchange = 0;
	}
	Sleep(2000);
	return 1;
}

int admin::sort_song()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ 1->序列号排序 ｜\n");
	printf("\t\t\t｜ 2->评分排序 ｜\n");
	printf("\t\t\t｜ 请输入选项[ ]｜\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t＋==============================＋\n");
	int i(0);
	cin >> i;
	if (i == 1) 
	{
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "排序完成，正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	if (i == 2)
	{
		sort(mysong.begin(), mysong.end(), comp_starnum);
		cout << "排序完成，正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	cout << "输入不合法，返回上一级" << endl;
	return 0;
}

int admin::legalID(string A)
{
	int legalnum(1);
	if (A.length() > 20)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z') || (A[i] >= '0'&&A[i] <= '9'))
			legalnum = 1;
		else
		{
			legalnum = 0;
			break;
		}
	}
	return legalnum;

}

int admin::legalpassword(string A)
{
	int wordlegalnum(0);
	int numberlegalnum(0);
	if (A.length() > 12)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z'))
		{
			wordlegalnum += 1;
		}
		else
			if ((A[i] >= '0'&&A[i] <= '9'))
			{
				numberlegalnum += 1;
			}
	}
	if (numberlegalnum > 0 && wordlegalnum > 0)
	{
		return 1;
	}
	else
		return 0;
}

int admin::realprintall()
{
	printall();
	int i(0);
	cout << "输入任意数字返回" << endl;
	cin >> i;
	return 0;
}



int ktvsystem::pmainmenu()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                                  ｜\n");
	printf("\t\t\t｜  1->用户直达                      ｜\n");
	printf("\t\t\t｜  2->管理员登陆                    ｜\n");
	printf("\t\t\t｜  3->退出系统                      ｜\n");
	printf("\t\t\t｜  请输入选项[]                     ｜\n");
	printf("\t\t\t｜                                  ｜\n");
	printf("\t\t\t＋==============================＋\n");
	fflush(stdin);
	cin >> syoperationnum;
	return syoperationnum;
}

void ktvsystem::run()
{
	initialsys();
	Sleep(1500);
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
		case 1:B.usmenu(A); break;
		case 2:A.login(); break;
		}
	}
}

int ktvsystem::initialsys()
{
//初始化歌曲库读入
	system("cls");
	system("color f1");
	cout << "初始化系统中，请稍后" << endl;
	ifstream infile;
	infile.open("ktvsong.txt");
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	for (int j(1); !infile.eof(); j++)
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.frequence = 0;
		temp.totalscore = 0;
		if (temp.frequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore / temp.frequence;
		temp.serialnum = j;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		A.mysong.push_back(temp);
	}
	A.mysong.pop_back();
	cout << "文件导入成功" << endl;
	return 1;
}



int user::usmenu(admin &A)
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                                     |\n");
	printf("\t\t\t｜ 1->点歌                             |\n");
	printf("\t\t\t｜ 2->置顶                             |\n");
	printf("\t\t\t｜ 3->删除歌曲                         ｜\n");
	printf("\t\t\t｜ 4->评分                             |\n");
	printf("\t\t\t｜ 5->已点歌曲                         ｜\n");
	printf("\t\t\t｜ 6->切歌                             ｜\n");
	printf("\t\t\t｜ 7->退出                             ｜\n");
	printf("\t\t\t｜                                     ｜\n");
	printf("\t\t\t＋==============================＋\n");
	fflush(stdin);
	int adnumtemp = 100;
	while (1)
	{
		cin >> adnumtemp;
		switch (adnumtemp)
		{
		case 1:ordersong(A); break;
		case 2:make_song_top(A); break;
		case 3:delete_song_inqueue(A); break;
		case 4:judge_song(A); break;
		case 5:realsee_playingqueue(A); break;
		case 6:change_song(A);break;
		case 7:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋==============================＋\n");
		printf("\t\t\t｜                                   ｜\n");
		printf("\t\t\t｜ 1->点歌                           ｜\n");
		printf("\t\t\t｜ 2->置顶                           ｜\n");
		printf("\t\t\t｜ 3->删除歌曲                        ｜\n");
		printf("\t\t\t｜ 4->评分                           ｜\n");
		printf("\t\t\t｜ 5->已点歌曲                        ｜\n");
		printf("\t\t\t｜ 6->切歌                           ｜\n");
		printf("\t\t\t｜ 7->退出                           ｜\n");
		printf("\t\t\t｜                                   ｜\n");
		printf("\t\t\t＋==============================＋\n");
		fflush(stdin);
	}
	return 1;
}

int user::ordersong(admin &A)
{
	system("cls");
	system("color f1");
	A.printall();
	cout << "输入你想点的歌曲的编号" << endl;
	int i(0);
	cin >> i;
	if (i<1 || i>A.mysong.size())
	{
		cout << "输入的号码不合法，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	for (int j(0); j < playing_queue.size(); j++)
	{
		if (playing_queue[j] == i)
		{
			cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
	}
	if (i != -1)
	{
		playing_queue.push_back(i);
		cout << "添加成功" << endl;
	}
	cout << "继续点歌？输入1继续，其他键返回" << endl;
	int temp(0);
	cin >> temp;
	if (temp == 1)
	{
		ordersong(A);
		return 1;
	}
	return 1;
		
}

int user::make_song_top(admin &A)
{
	system("cls");
	system("color f1");
	if (playing_queue.size() == 0)
	{
		cout << "空空如也的歌单，先去点首试试？" << endl;
		Sleep(1000);
		return 0;
	}
	cout << "你已经点的歌如下" << endl;
	for (int i(0); i < playing_queue.size(); i++)
	{
		A.printsong(A.mysong[playing_queue[i] - 1]);
	}
	cout << "输入你想置顶的歌曲的编号" << endl;
	int i(0);
	cin >> i;
	if (i<1 || i>A.mysong.size())
	{
		cout << "没有这首歌，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	vector<int>temp;
	playing_queue.insert(playing_queue.begin(),i);
	vector<int>::iterator it;
	for (it = playing_queue.begin(); it != playing_queue.end(); )
	{
		if (*it==i)
		{
			it = playing_queue.erase(it);
		}
		else
		{
			++it;
		}
	}
	cout << "置顶成功" << endl;
	Sleep(2000);
	return 0;
}

int user::delete_song_inqueue(admin&A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	cout << "输入你想删除的歌的编号" << endl;
	int number;
	cin >> number;
	if (number == 0||number>playing_queue.size())
	{
		cout << "输入有误，将会返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	vector<int>::iterator it;
	for (it = playing_queue.begin(); it != playing_queue.end(); )
	{
		if (*it == number)
		{
			it = playing_queue.erase(it);
		}
		else
		{
			++it;
		}
	}
	cout << "删除成功" << endl;
	Sleep(2000);
	return 0;
}

int user::judge_song(admin&A)
{
	int star;
	int IDnum;
	system("cls");
	system("color f1");
	A.printall();
	cout << "输入你要评分的歌曲对应的ID号" << endl;
	cin >> IDnum;
	if (IDnum<1||IDnum>A.mysong.size())
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "输入你的评分，介于1-5分" << endl;
	cin >> star;

	if (star < 1 || star>5)
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	A.mysong[IDnum - 1].totalscore += star;
	A.mysong[IDnum - 1].frequence += 1;
	cout << "评分成功，正在返回上一级" << endl;
	Sleep(2000);
	return 1;

}

int user::see_playingqueue(admin&A)
{
	if (playing_queue.size() == 0)
	{
		cout << "空空如也的歌单，先去点首试试？" << endl;
		Sleep(1000);
		return 0;
	}
	cout << left << setw(15) << "序列号" << "|";
	cout << left << setw(15) << "歌手" << "|";
	cout << left << setw(15) << "歌名" << "|";
	cout << left << setw(15) << "总分" << endl;
	for (int i(0); i < playing_queue.size(); i++)
	{
		A.printsong(A.mysong[playing_queue[i] - 1]);
	}
	return 0;
}

int user::realsee_playingqueue(admin &A)
{
	see_playingqueue(A);
	int i(0);
	cout << "输入任意数字返回" << endl;
	cin >> i;
	return 0;
}

int user::change_song(admin &A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		cout << "准备返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "请输入你想改变的歌曲的编号" << endl;
	int number;
	cin >> number;
	if (number<1 )
	{
		cout << "输入有问题，准备回到上一级" << endl;
		Sleep(2000);
		return 1;
	}
	for (int i(0); i < playing_queue.size(); i++)
	{
		if (number == playing_queue[i])
		{
			A.mysong[number-1].playstatus = 1;
			for (int i(0); i < playing_queue.size(); i++)
			{
				if (playing_queue[i] == number)
					continue;
				A.mysong[playing_queue[i]-1].playstatus = 0;
			}
			cout << "切歌成功，准备返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
	}
	cout << "播放列表没有这首，准备返回上一级" << endl;
	Sleep(2000);
	return 0;
	
}

int main()
{
	ktvsystem cursys;
	cursys.run();
	return 0;
}
