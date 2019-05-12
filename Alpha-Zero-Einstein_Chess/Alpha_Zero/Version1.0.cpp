#include "Einstein.h"
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<fstream>

using namespace std;

struct chesser {
	int hpos;
	int lpos;
	int chess_id;
	double at_val;
	double def_val;
	double dis_val;
	double thr_val;
	double pro_val;
	double self_val;
};

vector<chesser> All_chess;
int mychessboard[5][5];
int prechessboard[5][5];
int bluechess_num;
int redchess_num;
int mypos;//表示我是蓝方还是红方，1是蓝方，0是红方

bool comp(const chesser&a,const chesser&b)
{
	return a.chess_id < b.chess_id;
}

vector<string> command_split(const string &s, const string &seperator)
{
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;
	while (i != s.size())
	{
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0)
		{
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

Einstein::Einstein()
{
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

int count_pos(chesser &A)
{
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (mychessboard[i][j] == A.chess_id)
			{
				A.hpos = i;
				A.lpos = j;
				return 1;
			}
		}
	}
	return 0;
}

int count_dis(int chess_id)
{
	int dis(All_chess[chess_id].lpos);
	if (chess_id > 6)
	{
		if (All_chess[chess_id].hpos > All_chess[chess_id].lpos)
		{
			dis = All_chess[chess_id].hpos;
		}
		return dis;
	}
	else
	{
		if (All_chess[chess_id].hpos < All_chess[chess_id].lpos)
		{
			dis = All_chess[chess_id].hpos;
		}
		return 4 - dis;
	}
}

int count_num()
{
	for (int i(0); i < All_chess.size(); i++)
	{
		if (All_chess[i].chess_id > 6)
		{
			bluechess_num++;
		}
		else
		{
			redchess_num++;
		}
	}
	return 0;
}

int count_self(int chess_id)
{
	return 0;
}

int count_pro(int chess_id)
{
	int count(0);
	if (chess_id > 6)
	{
		count = bluechess_num;
	}
	else
		count = redchess_num;
	All_chess[chess_id].pro_val = (1.0 / 6.0)*(count + 1);
	return 0;
}

int count_attack(int chess_id)
{
	return 0;
}

int intial_chessboard()
{
	All_chess.clear();
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (mychessboard[i][j] != 0)
			{
				chesser temp;
				temp.chess_id = mychessboard[i][j];
				All_chess.push_back(temp);
			}
		}
	}
	return 0;

}

int record_pre()
{
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			prechessboard[i][j] = mychessboard[i][j];
		}
	}
	return 0;
}

int count_dif()
{
	int num(0);
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			if (prechessboard[i][j] != mychessboard[i][j])
			{
				num++;
			}
		}
	}
	return num;
}

int find_nearest(int mydice)
{
	int pos(All_chess.size()-1);
	for (int i(0); i < All_chess.size(); i++)
	{
		if (All_chess[i].chess_id > 6)
		{
			pos = i;
			break;
		}
	}
	if (mydice > 6)
	{
		for (int i(pos); i < All_chess.size(); i++)
		{
			if (All_chess[i].chess_id >= mydice)
			{
				return i;
			}
		}
		return All_chess.size() - 1;
	}
	else
	{
		for (int i(pos - 1); i >= 0; i--)
		{
			if (All_chess[i].chess_id <= mydice)
			{
				return i;
			}
		}
		return 0;
	}

}

int check_board(int col, int line,int op,int side)//col是列数line是行数
{
	if (side == 0)
	{
		if (op == 0&&col+1>4)
		{
			return 0;
		}
		if (op == 1)
		{
			if (col + 1 > 4 || line + 1 > 4)
			{
				return 0;
			}
		}
		if (op == 2&&line+1>4)
		{
			return 0;
		}
		return 1;
	}
	if (side == 1)
	{
		if (op == 0 && col - 1 < 0)
		{
			return 0;
		}
		if (op == 1)
		{
			if (col - 1 < 0 || line - 1 <0 )
			{
				return 0;
			}
		}
		if (op == 2 && line - 1 < 0)
		{
			return 0;
		}
		return 1;
	}
	return 0;
}

