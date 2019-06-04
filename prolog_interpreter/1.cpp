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
	int annotation_flag(0);
	int atom_flag = 0;
	int infor_in(0);
	int left_small(0);
	int right_small(0);//这里是小括号的匹配
	int left_mid(0);
	int right_mid(0);
	int left_large(0);
	int right_larger(0);
	string temp_infor;
	for (int i=0; i < a.size(); i++)
	{
		if (annotation_flag == 1)
		{
			continue;
		}
		if (a[0] == '/'&&a[1] == '*')//拿到了注释
		{
			annotation_flag = 1;
			continue;
		}
		if (i<(a.size() - 1) && a[i] == '*'&&a[i + 1] == '/')
		{
			annotation_flag = 0;
			continue;
		}
		if ((a[i] <= 'z'&&a[i] >= 'a') || (a[i] >= 'A'&&a[i] <= 'Z') || (a[i] >= '0'&&a[i] <= '9') || (a[i] == '_'))
		{
			temp_infor.push_back(a[i]);
			continue;
		}
		if (a[i] == ' ')
		{
			infor_in = 0;
			temp_infor = "";
			continue;
		}
		if (a[i] == ',')
		{
			infor_in = 0;
			temp_infor = "";
			continue;
		}
	}
}
