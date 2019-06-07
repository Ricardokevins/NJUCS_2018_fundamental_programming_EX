
#include"1.h"

int main()
{
	mysystem cur_system;
	cur_system.run();
	//暂时信息
	cout << "running end" << endl;
	return 0;
}

int mysystem::file_in(string path)
{
	ifstream myoperate;
	path.push_back('.');
	path.push_back('p');
	path.push_back('l');
	const char *I;
	I = path.c_str();
	myoperate.open(I);
	if (myoperate.fail())
	{
		cout << "文件不存在，或者是输入的非法的字符" << endl;

		return 0;
	}
	vector<string> all_command;
	string temp1234;
	int count(1);
	while (getline(myoperate, temp1234))
	{
		cur_infor.push_back(temp1234);
	}
	return 0;
}

int mysystem::run()
{
	zuokuohao = 0;
	youkuohao = 0;
	fuhe = 0;
	juhao = 0;
	douhao = 0;
	int read_wrong(0);
	while (1)
	{
		cout << "-?  ";
		string tmp;
		rewind(stdin);
		getline(cin, tmp);
		if (tmp == "halt.")
			break;
		rewind(stdin);
		delete_start(tmp);
		delete_end(tmp);
		if (check_pair(tmp))
		{
			cout << "至少括号没有配对" << endl;
			continue;
		}
		if (!check_end(tmp))
		{
			cout << "至少没有末尾的结束符" << endl;
			continue;
		}
		string k = "consult";
		if (tmp.size() > 7)
		{

			int flag11(1);
			for (int i(0); i < 7; i++)
			{
				if (k[i] != tmp[i])
				{
					flag11 = 0;
					break;
				}
			}
			if (flag11 != 0)
			{
				int flag12(0);
				int count_delete(0);
				string f = tmp.substr(7, tmp.size() - 7);
				f.pop_back();
				delete_start(f);
				if (f[0] != '(')
				{
					cout << "没有检测到括号，检查输入" << endl;
					continue;
				}
				f.pop_back();
				f.erase(f.begin());
				file_in(f);

				delete_empty(cur_infor);
				for (int i(0); i < cur_infor.size(); i++)
				{
					for (int k(0); k < cur_infor[i].size(); k++)
					{
						if (cur_infor[i][k] == ',')
							douhao++;
						if (cur_infor[i][k] == '.')
							juhao++;
						if (cur_infor[i][k] == ':'&&k < cur_infor[i].size() - 1 && cur_infor[i][k + 1] == '-')
							fuhe++;
						if (cur_infor[i][k] == '(')
							zuokuohao++;
						if (cur_infor[i][k] == ')')
							youkuohao++;
					}
				}
				for (int i(0); i < cur_infor.size();)
				{
					if (find_anno(cur_infor[i]) == -1)
					{
						cout << "词法错误 左右注释符号没有匹配在" << i + count_delete + 1 << "行" << endl;
						read_wrong++;
						cur_infor.erase(cur_infor.begin() + i);
						count_delete++;
						continue;
					}
					if (cur_infor[i].size() == 0)
					{
						delete_empty(cur_infor);
						count_delete++;
					}
					if (check_pair(cur_infor[i]) != 0)
					{
						cout << "语法错误 括号不匹配 在" << i + count_delete + 1 << "行" << endl;
						read_wrong++;
						cur_infor.erase(cur_infor.begin() + i);
						count_delete++;
						continue;
					}
					if (check_end(cur_infor[i]) == 0)
					{
						cout << "语法错误 结尾没有结束符 在" << i + count_delete + 1 << "行" << endl;
						read_wrong++;
						cur_infor.erase(cur_infor.begin() + i);
						count_delete++;
						continue;
					}
					if (check_start(cur_infor[i]) == 0)
					{
						cout << "词法错误 字符不合法 在" << i + count_delete + 1 << "行" << endl;
						read_wrong++;
						cur_infor.erase(cur_infor.begin() + i);
						count_delete++;
						continue;
					}
					if (judge_kind(cur_infor[i]) == 1)
					{
						if (first_check(cur_infor[i]) <= 0)
						{
							read_wrong++;
							cur_infor.erase(cur_infor.begin() + i);

							cout << " 在" << i + count_delete + 1 << "行" << endl;
							count_delete++;
							continue;
						}

					}
					if (judge_kind(cur_infor[i]) != 1)
					{
						if (third_check(cur_infor[i], 0) <= 0)
						{
							read_wrong++;
							cur_infor.erase(cur_infor.begin() + i);
							cout << " 在" << i + count_delete + 1 << "行" << endl;
							count_delete++;
							continue;
						}

					}
					i++;
				}
				if (read_wrong == 0)
					file_out();
				continue;
			}
		}

		if (judge_kind(tmp) != 1)
		{
			if (third_check(tmp, 1) > 0)//说明是成功的使用了这个语句生成了一个relation的对象
			{
				myrelation ask = cur_relation[cur_relation.size() - 1];//那么我就提取出这个对象
				cur_relation.pop_back();//下面就是要基于问题的查询的功能的实现了
				int flag13(0);//这里设置的标志位是为了标志现在的这个语句是查询型的还是确认型，也就是说是否含有变量
				vector<int> va;//设置一个变量保存语句中可能有的变量的名字
				vector<int> answer;//这里是设置了如果有变量的时候就要匹配然后输出对应的答案
				for (int i(0); i < ask.rela_data.size(); i++)
				{
					if (judge_word(cur_token[ask.rela_data[i]].origin) == 2)
					{
						flag13 = 1;
						break;
					}
				}
				int flag16(0);
				if (flag13 == 1)//这里也就是检查到了大写的字母，也就是变量
				{
					for (int i(0); i < cur_relation.size(); i++)
					{
						if (cur_relation[i].name == ask.name)
						{
							int flag14(1);//这个标志位的设置是为了标志说是否已经找到了对应的答案，也就是除了变量之外的所有的信息都是匹配的
							if (ask.rela_data.size() != cur_relation[i].rela_data.size())
							{
								flag14 = 0;
								continue;
							}
							for (int j(0); j < ask.rela_data.size(); j++)
							{
								if (judge_word(cur_token[ask.rela_data[j]].origin) == 2 && judge_word(cur_token[cur_relation[i].rela_data[j]].origin) != 2)
								{
									va.push_back(j);
									continue;//如果是变量的话那就不需要进行匹配
								}
								if (ask.rela_data[j] != cur_relation[i].rela_data[j])
								{
									flag14 = 0;
									break;//检测到了不一致，那么就直接结束
								}
							}
							if (flag14 == 1)//说明这里是成功的匹配上了
							{
								flag16 = 1;
								for (int l(0); l < va.size(); l++)
								{
									answer.push_back(cur_relation[i].rela_data[va[l]]);
								}
								for (int g(0); g < va.size(); g++)
								{
									cout << cur_token[ask.rela_data[va[g]]].origin << " = ";
									cout << cur_token[answer[g]].origin << endl;
									answer.clear();
									va.clear();
								}
							}

						}
					}
					if (!flag16)
					{
						cout << "没有匹配的相关项" << endl;
					}
				L1:					continue;

				}
				else
				{
					for (int i(0); i < cur_relation.size(); i++)
					{
						if (cur_relation[i].name == ask.name)
						{

							int flag14(1);//这个标志位的设置是为了标志说是否已经找到了对应的答案
							if (ask.rela_data.size() != cur_relation[i].rela_data.size())
							{
								flag14 = 0;
								continue;
							}
							for (int j(0); j < ask.rela_data.size(); j++)
							{
								if (ask.rela_data[j] != cur_relation[i].rela_data[j])
								{

									flag14 = 0;
									break;//检测到了不一致，那么就直接结束
								}
							}
							if (flag14 == 1)//说明这里是成功的匹配上了
							{
								cout << "true" << endl;
								goto L2;
							}
						}
					}
					cout << "没有相关问题的匹配项" << endl;
				L2:					continue;
				}
			}
			cout << "指令不合法，没看懂" << endl;
		}
	}

	return 0;
}