int Einstein::handle()
{
	ofstream outfile("log.txt",ios::app);
	if (!outfile)
	{
		cout << "文件打开失败" << endl;
		return 1;
	}

	clientsocket.recvMsg();
	string s = clientsocket.getRecvMsg();
	parse(s);
	if (dice > 6)
	{
		mypos = 1;
	}
	else
		mypos = 0;
	intial_chessboard();

	if (count_dif() > 2)
	{
		outfile << endl << endl << endl;
	}
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			cout <<setw(3) << mychessboard[i][j] << "  ";
		}
		cout << endl;
	}
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			outfile << mychessboard[i][j] << " ";
		}
		outfile << endl;
	}
	sort(All_chess.begin(), All_chess.end(), comp);
	for (int i(0); i < All_chess.size(); i++)
	{
		count_pos(All_chess[i]);
	}
	for (int i(0); i < All_chess.size(); i++)
	{
		outfile << All_chess[i].chess_id << " ";
	}
	outfile << endl;
	int target = find_nearest(dice);
	string temp;
	temp = to_string(All_chess[target].chess_id);
	string op; 
	op = temp + "|";
	if (check_board(All_chess[target].lpos, All_chess[target].hpos, 1, mypos))
	{
		string temp2;
		if (mypos == 0)
		{
			temp2 = "rightdown";
		}
		else
			temp2 = "leftup";
		op = op + temp2;
	}
	else
	{
		if (check_board(All_chess[target].lpos, All_chess[target].hpos, 0, mypos))
		{
			string temp2;
			if (mypos == 0)
			{
				temp2 = "right";
			}
			else
				temp2 = "left";
			op = op + temp2;
		}
		else
		{
			if (check_board(All_chess[target].lpos, All_chess[target].hpos, 2, mypos))
			{
				string temp2;
				if (mypos == 0)
				{
					temp2 = "down";
				}
				else
					temp2 = "up";
				op = op + temp2;
			}
		}
	}
	const char *hehe = op.c_str();
	cout << "dics" << dice << endl;
	cout << "op" << " " << op << endl;
	outfile << op << endl;
	clientsocket.sendMsg(hehe);
	return 1;
}

int Einstein::parse(std::string A)
{
	A.erase(A.begin());
	int flag_pos(0);
	for (int i(0); i < A.size(); i++)
	{
		if (A[i] == '|')
		{
			flag_pos = i;
			break;
		}
	}
	std::string mydice;
	for (int i(flag_pos+1); i < A.size(); i++)
	{
		mydice.push_back(A[i]);
	}
	stringstream ss;
	ss << mydice;
	ss >> dice;
	vector<string> temp;
	for (int i(A.size() - 1); i >= flag_pos; i--)
	{
		A.pop_back();
	}
	A.pop_back();
	temp = command_split(A, " ");
	for (int i(0); i < temp.size(); i++)
	{
		for (int j(0); j < temp[i].size();)
		{
			int s = temp[i].size();
			if (temp[i][j] == '[' || temp[i][j] == ']' || temp[i][j] == ',' || temp[i][j] == ' ')
			{
				temp[i].erase(temp[i].begin() + j);
			}
			else
				j++;
		}
	}
	for (int i(0); i < 25; i++)
	{
		stringstream sa;
		sa << temp[i];
		sa >> chessboard[i];
	}
	int num(0);
	for (int i(0); i < 5; i++)
	{
		for (int j(0); j < 5; j++)
		{
			mychessboard[i][j] = chessboard[num];
			num++;
		}
	}
	return 0;
}

int Einstein::logging(std::string)
{
	return 1;
}

int Einstein::writelog()
{
	return 0;
}