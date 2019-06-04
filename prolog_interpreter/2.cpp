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