int mysystem::take_in(string a, int b)
{
	vector<myrelation>temp_relation;
	if (a[0] <= 'z'&&a[0] >= 'a'&&a[0] != '/');
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
	for (int i = 0; i < a.size(); i++)
	{
		cur_event = detect_event(a[i]);
		if (cur_event == 9 && cur_status != 6)
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
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == '/'&&left_1 == 0)
		{
			if (i < a.size() - 3 && a[i + 1] == '*')
			{
				left_1 = 1;
				left_2 = 1;
				pos = i;
				continue;
			}
		}
		if (a[i] == '*'&&i < a.size() - 1)
		{
			if (a[i + 1] == '/'&&left_1 == 1 && left_2 == 1)
			{
				a.erase(pos, i + 2 - pos);
				left_1 = 0;
				left_2 = 0;
			}
		}
	}
	if (left_1 == 1)
	{
		return -1;
	}
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
			return 3;
	}
	return 2;
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
		while (*a[i].begin() == ' ')
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
	{

		return 1;
	}
	else
		return 0;
}

int mysystem::check_start(string a)
{
	if (a.size() == 0)
	{
		return 1;
	}
	if (a[0] <= 'z'&&a[0] >= 'a')
		return 1;
	else
		return 0;
}

int mysystem::delete_start(string &a)
{
	if (a.size() == 0)//传入空字符串的判断
	{
		return 0;
	}
	while (a[0] == ' ')
	{
		a.erase(a.begin());//去除字符串的头部的可能的空格
		if (a.size() == 0)//传入空字符串的判断
		{
			return 0;
		}
	}
	return 1;
}

