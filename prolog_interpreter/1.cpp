#include"alldefined.h"

int main()
{
	mysystem cur_system;
	cur_system.run();
	//暂时信息
	int a(0);
	cin >> a;
	return 0;
}

int mysystem::file_in(string path)
{
	ifstream myoperate;
	const char *I;
	I = path.c_str();
	myoperate.open(I);
	if (myoperate.fail())
	{
		cout << "文件不存在" << endl;

		return 0;
	}
	vector<string> all_command;
	string temp1234;
	int count(1);
	while (getline(myoperate, temp1234))
	{
		cur_infor.push_back(temp1234);
	}
	cout << "执行结束" << endl;
	return 0;
}

int mysystem::run()
{
	cout << "haha start test!!!" << endl;
	string mypath;
	cin >> mypath;
	file_in(mypath);
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "file_in test completed" << endl;
	cout << endl;

	for (int i(0); i < cur_infor.size(); i++)
	{
		find_anno(cur_infor[i]);
	}
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "delete test completed!" << endl;
	cout << endl;

	for (int i(0); i < cur_infor.size(); i++)
	{
		if (check_pair(cur_infor[i]) != 0)
			cout << "error !!!!" << endl;
	}
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "check_pair test completed!" << endl;
	cout << endl;

	repair(cur_infor);
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "repair test completed!" << endl;
	cout << endl;

	for (int i(0); i < cur_infor.size();)
	{
		if (check_end(cur_infor[i]) == 0)
		{
			cout << "error !!!!" << endl;
			cur_infor.erase(cur_infor.begin() + i);
		}
		else
			i++;
	}
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "check_end test completed!" << endl;
	cout << endl;


	for (int i(0); i < cur_infor.size();)
	{
		if (check_start(cur_infor[i]) == 0)
		{
			cout << "error !!!!" << endl;
			cur_infor.erase(cur_infor.begin() + i);
		}
		else
			i++;
	}
	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << cur_infor[i] << endl;
	}
	cout << "check_start test completed!" << endl;
	cout << endl;

	for (int i(0); i < cur_infor.size(); i++)
	{
		cout << judge_kind(cur_infor[i]) << endl;
	}
	cout << "judge_kind test completed!" << endl;
	cout << endl;
	return 0;
}

int mysystem::take_in(string a,int b)
{
	vector<myrelation>temp_relation;
	if (a[0] <= 'z'&&a[0] >= 'a'&&a[0]!='/');
	else
	{
		cout << "语法错误，开头不是小写的信息" << endl;
		myerror temp_error;
		temp_error.kind = 1;
		temp_error.line_num = b;
		cur_error.push_back(temp_error);
		return 0;
	}
	int cur_status(0);
	int cur_event(0);
	int left_small(0);
	int right_small(0);//这里是小括号的匹配
	int left_mid(0);
	int right_mid(0);
	int left_large(0);
	int right_larger(0);
	string temp_infor;
	for (int i=0; i < a.size(); i++)
	{
		cur_event = detect_event(a[i]);
		if (cur_event == 9&&cur_status!=6)
		{
			cur_status = 8;
			continue;
		}
		if (cur_event == 10 && cur_status == 8)
		{
			cur_status = 6;
			continue;
		}
		if (cur_event != 10 && cur_status == 8)
		{
			cout << "error" << endl;//这里是只有/，但是下一个字符并不是*的报错
			return 0;
		}
		
	}
}

int mysystem::detect_event(char a)
{
	if (a >= 'a'&&a <= 'z')
		return 1;
	if (a >= 'A'&&a <= 'Z')
		return 2;
	if (a >= '0'&&a <= '9')
		return 3;
	if (a == '(')
		return 4;
	if (a == ')')
		return 5;
	if (a == '_')
		return 6;
	if (a == ':')
		return 7;
	if (a == '-')
		return 8;
	if (a == '/')
		return 9;
	if (a == '*')
		return 10;
	if (a == ' ')
		return 11;
	else
		return 12;
}

int mysystem::find_anno(string &a)//这个函数是去除注释的
{
	int left_1(0);
	int left_2(0);
	int pos(0);
	cout << "now    " << a << endl;
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == '/'&&left_1==0)
		{
			if (i < a.size() - 3&&a[i+1]=='*')
			{
				left_1 = 1;
				left_2 = 1;
				pos = i;
				continue;
			}
		}
		if (a[i] == '*'&&i < a.size() - 1)
		{
			if (a[i + 1] == '/'&&left_1==1&&left_2==1)
			{
				a.erase(pos, i+2);
				left_1 = 0;
				left_2 = 0;
			}
		}
	}
	cout << "after    " << a << endl;
	if (left_1 == 1)
		return -1;

	return 0;
}

int mysystem::check_pair(string &a)
{
	int small_left(0);
	int small_right(0);
	int mid_left(0);
	int mid_right(0);
	int big_left(0);
	int big_right(0);
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == '(')
			small_left++;
		if (a[i] == ')')
			small_right++;
		if (a[i] == '[')
			mid_left++;
		if (a[i] == ']')
			mid_right++;
		if (a[i] == '{')
			big_left++;
		if (a[i] == '}')
			big_right++;
		if (small_right > small_left)
		{
			a.clear();
			return -1;
		}
		if (mid_right > mid_left)
		{
			a.clear();
			return -2;
		}
		if (big_right > big_left)
		{
			a.clear();
			return -3;
		}
	}
	if (small_right != small_left)
	{
		a.clear();
		return -1;
	}
	if (mid_right != mid_left)
	{
		a.clear();
		return -2;
	}
	if (big_right != big_left)
	{
		a.clear();
		return -3;
	}
	return 0;
}

int mysystem::judge_kind(string a)
{
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == ':'&&i < a.size() - 1 && a[i + 1] == '-')//应该是一个multi_relation
			return 1;
	}
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == ',')//应该是一个relation
			return 2;
	}
	return 3;
}

int mysystem::repair(vector<string>&a)
{
	for (int i(0); i < a.size(); )
	{
		if (a[i].size() == 0)
		{
			a.erase(a.begin() + i);
			continue;
		}
		while(*a[i].begin() == ' ')
		{
			a[i].erase(a[i].begin());//去除字符串的头部的可能的空格
		}
		if (a[i].size() == 0)
		{
			a.erase(a.begin() + i);
		}
		else
		{
			i++;
		}
	}
	return 0;
}

int mysystem::check_end(string a)
{
	if (a.size() == 0)
	{
		return 1;
	}
	if (a[a.size() - 1] == '.')
		return 1;
	else
		return 0;
}

int mysystem::check_start(string a)
{
	if (a.size() == 0)
	{
		return 1;
	}
	if (a[0] <= 'z'&&a[0]>='a')
		return 1;
	else
		return 0;
}