int mysystem::delete_end(string &a)
{
	if (a.size() == 0)//传入空字符串的判断
	{
		return 0;
	}
	while (a[a.size() - 1] == ' ')
	{
		a.pop_back();//去除字符串的头部的可能的空格
		if (a.size() == 0)//传入空字符串的判断
		{
			return 0;
		}
	}
	return 1;
}

int mysystem::first_check(string a)
{

	if (a[a.size() - 1] == '.')
	{
		a.pop_back();
	}
	string mrelation;
	int pos1(0);
	int flag1(0);
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == ' ')
			break;
		if (a[i] == '(')//想要先找到这个开头的位置的名词
		{
			pos1 = i;
			flag1 = i;
			break;
		}
	}
	if (flag1 == 0)
	{
		cout << "语法错误 没有找到左括号";
		return -1;
	}
	mrelation = a.substr(0, pos1);
	//test1
	int flag23 = 0;
	flag23 = check_word(mrelation);
	if (flag23 == -1)
	{
		cout << "词法错误 有不合法字符的单词";
		return -5;
	}
	if (flag23 == 0)
	{
		cout << "语法错误 有单词是空的";
		return -6;
	}
	string sub_head;
	int flag2(0);
	int pos2(0);
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == ')')//想要先找到这个开头的位置的名词
		{
			pos2 = i;
			flag2 = i;
			break;
		}
	}
	if (flag2 == 0)
	{
		cout << "没有找到右括号";
		return -2;
	}
	sub_head = a.substr(pos1 + 1, pos2 - pos1 - 1);
	//test2
	/*
	cout << sub_head << endl;//提取得到括号里面的子串
	*/

	vector<string>ini_para1;
	ini_para1 = analyze_bracket(sub_head);
	if (ini_para1.size() == 0)
	{
		cout << "括号中没有信息";
		return -3;//说明没有提取到有用的参数的信息
	}
	for (int i(0); i < ini_para1.size(); i++)
	{
		if (ini_para1[i].size() == 0)//说明在有的逗号之间只有空格
		{
			cout << "逗号中没有信息";
			return -4;
		}
	}
	//test3
	/*
	for (int i(0); i < ini_para1.size(); i++)
	{
		cout << ini_para1[i] << endl;
	}
	cout << endl << endl;
	*/
	double_rela temp6;
	for (int i(0); i < ini_para1.size(); i++)
	{
		int flag3 = 0;
		flag3 = check_word(ini_para1[i]);
		if (flag3 == -1)
		{
			cout << "有不合法字符的单词";
			return -5;
		}
		if (flag3 == 0)
		{
			cout << "有空的单词" << endl;
			return -6;
		}
	}
	for (int i(0); i < ini_para1.size(); i++)
	{
		int small_flag(0);
		for (int j(0); j < cur_token.size(); j++)
		{
			if (ini_para1[i] == cur_token[j].origin)
			{
				cur_token[i].num++;
				small_flag = 1;
				temp6.rela_data.push_back(j);
				break;
			}
		}
		if (!small_flag)
		{
			mytoken temp2;
			temp2.num = 1;
			temp2.order = cur_token.size();
			temp2.origin = ini_para1[i];
			cur_token.push_back(temp2);
			temp6.rela_data.push_back(temp2.order);
		}
	}





	//截至到这里已经就完成了第一个括号的内容的提取
	int pos3(0);
	int flag3(0);//这里是在标记一下“：-”的位置
	for (int i(pos2); i < a.size(); i++)
	{
		if (a[i] == ':')
		{
			if (a[i + 1] == '-')
			{
				pos3 = i;
				flag3 = 1;
				break;
			}
		}
	}
	if (flag3 == 0)
	{
		cout << "没有找到分割符";
		return -7;
	}
	string infor;
	infor = a.substr(pos3 + 2, a.size() - 2 - pos3);
	//cout << "infor                       "<<infor << endl;//这里是已经把复合关系的后面的具体的信息数据都拿到了
	vector<string> ini_para2;//这里是预计对后面的具体的信息进行进一步的分解
	ini_para2 = command_split(infor, ")");

	for (int i(0); i < ini_para2.size(); i++)
	{
		int flag9(0);
		for (int k(0); k < ini_para2[i].size(); )
		{
			if (ini_para2[i][k] == ' ')
			{
				ini_para2[i].erase(ini_para2[i].begin());
			}
			else
			{
				if (ini_para2[i][k] == ',')
				{
					ini_para2[i].erase(ini_para2[i].begin());
					flag9++;
				}
				else
				{
					break;
				}
			}
		}
		if (flag9 > 1)
		{
			cout << "有多余的逗号";
			return -8;
		}
		ini_para2[i].push_back(')');
	}
	int count(0);
	for (int i(0); i < ini_para2.size(); i++)//使用逗号进行分割，结果应该是若干个已经定义好的内容
	{
		delete_end(ini_para2[i]);
		delete_start(ini_para2[i]);
		if (third_check(ini_para2[i], 1) > 0)
		{
			count++;
		}
		else
		{
			return -9;
		}
	}

	temp6.name = mrelation;
	for (int k(0); k < count; k++)
	{
		temp6.double_rela_data.push_back(cur_relation[cur_relation.size() - count + k]);
	}
	cur_double.push_back(temp6);
	return 1;
}

int mysystem::third_check(string a, int q)
{
	if (a.size() == 0)
	{
		cout << "语法错误  输入了空的字符";
	}
	if (a[a.size() - 1] == '.')
	{
		a.pop_back();
	}
	string mrelation;
	int pos1(0);
	int flag1(0);
	for (int i(0); i < a.size(); i++)
	{

		//		if (a[i] == ' ')
			//		break;
		if (a[i] == '(')//想要先找到这个开头的位置的名词
		{
			pos1 = i;
			flag1 = 1;
			break;
		}
	}
	if (flag1 == 0)
	{
		cout << "语法错误 没找到左括号";
		return -1;
	}
	mrelation = a.substr(0, pos1);//这里是关系名字
	int flag13 = 0;
	flag13 = check_word(mrelation);
	if (flag13 == -1)
	{
		cout << "词法错误 有不合法字符的单词";
		return -5;
	}
	if (flag13 == 0)
	{
		cout << "语法错误 有单词是空的";
		return -6;
	}
	//test1
	//cout << mrelation << endl;
	string sub_head;
	int flag2(0);
	int pos2(0);
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] == ')')//想要先找到这个开头的位置的名词
		{
			pos2 = i;
			flag2 = 1;
			break;
		}
	}
	if (flag2 == 0)
	{
		cout << "语法错误 没有找到右括号";
		return -2;
	}
	sub_head = a.substr(pos1 + 1, pos2 - pos1 - 1);//这里是关系的内容
	vector<string>ini_para1;

	ini_para1 = analyze_bracket(sub_head);
	if (ini_para1.size() == 0)
	{
		cout << "语法错误 括号中没有信息";
		return -3;//说明没有提取到有用的参数的信息
	}
	for (int i(0); i < ini_para1.size(); i++)
	{
		if (ini_para1[i].size() == 0)//说明在有的逗号之间只有空格
		{
			cout << "语法错误 逗号之间没有信息";

			return -4;
		}
	}

	for (int i(0); i < ini_para1.size(); i++)
	{
		int flag3 = 0;
		flag3 = check_word(ini_para1[i]);
		if (flag3 == -1)
		{
			cout << "词法错误 有不合法字符的单词";
			return -5;
		}
		if (flag3 == 0)
		{
			cout << "语法错误 有单词是空的";
			return -6;
		}
		int flag100 = judge_word(ini_para1[i]);
		if (flag100 == 2 && q == 0)
		{
			cout << "语法错误 含有参数";
			return -10;
		}
	}

	myrelation temp5;
	temp5.name = mrelation;
	for (int i(0); i < ini_para1.size(); i++)
	{
		int small_flag(0);
		for (int j(0); j < cur_token.size(); j++)
		{
			if (ini_para1[i] == cur_token[j].origin)
			{
				cur_token[i].num++;
				small_flag = 1;
				temp5.rela_data.push_back(j);
				break;
			}
		}
		if (!small_flag)
		{
			mytoken temp2;
			temp2.num = 1;
			temp2.order = cur_token.size();
			temp2.origin = ini_para1[i];
			cur_token.push_back(temp2);
			temp5.rela_data.push_back(temp2.order);
		}
	}
	cur_relation.push_back(temp5);

	return 1;
}

vector<string> mysystem::command_split(const string &s, const string &seperator)
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

vector<string>mysystem::analyze_bracket(string& a)//对括号内的字符串进行切割，然后去掉每一个组分的头尾的空格
{
	vector<string>ini_para1;
	ini_para1 = command_split(a, ",");
	if (ini_para1.size() == 0)
	{
		return ini_para1;//说明没有提取到有用的参数的信息
	}
	for (int i(0); i < ini_para1.size(); i++)
	{
		delete_end(ini_para1[i]);
		delete_start(ini_para1[i]);
	}
	return ini_para1;

}

int mysystem::check_word(string &a)
{
	int legal(1);
	if (a.size() == 0)
		return 0;//代表是空串，方便后面直接用下表进行遍历
	if (a[0] <= 'z'&&a[0] >= 'a')
		legal = 1;
	if (a[0] >= 'A'&&a[0] <= 'Z')
		legal = 2;
	if (legal == 0)
		return -1;
	for (int i(0); i < a.size(); i++)
	{
		if (a[i] <= 'z'&&a[i] >= 'a')
			continue;
		if (a[i] >= 'A'&&a[i] <= 'Z')
			continue;
		if (a[i] >= '0'&&a[i] <= '9')
			continue;
		if (a[i] == '_')
			continue;
		return -1;
	}
	return legal;//返回一说明是小写开头，二是大写开头
}

int mysystem::delete_empty(vector<string>&a)
{
	int count(0);
	for (int i(0); i < a.size();)
	{
		if (a[i].size() == 0)
		{
			count++;
			a.erase(a.begin() + i);
			continue;
		}
		delete_start(a[i]);
		delete_end(a[i]);
		if (a[i].size() == 0)
		{
			a.erase(a.begin() + i);
			count++;
			continue;
		}
		i++;
	}
	return count;
}

int mysystem::test_multi_relation(double_rela a)
{
	cout << "复合关系的名字" << a.name << endl;
	cout << "自己的参数列表是" << endl;
	for (int i(0); i < a.rela_data.size(); i++)
	{
		cout << cur_token[a.rela_data[i]].origin << "--" << endl;
	}
	cout << "复合组分是" << endl;
	for (int i(0); i < a.double_rela_data.size(); i++)
	{
		test_relation(a.double_rela_data[i]);
	}
	return 0;
}

int mysystem::test_relation(myrelation a)
{
	cout << "关系名 " << a.name << endl;
	for (int j(0); j < a.rela_data.size(); j++)
	{
		cout << cur_token[a.rela_data[j]].origin << "--" << endl;
	}
	cout << endl << endl;
	return 0;
}

int mysystem::judge_word(string a)
{
	if (a.size() == 0)
		return 0;
	if (a[0] <= 'z'&&a[0] >= 'a')//小写的字母
		return 1;
	if (a[0] <= 'Z'&&a[0] >= 'A')//大写的字母
		return 2;
	cout << "这个单词是不合法的" << endl;
	return -1;//出现了错误的字符
}

int mysystem::file_out()
{
	ofstream outfile("token.txt");
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
	}
	outfile << "atom " << endl;
	for (int i(0); i < cur_token.size(); i++)
	{
		if (judge_word(cur_token[i].origin) == 1)
		{
			outfile << cur_token[i].origin << endl;
		}
	}
	for (int i(0); i < cur_relation.size(); i++)
	{
		outfile << cur_relation[i].name << endl;
	}
	for (int i(0); i < cur_double.size(); i++)
	{
		outfile << cur_double[i].name << endl;
	}
	outfile << "varible   " << endl;
	for (int i(0); i < cur_token.size(); i++)
	{
		if (judge_word(cur_token[i].origin) == 2)
		{
			outfile << cur_token[i].origin << endl;
		}
	}
	outfile << "symbol   " << endl;
	outfile << ":-" << fuhe << endl;
	outfile << "," << douhao << endl;
	outfile << "." << juhao << endl;
	outfile << "(" << zuokuohao << endl;
	outfile << ")" << youkuohao << endl;

	return 0;
}




