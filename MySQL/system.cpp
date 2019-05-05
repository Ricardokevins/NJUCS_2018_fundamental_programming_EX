#include"alldefine.h"
#include"system.h"


extern bool mycmp_up(vector<string>A, vector<string> B)
{
	return A[A.size() - 1] > B[B.size() - 1];
}
extern bool mycmp_down(vector<string>A, vector<string> B)
{
	return A[A.size() - 1] < B[B.size() - 1];
}

int mysystem::read_initial_file()//打开初始化的文件写入信息
{
	ifstream myoperate;
	myoperate.open("initial.txt");	
	if (myoperate.fail())
	{
		cout << "文件不存在" << endl;
		Sleep(2000);
		return 0;
	}
	int flag = 0;
	for (int j(1); !myoperate.eof(); )
	{
		string temp;
		myoperate >> temp;
		if (temp == "用户") 
		{
			flag = 1;
			myoperate >> temp;
		}
		if (temp == "库名")
		{
			flag = 2;
			myoperate >> temp;
		}
		if (temp == "文件名")
		{
			flag = 3;
			myoperate >> temp;
		}
		if (flag == 0)
			return 0;
		if (flag == 1)
			cur_username.push_back(temp);
		if (flag == 2)
			table_name.push_back(temp);
		if (flag == 3)
			file_name.push_back(temp);
	}
	if (flag == 1)//eof会再次读入一个空的内容，所以要除掉
		cur_username.pop_back();
	if (flag == 2)
		table_name.pop_back();
	if (flag == 3)
		file_name.pop_back();
	myoperate.close();
	return 1;
}

int mysystem::load_user()//根据用户的名字作为文件名打开对应的文件写入信息
{
	for (int i(0); i < cur_username.size(); i++)
	{
		string path;
		path=cur_username[i];
		path.append(".txt");//保存的是用户的名字，后面还要加上txt的后缀哦
		ifstream loaduser;
		loaduser.open(path);
		if (loaduser.fail())
		{
			cout << "文件不存在" << endl;
			Sleep(2000);
			return 0;
		}
		user temp;
		string imfortemp;
		loaduser >> temp.username;
		loaduser >> temp.password;
		for (int j(1); !loaduser.eof(); )
		{
			loaduser >> imfortemp;
			temp.touch_table.push_back(imfortemp);
			vector<string> command_temp;
			for (int j(0); j < 5; j++)
			{
				loaduser >> imfortemp;
				command_temp.push_back(imfortemp);
			}
			temp.table_power.push_back(command_temp);
		}
		temp.touch_table.pop_back();
		temp.table_power.pop_back();
		cur_user.push_back(temp);
	}
	cout << "全部载入完毕" << endl;
	Sleep(2000);
	return 0;
}

void mysystem::run()
{
	read_initial_file();
	load_user();
	read_table_file();
	read_power_file();
	while (1)
	{
		cout << "~$ ";
		string tmp;
		rewind(stdin);
		cin >> tmp;
		if (tmp == "mySQL")
		{
			while (!login_user());
			goto L2;
		}
		return;
	}
L2:	string temp;
	exam_power_req();
	while (1)
	{
		cout << "(mysql)==> ";
		temp = "";
		rewind(stdin);
		getline(cin, temp);
		command_spilted=command_split(temp, " ");
		
		int haha=command_analyse();
		if (haha == 0)
			return;
	}
}

int mysystem::login_user()
{
	cout << "(mysql)==> login:";
	string tempID;
	string temppassword;
	rewind(stdin);
	cin >> tempID;
	int IDflag(0);
	int passwordflag(0);
	for (int i(0); i < cur_user.size(); i++)
	{
		if (tempID == cur_user[i].username)
		{
			IDflag += 1;
			if (IDflag == 0)
				goto L1;
			cout << "(mysql)==> password:";
			char  temp = 's';
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if (temp != '\r'&&temp != '\b'&&temp != '\n')
				{
					putchar('*');
					temppassword += temp;
				}
				if ((temp & 0xff) == 8)
				{
					if (temppassword.length() > 0)
					{
						cout << temp;
						cout << " ";
						cout << temp;
						temppassword.pop_back();
					}
					rewind(stdin);
				}
			}
			cout << endl;
			if (temppassword == cur_user[i].password)
			{
				passwordflag += 1;
				cur_user_ID = i;
				break;
			}
		}

	}
	if (IDflag == 1 && passwordflag == 1)
	{
		cout << "(mysql)==> login successfully";
		Sleep(2000);
		printf("\r");
		cout << "                                                                               "; 
		printf("\r");
		return 1;
	}
L1:	cout << "(mysql)==> fail to login";
	Sleep(2000);
	printf("\r");
	cout << "                                                                               ";
	printf("\r");
	return 0;
}

int mysystem::command_analyse()
{
	length_command = command_spilted.size();
	if (length_command == 0)
		return 1;
	int flag = 0;
	if (command_spilted[0] == "CREATE")
		flag = 1;
	if (command_spilted[0] == "DROP")
		flag = 2;
	if (command_spilted[0] == "TABLE")
		flag = 3;
	if (command_spilted[0] == "INSERT")
		flag = 4;
	if (command_spilted[0] == "DELETE")
		flag = 5;
	if (command_spilted[0] == "SELECT")
		flag = 6;
	if (command_spilted[0] == "GRANT")
		flag = 7;
	if (command_spilted[0] == "REVOKE")
		flag = 8;
	if (command_spilted[0] == "quit"&&length_command == 1)
		flag = 9;
	if (command_spilted[0] == "MULTIFILE")
		flag = 10;
	switch (flag)
	{
	case 1:
		create();
		break;
	case 2:
		drop();
		break;
	case 3:
		tablelist();
		break;
	case 4:
		insert();
		break;
	case 5:
		mydelete();
		break;
	case 6:
		select();
		break;
	case 7:
		grant();
		break;
	case 8:
		revoke();
		break;
	case 9:
		return 0;
		break;
	case 10:
		multi_file();
		break;
	default:
		cout << "输入非法指令" << endl;
	}
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

int mysystem::file_in(string path, mydata &A)//这个函数是用于载入数据库的信息文件
{
	ifstream myoperate;
	myoperate.open(path);
	if (myoperate.fail())
	{
		cout << "文件不存在" << endl;
		Sleep(2000);
		return 0;
	}
	myoperate >> A.owner;
	myoperate >> A.lrow;//lrow就是有多少的列（不包括ID就是新建的那一列）
	myoperate >> A.hrow;//就是有多少行
	for (int i(0); i < A.lrow + 1; i++)
	{
		string temp;
		myoperate >> temp;
		A.table_head.push_back(temp);
	}
	for (int j(1); !myoperate.eof(); )
	{
		vector<string> data_temp;
		for (int i(0); i < A.lrow + 1; i++)
		{
			string temp;
			myoperate >> temp;
			data_temp.push_back(temp);
		}
		A.real_data.push_back(data_temp);
	}
	A.real_data.pop_back();
	return 0;

}

int mysystem::file_out(string path,mydata &A)
{
	ofstream outfile(path);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
		Sleep(2000);
	}
	else
	{
		outfile << A.owner << " ";
		outfile << A.lrow << " ";
		outfile << A.hrow << " ";
		outfile << endl;
		for (int i(0); i < A.table_head.size(); i++)
		{
			outfile << A.table_head[i];
			if (i == A.table_head.size() - 1)
			{
				outfile << endl;
			}
			else
				outfile << " ";
		}
		for (int i(0); i < A.real_data.size(); i++)
		{
			for (int j(0); j < A.real_data[i].size(); j++)
			{
				outfile << A.real_data[i][j];
				if (j == A.real_data[i].size() - 1)
				{
					outfile << endl;
				}
				else
					outfile << " ";
			}
		}
	}
	outfile.close();
	return 0;
}

int mysystem::create()
{
	if (command_spilted[1] == "TABLE"&&length_command >= 5)
	{
		vector<string> data_para;
		length_command = command_spilted.size();//保存一下按照空格分隔的命令的长度
		if (command_spilted[3] == "FROM")
		{
			if (length_command != 5)
				goto L3;
			string target = command_spilted[2];//表示的是库的名字
			string source = command_spilted[4];//表示的是文件的名字
			for (int i(0); i < file_name.size(); i++)
			{
				if (target == file_name[i] || source == table_name[i])
				{
					cout << "文件或者是数据库已经存在" << endl;
					goto L3;//防止重复的建立库 
				}
			}
			ifstream loaduser;
			loaduser.open(source);
			mydata A;
			int flag = file_in(source, A);
			if (flag == 1)
			{
				all_mydata.push_back(A);
				table_name.push_back(target);//开始新建并在系统内存里进行同步
				for (int i(0); i < 4; i++)
				{
					source.pop_back();//删除后面的后缀放入文件库
				}
				file_name.push_back(source);
			}
			else
			{
				cout << "文件打开失败" << endl;
				goto L3;
			}
		}
		else
		{
			if (command_spilted[3][0] != '(')
				goto L3;
			else
			{
				if (command_spilted[length_command - 2] != "TO")
					goto L3;
				else
				{
					int length2 = command_spilted[length_command - 3].size();//按照预定的命令结构进行分析应该是列参数的最后一个进行检验
					if (command_spilted[length_command - 3][length2 - 1] != ')')
						goto L3;
					else
					{
						for (int i = 3; i<= length_command - 3; i++)
						{
							data_para.push_back ( command_spilted[i]);//按照顺序把参数放到数据参数这个数组
						}
						for (int i(0); i < data_para.size(); i++)
						{
							if (data_para[i][data_para[i].size() - 1] != ',')//检查命令的合法是否都是以,结尾的
							{
								
								if (i == data_para.size() - 1)
								{
									data_para[i].pop_back();//是的话就去掉这个逗号
									continue;
								}
								else
								{
									goto L3;
								}
							}
							else
							{
								if (data_para[i][0] == '(')
									data_para[i].erase(0, 1);
								data_para[i].pop_back();//如果是第一个的话就去掉开头的括号
							}
						}
						int legal(1);
						string target1;//目标表示要创建的数据库的名字
						string source1;//来源表示的是文件的名字
						target1 = command_spilted[2];
						source1 = command_spilted[length_command - 1];
						if (source1[source1.size() - 1] == 't'&&source1[source1.size() - 2] == 'x'&&source1[source1.size() - 3] == 't'&&source1[source1.size() - 4] == '.');
						else
							goto L3;
						for (int i(0); i < 4; i++)
						{
							source1.pop_back();//去掉后缀
						}
						for (int i(0); i < file_name.size(); i++)
						{
							if (target1 == table_name[i] || source1 == file_name[i])
							{
								cout << "文件或者是数据库已经存在" << endl;
								goto L3;//比较一下避免重复的建立
							}
						}
						file_name.push_back(source1);//放入系统的内存里
						table_name.push_back(target1);
						ofstream outfile(command_spilted[length_command - 1]);
						if (!outfile)
						{
							cout << "创建文件失败" << endl;
							goto L3;
						}
						else
						{
							outfile << cur_username[cur_user_ID] << " ";//这里是写入拥有着
							outfile << data_para.size() << " ";//这里写入的是列表参数的个数
							outfile << "0" << endl;//新建的列表一定是没有数据的零行的
							cur_user[cur_user_ID].touch_table.push_back(target1);
							vector<string> command_temp;
							for (int i(0); i < 5; i++)
							{
								command_temp.push_back("1");//把所有的权限都是设置为是1因为是拥有着
							}
							cur_user[cur_user_ID].table_power.push_back(command_temp);
							vector<string>temp2;
							for (int i(0); i < 5; i++)
							{
								temp2.push_back("0");//把所有的权限都是设置为是0因为是刚刚创建
							}
							for (int i(0); i < cur_user.size(); i++)
							{
								if (i != cur_user_ID)
								{
									cur_user[i].touch_table.push_back(target1);
									cur_user[i].table_power.push_back(temp2);
								}
							}
							cur_user[cur_user_ID].table_power.push_back(command_temp);
							data_para.insert(data_para.begin(), "ID");//手动的插入这个ID的列表属性
							for (int i(0); i < data_para.size(); i++)
							{
								outfile << data_para[i];
								if (i == data_para.size() - 1)
								{
									outfile << endl;
								}
								else
									outfile << " ";
							}
							initial_file_out();//更新一下初始化的信息的文件
							for (int i(0); i < cur_user.size(); i++)
							{
								update_user_file(i);//这里是更新一下用户的信息的文件，因为新建了一个表
							}
							mydata temp;
							for (int i(0); i < data_para.size(); i++)
							{
								temp.table_head.push_back(data_para[i]);
							}
							temp.owner = cur_username[cur_user_ID];
							temp.hrow = 0;
							temp.lrow = data_para.size() - 1;
							for (int k(0); k < 4; k++)
							{
								vector < vector<int >> temp13;
								for (int i(0); i < cur_user.size(); i++)
								{
									vector<int> temp12;
									for (int j(0); j < cur_user.size(); j++)
									{
										temp12.push_back(0);
									}
									temp13.push_back(temp12);
								}
								temp.mypower.push_back(temp13);
							}
							all_mydata.push_back(temp);
							for (int i(0); i < file_name.size(); i++)
							{
								update_powerfile(i);
							}
						}
					}
				}
			}
		}
	}
	else
		L3:		cout << "指令不合法" << endl;
	Sleep(2000);
	return 0;
}

int mysystem::drop()
{
	int power_flag(0);
	string target;
	if (command_spilted[0] == "DROP"&&command_spilted[1] == "TABLE"&&command_spilted.size()==3)
	{
		target = command_spilted[2];
	}
	else
	{
		cout << "输入的不合法" << endl;
		Sleep(2000);
		return 0;
	}
	int pos2;
	for (int i(0); i < cur_user[cur_user_ID].touch_table.size(); i++)
	{
		if (cur_user[cur_user_ID].touch_table[i] == target)
		{

			pos2 = i;
		}

	}
	int flag = 0;//设置一个标志位来表示是否有这个文件
	int pos = 0;//保存的是地址
	for (int i(0); i < table_name.size(); i++)
	{
		if (table_name[i] == target)
		{
			flag = 1;
			pos = i;
		}
	}
	power_flag = exam_power("DROP", pos);
	if (power_flag <= 0)
	{
		cout << "你没有相关的权限" << endl;
		send_power_req(0, pos, cur_user_ID);
		Sleep(2000);
		return 0;
	}
	if (flag == 1)
	{
		string target2 = file_name[pos];
		string target123 = target2 + "_power.txt";
		target2.push_back('.');
		target2.push_back('t');
		target2.push_back('x');
		target2.push_back('t');
		const char* p = target2.data();
		const char* q = target123.data();
		if (remove(p) == 0&&remove(q)==0)
		{
			cout << "删除成功" << endl;
			table_name.erase(table_name.begin() + pos);
			file_name.erase(file_name.begin() + pos);
			initial_file_out();//更新一下初始化的信息的文件
			for (int i(0); i < cur_user.size(); i++)
			{				
				cur_user[i].touch_table.erase(cur_user[i].touch_table.begin() + pos2);
				cur_user[i].table_power.erase(cur_user[i].table_power.begin() + pos2);
			}
			for (int j(0); j < cur_user.size(); j++)
			{
				update_user_file(j);//这里是更新一下用户的信息的文件，因为新建了一个表
			}
		}
		else
		{
			cout << "删除失败" << endl;
		}
		return 0;
	}
	else
	{
		cout << "没有这个文件" << endl;
		return 0;
	}
	return 0;
}

int mysystem::tablelist()
{
	int totalnum(0);
	vector<int> enable_table;

	int flag(0);
	for (int j(0); j < cur_user[cur_user_ID].touch_table.size(); j++)
	{
		for (int k(0); k < 4; k++)
		{
			if (cur_user[cur_user_ID].table_power[j][k] != "0")
			{
				flag++;
			}
		}
		if (flag > 0)
		{
			enable_table.push_back(j);
		}
	}
	cout << "共有"<<enable_table.size() <<"个"<< endl;
	for (int i(0); i < enable_table.size(); i++)
	{
		cout << cur_user[cur_user_ID].touch_table[enable_table[i]] << " ";
		cout << "(" << all_mydata[enable_table[i]].lrow << "," << all_mydata[enable_table[i]].hrow << ")"<< " ";
		for (int k(0); k < all_mydata[enable_table[i]].table_head.size(); k++)
		{
			cout << all_mydata[enable_table[i]].table_head[k];
			if (k == all_mydata[enable_table[i]].table_head.size() - 1)
			{
				cout << endl;
			}
			else
				cout << " ";
		}
		for (int j(0); j < 5; j++)
		{
			if (cur_user[cur_user_ID].table_power[enable_table[i]][j] != "0")
			{
				if (j == 0)cout << "DROP";
				if (j == 1)cout << "INSERT";
				if (j == 2)cout << "DELETE";
				if (j == 3)cout << "SELECT";
				if (j == 4)cout << "[Owner]" ;
				if (j == 5)cout << endl;
				else
					cout << " ";
			}
		}
	}
	cout << endl;
	return 0;
}

int mysystem::insert()
{
	int power_flag(0);
	int flag6 = 0;//设置一个标志位来表示是否有这个文件
	int pos6= 0;//保存的是地址
	for (int i(0); i < table_name.size(); i++)
	{
		if (table_name[i] == command_spilted[2])
		{
			flag6 = 1;
			pos6 = i;
		}
	}
	if (!flag6)
	{
		cout << "文件不存在" << endl;
		Sleep(2000);
		return 0;
	}
	power_flag = exam_power("INSERT", pos6);
	if (power_flag == 0)
	{
		cout << "你没有相关的权限" << endl;
		Sleep(2000);
		return 0;
	}
	if (command_spilted[0] == "INSERT"&&command_spilted[1] == "INTO");
	else
	{
		cout << "指令不合法" << endl;
		Sleep(2000);
		return 0;
	}
	if (command_spilted[3] == "VALUES")
	{
		string target = command_spilted[2];
		vector<string>data_para;
		for (int i(4); i < command_spilted.size(); i++)
		{
			data_para.push_back(command_spilted[i]);
		}
		if (data_para[0][0] != '(')
		{
			cout << "输入的指令是不合法的" << endl;
			Sleep(2000);
			return 0;
		}
		if (data_para[data_para.size() - 1][data_para[data_para.size() - 1].size() - 1] != ')')
		{
			cout << "输入的指令是不合法的" << endl;
			Sleep(2000);
			return 0;
		}
		for (int i(0); i < data_para.size(); i++)
		{
			if (data_para[i][data_para[i].size() - 1] != ',')//检查命令的合法是否都是以,结尾的
			{

				if (i == data_para.size() - 1)
				{
					data_para[i].pop_back();//是的话就去掉这个逗号
					continue;
				}
				else
				{
					cout << "输入的指令是不合法的" << endl;
					Sleep(2000);
					return 0;
				}
			}
			else
			{
				if (data_para[i][0] == '(')
					data_para[i].erase(0, 1);
				data_para[i].pop_back();//如果是第一个的话就去掉开头的括号
			}
		}
		int flag = 0;//设置一个标志位来表示是否有这个文件
		int pos = 0;//保存的是地址
		for (int i(0); i < table_name.size(); i++)
		{
			if (table_name[i] == target)
			{
				flag = 1;
				pos = i;
			}
		}
		if (flag == 1)
		{
			string target2;
			target2= file_name[pos];
			if (data_para.size() != all_mydata[pos].lrow)
			{
				cout << "输入的指令不合法" << endl;
				Sleep(2000);
				return 0;
			}
			int cur_size = all_mydata[pos].real_data.size();
			vector<string>data_temp;
			string now_temp = to_string(cur_size + 1);
			data_temp.push_back(now_temp);
			all_mydata[pos].hrow++;
			for (int i(0); i < data_para.size(); i++)
			{
				data_temp.push_back(data_para[i]);
			}
			all_mydata[pos].real_data.push_back(data_temp);
			string ini_path = file_name[pos];
			ini_path += ".txt";
			file_out(ini_path, all_mydata[pos]);
		}
		return 0;
	}
	else
	{
		int val_pos(0);
		for (int i(0); i < command_spilted.size(); i++)
		{
			if (command_spilted[i] == "VALUES")
			{
				val_pos = i;
				break;
			}
		}
		if (val_pos < 5)
		{
			cout << "输入有问题" << endl;
			Sleep(2000);
			return 0;
		}
		vector<string>col_para;
		vector<string>val_para;
		string mytarget2;
		mytarget2 = command_spilted[2];
		for (int i(3); i < val_pos; i++)
		{
			col_para.push_back(command_spilted[i]);
		}
		for (int i(val_pos + 1); i < command_spilted.size(); i++)
		{
			val_para.push_back(command_spilted[i]);
		}
		if (val_para.size() != col_para.size())
		{
			cout << "输入有问题" << endl;
			Sleep(2000);
			return 0;
		}
		for (int i(0); i < val_para.size(); i++)
		{
			if (val_para[i][val_para[i].size() - 1] != ',')//检查命令的合法是否都是以,结尾的
			{

				if (i == val_para.size() - 1)
				{
					val_para[i].pop_back();//是的话就去掉这个逗号
					continue;
				}
				else
				{
					cout << "输入的指令是不合法的" << endl;
					Sleep(2000);
					return 0;
				}
			}
			else
			{
				if (val_para[i][0] == '(')
					val_para[i].erase(0, 1);
				val_para[i].pop_back();//如果是第一个的话就去掉开头的括号
			}
		}
		for (int i(0); i < col_para.size(); i++)
		{
			if (col_para[i][col_para[i].size() - 1] != ',')//检查命令的合法是否都是以,结尾的
			{

				if (i == col_para.size() - 1)
				{
					col_para[i].pop_back();//是的话就去掉这个逗号
					continue;
				}
				else
				{
					cout << "输入的指令是不合法的" << endl;
					Sleep(2000);
					return 0;
				}
			}
			else
			{
				if (col_para[i][0] == '(')
					col_para[i].erase(0, 1);
				col_para[i].pop_back();//如果是第一个的话就去掉开头的括号
			}
		}
		int flag2 = 0;//设置一个标志位来表示是否有这个文件
		int pos2 = 0;//保存的是地址
		for (int i(0); i < table_name.size(); i++)
		{
			if (table_name[i] == mytarget2)
			{
				flag2 = 1;
				pos2 = i;
			}
		}
		if (flag2 == 1)
		{
			string target2;
			target2 = file_name[pos2];
			int cur_size = all_mydata[pos2].real_data.size();
			vector<string>data_temp;
			string now_temp = to_string(cur_size + 1);
			data_temp.push_back(now_temp);
			all_mydata[pos2].hrow++;
			/*
			这里是要插入关于在内存里改变数据的内容
			*/
			vector<int>data_pos;
			for (int i(0); i < col_para.size();i++)
			{
				int j(1);
				for (; j < all_mydata[pos2].table_head.size(); j++)
				{
					if (col_para[i] == all_mydata[pos2].table_head[j])
					{
						data_pos.push_back(j);
						break;
					}
				}
			}
			int j(0);
			for (int i(1); i < all_mydata[pos2].table_head.size(); i++)
			{
				if (j != data_pos.size())
				{
					if (i == data_pos[j])
					{
						data_temp.push_back(val_para[j]);
						j++;
					}
					else
					{
						data_temp.push_back("       ");
					}
				}
			}
			all_mydata[pos2].real_data.push_back(data_temp);
			string ini_path = file_name[pos2];
			ini_path += ".txt";
			file_out(ini_path, all_mydata[pos2]);
		}		
	}
	return 0;
}

int mysystem::mydelete()
{
	if (command_spilted[0] == "DELETE" && command_spilted[1] == "FROM"&&command_spilted.size()==7)
	{
		string target;
		target = command_spilted[2];
		if (command_spilted[3] != "WHERE"||command_spilted[5]!="=")
		{
			cout << "输入不合法" << endl;
			Sleep(2000);
			return 0;
		}
		string col;
		string val;
		col = command_spilted[4];
		val = command_spilted[6];
		int flag = 0;//设置一个标志位来表示是否有这个文件
		int pos = 0;//保存的是地址
		for (int i(0); i < table_name.size(); i++)
		{
			if (table_name[i] == target)
			{
				flag = 1;
				pos = i;
			}
		}
		if (!exam_power("DELETE", pos))
		{
			cout << "你没有相关的权限" << endl;
			Sleep(2000);
			return 0;
		}
		if (flag == 0)
		{
			cout << "输入不合法" << endl;
			Sleep(2000);
			return 0;
		}
		int col_pos(0);
		int i(0);
		for (; i < all_mydata[pos].table_head.size(); i++)
		{
			if (all_mydata[pos].table_head[i] == col)
			{
				col_pos = i;
				break;
			}
		}
		if (i == all_mydata[pos].table_head.size())
		{
			cout << "没有这个列表的数据" << endl;
			Sleep(2000);
			return 0;
		}
		for (int i(0); i < all_mydata[pos].real_data.size(); )
		{
			if (all_mydata[pos].real_data[i][col_pos] == val)
			{
				all_mydata[pos].real_data.erase(all_mydata[pos].real_data.begin() + i);
				all_mydata[pos].hrow -= 1;
			}
			else
			{
				i++;
			}
		}
		for (int i(0); i < all_mydata[pos].real_data.size(); i++)
		{
			stringstream ss;
			ss << (i+1);
			string tempID;
			ss >> tempID;
			all_mydata[pos].real_data[i].erase(all_mydata[pos].real_data[i].begin());
			all_mydata[pos].real_data[i].insert(all_mydata[pos].real_data[i].begin(),tempID);
		}
		string ini_path = file_name[pos];
		ini_path += ".txt";
		file_out(ini_path, all_mydata[pos]);		
	}
	else
	{
		if (command_spilted[0] == "DELETE"&&command_spilted[1] == "*"&&command_spilted[2] == "FROM"&&command_spilted.size()==4)
		{
			string target2;
			target2 = command_spilted[3];
			int flag2 = 0;//设置一个标志位来表示是否有这个文件
			int pos2 = 0;//保存的是地址
			for (int i(0); i < table_name.size(); i++)
			{
				if (table_name[i] == target2)
				{
					flag2 = 1;
					pos2 = i;
				}
			}
			if (!exam_power("DELETE", pos2))
			{
				cout << "你没有相关的权限" << endl;
				Sleep(2000);
				return 0;
			}
			if (flag2 == 0)
			{
				cout << "输入不合法" << endl;
				Sleep(2000);
				return 0;
			}
			while (all_mydata[pos2].real_data.size() != 0)
			{
				all_mydata[pos2].real_data.pop_back();
			}
			all_mydata[pos2].hrow = 0;
			string ini_path = file_name[pos2];
			ini_path += ".txt";
			file_out(ini_path, all_mydata[pos2]);
			return 0;
		}
		else
		{
			cout << "输入有问题" << endl;
			Sleep(2000);
			return 0;
		}
	}
	return 0;
}

int mysystem::select()
{
		if (command_spilted[command_spilted.size() - 2] == "FROM"&&command_spilted.size()>4&&command_spilted[1]!="DISTINCT")
		{
			vector<string> col_para;
			for (int i(1); i < command_spilted.size() - 2; i++)
			{
				col_para.push_back(command_spilted[i]);
			}
			for (int i(0); i < col_para.size(); i++)
			{
				if (col_para[i][col_para[i].size() - 1] == ','&& i!=col_para.size()-1)
				{
					col_para[i].pop_back();
				}
			}
			string target;
			target = command_spilted[command_spilted.size() - 1];
			int flag = 0;//设置一个标志位来表示是否有这个文件
			int pos = 0;//保存的是地址
			for (int i(0); i < table_name.size(); i++)
			{
				if (table_name[i] == target)
				{
					flag = 1;
					pos = i;
				}
			}
			if (!exam_power("SELECT", pos))
			{
				cout << "你没有相关的权限" << endl;
				Sleep(2000);
				return 0;
			}
			if (flag == 0)
			{
				cout << "输入不合法" << endl;
				Sleep(2000);
				return 0;
			}
			vector<int>col_pos;//设置一个vector用来保存一下他的要展示的列的位置
			for (int i(0); i < col_para.size(); i++)
			{
				int flag2 = 0;
				for (int j(0); j < all_mydata[pos].table_head.size(); j++)
				{
					if (col_para[i] == all_mydata[pos].table_head[j])
					{
						col_pos.push_back(j);
						flag2 = 1;
						break;
					}
				}
				if (!flag2)
				{
					cout << "输入有问题" << endl;
					Sleep(3000);
					return 0;
				}
				
			}
			for (int i(0); i < col_para.size(); i++)
			{
				cout << col_para[i];
				if (i == col_para.size() - 1)
				{
					cout << endl;
				}
				else
					cout << " ";
			}
			for (int i(0); i < all_mydata[pos].real_data.size(); i++)
			{
				int s(0);
				for (int j(0); i < all_mydata[pos].real_data[i].size(); j++)
				{
					if (s == col_pos.size())
					{
						break;
					}
					if (j == col_pos[s])
					{
						cout << all_mydata[pos].real_data[i][j];
						s++;
						if (s == col_pos.size())
						{
							cout << endl;
						}
						else
						{
							cout << " ";
						}
					}
				}
			}
		}	
		else 
		{
			if (command_spilted[1] == "*"&&command_spilted.size() == 4)
			{
				string target;
				target = command_spilted[command_spilted.size() - 1];
				int flag = 0;//设置一个标志位来表示是否有这个文件
				int pos = 0;//保存的是地址
				for (int i(0); i < table_name.size(); i++)
				{
					if (table_name[i] == target)
					{
						flag = 1;
						pos = i;
					}
				}
				if (!exam_power("SELECT", pos))
				{
					cout << "你没有相关的权限" << endl;
					Sleep(2000);
					return 0;
				}
				if (flag == 0)
				{
					cout << "输入不合法" << endl;
					Sleep(2000);
					return 0;
				}
				for (int i(0); i < all_mydata[pos].table_head.size(); i++)
				{
					cout << all_mydata[pos].table_head[i];
					if (i == all_mydata[pos].table_head.size() - 1)
					{
						cout << endl;
					}
					else
						cout << " ";
				}
				for (int i(0); i < all_mydata[pos].real_data.size(); i++)
				{
					for (int j(0); j < all_mydata[pos].real_data[i].size(); j++)
					{
						cout << all_mydata[pos].real_data[i][j];
						if (j == all_mydata[pos].real_data[i].size() - 1)
						{
							cout << endl;
						}
						else
						{
							cout << " ";
						}
					}
				}
			}
			else
			{
				if (command_spilted[1]=="DISTINCT"&&command_spilted[command_spilted.size()-2]=="FROM")
				{
					string target3;
					target3 = command_spilted[command_spilted.size() - 1];
					int flag = 0;//设置一个标志位来表示是否有这个文件
					int pos = 0;//保存的是地址
					for (int i(0); i < table_name.size(); i++)
					{
						if (table_name[i] == target3)
						{
							flag = 1;
							pos = i;
						}
					}
					if (!exam_power("SELECT", pos))
					{
						cout << "你没有相关的权限" << endl;
						Sleep(2000);
						return 0;
					}
					if (flag == 0)
					{
						cout << "输入不合法" << endl;
						Sleep(2000);
						return 0;
					}
					vector<string>col_para2;//保存的是要进入排列的数据的列
					for (int i(2); i < command_spilted.size() - 2; i++)
					{
						col_para2.push_back(command_spilted[i]);
					}
					for (int i(0); i < col_para2.size(); i++)
					{
						if (col_para2[i][col_para2.size() - 1] == ',')
							col_para2.pop_back();
					}
					vector<int>col_pos2;//记录的是要排列的数据的位置
					int j(0);
					for (; j < col_para2.size(); j++)
					{
						int flag2=0;
						for (int i(0); i < all_mydata[pos].table_head.size(); i++)
						{
							if (all_mydata[pos].table_head[i] == col_para2[j])
							{
								col_pos2.push_back(i);
								j++;
								flag2 = 1;
								break;
							}
						}
						if (!flag2)
						{
							cout << "输入不合法" << endl;
							Sleep(2000);
							return 0;
						}
					}
					vector<vector<string>>data_temp_para;
					for (int i(0); i < col_pos2.size(); i++)//对于每一个等待收集数据的列
					{
						vector<string>data_mytemp;
						for (int j(0); j < all_mydata[pos].real_data.size(); j++)
						{
							int flag3 = 0;
							for (int s(0); s < data_mytemp.size(); s++)//遍历寻找是否有一样的
							{
								if (data_mytemp[s] == all_mydata[pos].real_data[j][col_pos2[i]])
								{
									flag3 = 1;
									break;
								}
							}
							if (!flag3)
							{
								data_mytemp.push_back(all_mydata[pos].real_data[j][col_pos2[i]]);
							}
						}
						data_temp_para.push_back(data_mytemp);
					}
					for (int i(0); i < col_para2.size(); i++)
					{
						cout << col_para2[i];
						if (i == col_para2.size() - 1)
							cout << endl;
						else
							cout << " ";
					}
					for (int i(0); i < data_temp_para.size(); i++)
					{
						for (int j(0); j < data_temp_para[i].size(); j++)
						{
							cout << data_temp_para[i][j];
							if (j == data_temp_para[i].size() - 1)
								cout << endl;
							else
								cout << " ";
						}
					}
					return 0;
				}
				else
				{
					if (command_spilted[1] == "*"&&command_spilted[4] == "ORDER")
					{
						string mode;
						mode = command_spilted[command_spilted.size() - 1];
						string table_target;
						table_target = command_spilted[3];
						int table_flag(0);
						int table_pos(0);
						for (int i(0); i < table_name.size(); i++)
						{
							if (table_name[i] == table_target)
							{
								table_flag = 1;
								table_pos = i;
								break;
							}
						}
						if (!table_flag)
						{
							cout << "没有这个数据库" << endl;
							Sleep(2000);
							return 0;
						}
						string target_col;
						target_col = command_spilted[6];
						int col_pos(0);
						int col_flag(0);
						for (int i(0); i < all_mydata[table_pos].table_head.size(); i++)
						{
							if (all_mydata[table_pos].table_head[i] == target_col)
							{
								col_flag = 1;
								col_pos = i;
								break;
							}
						}
						if (!col_flag)
						{
							cout << "没有这一列" << endl;
							Sleep(2000);
							return 0;
						}
						vector<vector<string>>temp;
						for (int i(0); i < all_mydata[table_pos].real_data.size(); i++)
						{
							vector<string>temp1;
							for (int j(0); j < all_mydata[table_pos].real_data[i].size(); j++)
							{
								temp1.push_back(all_mydata[table_pos].real_data[i][j]);
							}
							temp.push_back(temp1);
						}
						for (int i(0); i < temp.size(); i++)
						{
							temp[i].push_back(temp[i][col_pos]);
						}
						if (mode == "ASC")
						{
							sort(temp.begin(), temp.end(), mycmp_down);
						}
						else
						{
							if (mode == "DESC")
							{
								sort(temp.begin(), temp.end(), mycmp_up);
							}
							else
							{
								cout << "输入的排序模式不正确" << endl;
								Sleep(2000);
								return 0;
							}
						}
						for (int i(0); i < all_mydata[table_pos].table_head.size(); i++)
						{
							cout << all_mydata[table_pos].table_head[i];
							if (i == all_mydata[table_pos].table_head.size() - 1)
							{
								cout << endl;
							}
							else
								cout << " ";
						}
						for (int i(0); i <temp.size(); i++)
						{
							for (int j(0); j < temp[i].size()-1; j++)
							{
								cout <<temp[i][j];
								if (j == temp[i].size() - 2)
								{
									cout << endl;
								}
								else
								{
									cout << " ";
								}
							}
						}
						
					}
					else
					{
						cout << "输入有问题" << endl;
						Sleep(2000);
						return 0;
					}
				}
			}
		}
	return 0;
}

int mysystem::grant()
{	
	int on_pos(0);
	int on_flag(0);//设置的标志位来表示是否找到这个on
	for (int i(0); i < command_spilted.size(); i++)
	{
		if (command_spilted[i] == "on")
		{
			on_pos = i;
			break;
		}
	}
	vector<string>power_temp;
	for (int i(1); i < on_pos; i++)
	{
		power_temp.push_back(command_spilted[i]);
	}
	for (int i(0); i < power_temp.size(); i++)
	{
		if (power_temp[i][power_temp[i].size() - 1] == ',')
		{
			power_temp[i].pop_back();
		}
	}
	string table_target;
	table_target = command_spilted[on_pos + 1];
	if (command_spilted[on_pos + 2] != "to")
	{
		cout << "输入有误，请检查" << endl;
	}
	string user_target;
	user_target = command_spilted[on_pos + 3];
	int table_flag(0);
	int table_pos(0);
	for (int i(0); i < table_name.size(); i++)
	{
		if (table_name[i] == table_target)
		{
			table_flag = 1;
			table_pos = i;
		}
	}
	if (table_flag == 0)
	{
		cout << "没有这个数据库" << endl;
		Sleep(2000);
		return 0;
	}
	int user_pos(0);
	int user_flag(0);
	if (user_target == "public")
	{
		for (int i(0); i < cur_user.size(); i++)
		{
			if (i == cur_user_ID)
				continue;
			user_pos = i;
			for (int i(0); i < power_temp.size(); i++)//对每一个权限进行相关的操作
			{
				int power_ID(0);//判断要操作的是哪个权限
				if (power_temp[i] == "DROP")
					power_ID = 0;
				if (power_temp[i] == "INSERT")
					power_ID = 1;
				if (power_temp[i] == "DELETE")
					power_ID = 2;
				if (power_temp[i] == "SELECT")
					power_ID = 3;
				stringstream ss;
				ss << cur_user[cur_user_ID].table_power[table_pos][power_ID];
				int  power_num(0);
				ss >> power_num;
				if (power_num == 0)
				{
					cout << "你也没有这个权限" << endl;
					Sleep(2000);
					return 0;
				}
				all_mydata[table_pos].mypower[power_ID][cur_user_ID][user_pos] += 1;
				int target_user_power(0);//查看一下这个用户是不是本来就有这个权限
				stringstream sw;
				string temp_power1;
				sw << cur_user[user_pos].table_power[table_pos][power_ID];
				sw >> target_user_power;
				target_user_power += 1;
				stringstream sa;
				sa << target_user_power;
				sa >> temp_power1;
				cur_user[user_pos].table_power[table_pos].erase(cur_user[user_pos].table_power[table_pos].begin() + power_ID);
				cur_user[user_pos].table_power[table_pos].insert(cur_user[user_pos].table_power[table_pos].begin() + power_ID, temp_power1);
				for (int i(0); i < cur_user.size(); i++)
				{
					update_user_file(i);//这里是更新一下用户的信息的文件，因为新建了一个表
				}
				for (int i(0); i < all_mydata.size(); i++)
				{
					update_powerfile(i);
				}
			}
			return 0;
		}
	}
	for (int i(0); i < cur_username.size(); i++)
	{
		if (cur_username[i] == user_target)
		{
			user_pos = i;
			user_flag = 1;
		}
	}
	if (user_flag == 0)
	{
		cout << "没有这个用户" << endl;
		Sleep(2000);
		return 0;
	}
	for (int i(0); i < power_temp.size(); i++)//对每一个权限进行相关的操作
	{
		int power_ID(0);//判断要操作的是哪个权限
		if (power_temp[i] == "DROP")
			power_ID = 0;
		if (power_temp[i] == "INSERT")
			power_ID = 1;
		if (power_temp[i] == "DELETE")
			power_ID = 2;
		if (power_temp[i] == "SELECT")
			power_ID = 3;
		stringstream ss;
		ss << cur_user[cur_user_ID].table_power[table_pos][power_ID];
		int  power_num(0);
		ss >> power_num;
		if (power_num == 0)
		{
			cout << "你也没有这个权限" << endl;
			Sleep(2000);
			return 0;
		}
		all_mydata[table_pos].mypower[power_ID][cur_user_ID][user_pos] += 1;
		int target_user_power(0);//查看一下这个用户是不是本来就有这个权限
		stringstream sw;
		string temp_power1;
		sw << cur_user[user_pos].table_power[table_pos][power_ID];
		sw >> target_user_power;
		target_user_power += 1;
		stringstream sa;
		sa << target_user_power;
		sa >> temp_power1;
		cur_user[user_pos].table_power[table_pos].erase(cur_user[user_pos].table_power[table_pos].begin()+power_ID);
		cur_user[user_pos].table_power[table_pos].insert(cur_user[user_pos].table_power[table_pos].begin()+power_ID, temp_power1);
		for (int i(0); i < cur_user.size(); i++)
		{
			update_user_file(i);//这里是更新一下用户的信息的文件，因为新建了一个表
		}
		for (int i(0); i < all_mydata.size(); i++)
		{
			update_powerfile(i);
		}
	}
	return 0;
}

int mysystem::revoke()
{
	string table_target;
	vector<string> power_target;
	vector<string> user_target;
	vector<int>user_pos;
	vector<int>power_pos;
	int on_pos;
	int on_flag(0);
	for (int i(0); i < command_spilted.size(); i++)
	{
		if (command_spilted[i] == "on")
		{
			on_pos = i;
			on_flag = 1;
			break;
		}
	}
	if (!on_pos)
	{
		cout << "输入的不合法" << endl;
		Sleep(2000);
		return 0;
	}
	table_target = command_spilted[on_pos + 1];
	int table_pos(0);
	int table_flag(0);
	for (int i(0); i < table_name.size(); i++)
	{
		if (table_name[i] == table_target) 
		{
			table_pos = i;
			table_flag = 1;
			break;
		}
	}
	if (!table_flag)
	{
		cout << "没有这个数据库" << endl;
		Sleep(2000);
		return 0;
	}
	for (int i(1); i < on_pos; i++)
	{
		power_target.push_back(command_spilted[i]);
	}
	for (int i(0); i < power_target.size(); i++)
	{
		if (power_target[i][power_target[i].size() - 1] == ',')
		{
			power_target.pop_back();
		}
	}
	for (int i(0); i < power_target.size(); i++)
	{

		if (power_target[i] == "DROP")
			power_pos.push_back(0);
		if (power_target[i] == "INSERT")
			power_pos.push_back(1);
		if (power_target[i] == "DELETE")
			power_pos.push_back(2);
		if (power_target[i] == "SELECT")
			power_pos.push_back(3);

	}
	for (int i(on_pos + 3); i < command_spilted.size(); i++)
	{
		user_target.push_back(command_spilted[i]);
	}
	for (int i(0); i < user_target.size(); i++)
	{
		if (user_target[i][user_target[i].size() - 1] == ',')
		{
			user_target.pop_back();
		}
	}
	for (int j(0); j < user_target.size(); j++)
	{
		int user_flag(0);
		for (int i(0); i < cur_username.size(); i++)
		{
			if (cur_username[i] == user_target[j])
			{
				user_pos.push_back(i);
				user_flag = 1;
			}
		}
		if (!user_flag)
		{
			cout << "输入了不存在的用户" << endl;
			Sleep(2000);
			return 0;
		}
	}
	for (int i(0); i < power_target.size(); i++)
	{
		for (int j(0); j < user_target.size(); j++)
		{
			revoke_power(all_mydata[table_pos].mypower[power_pos[i]], cur_user_ID, user_pos[j], table_pos, power_pos[i]);
		}
	}
	for (int i(0); i < cur_user.size(); i++)
	{
		update_user_file(i);//这里是更新一下用户的信息的文件，因为新建了一个表
	}
	for (int i(0); i < all_mydata.size(); i++)
	{
		update_powerfile(i);
	}
	return 0;
}

int mysystem::initial_file_out()
{
	ofstream outfile("initial.txt", ios::out);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
		goto L4;
	}
	outfile << "用户"<<" ";
	for (int i(0); i < cur_username.size(); i++)
	{
		outfile << cur_username[i];
		if (i == cur_username.size() - 1)
		{
			outfile << endl;
		}
		else
			outfile << " ";
	}
	outfile << "库名" << " ";
	for (int i(0); i < table_name.size(); i++)
	{
		outfile << table_name[i];
		if (i == table_name.size() - 1)
		{
			outfile << endl;
		}
		else
			outfile << " ";
	}
	outfile << "文件名" << " ";
	for (int i(0); i < file_name.size(); i++)
	{
		outfile << file_name[i];
		if (i == file_name.size() - 1)
		{
			outfile << endl;
		}
		else
			outfile << " ";
	}
	outfile.close();
	return 0;
L4:cout << "error !!!" << endl; 
	return 0;
}

int mysystem::update_user_file(int w)
{
	string mytarget=cur_username[w];

	mytarget += ".txt";
	ofstream outfile(mytarget, ios::out);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
		goto L5;
	}
	outfile << cur_user[w].username << " " << cur_user[w].password << endl;
	for (int i(0); i < cur_user[w].touch_table.size(); i++)
	{
		outfile << cur_user[w].touch_table[i] << " ";
		for (int j(0); j <5; j++)
		{
			outfile << cur_user[w].table_power[i][j];
			if (j == 4)
			{
				outfile << endl;
			}
			else
				outfile << " ";
		}
	}
	return 0;
L5:cout << "error" << endl;
	return 0;
}

int mysystem::read_table_file()
{
	for (int i(0); i < file_name.size(); i++)
	{
		mydata temp;
		string path = file_name[i] + ".txt";
		file_in(path, temp);
		all_mydata.push_back(temp);
	}
	return 0;
}

int mysystem::read_power_file()
{
	for (int i(0); i < file_name.size(); i++)
	{
		string path;
		path = file_name[i] + "_power.txt";
		ifstream myoperate;
		myoperate.open(path);
		if (myoperate.fail())
		{
			cout << "文件不存在" << endl;
			Sleep(2000);
			return 0;
		}
		for (int w(0); w < 4; w++)
		{
			vector<vector<int>>temp5;
			for (int k(0); k < cur_user.size(); k++)
			{
				vector<int>temp;
				for (int l(0); l < cur_user.size(); l++)
				{
					int q(0);
					myoperate >> q;
					temp.push_back(q);
				}
				temp5.push_back(temp);
			}
			all_mydata[i].mypower.push_back(temp5);
		}
	}
	return 0;
}

int mysystem::update_powerfile(int i)
{
	string mytarget = file_name[i];
	mytarget += "_power.txt";
	ofstream outfile(mytarget, ios::out);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
		goto L5;
	}
	for (int w(0); w < 4; w++)
	{
		for (int k(0); k < cur_user.size(); k++)
		{
			for (int l(0); l < cur_user.size(); l++)
			{
				outfile << all_mydata[i].mypower[w][k][l];
				if (l == cur_user.size() - 1)
				{
					outfile << endl;
				}
				else
					outfile << " ";
			}
		}
	}
	return 0;
L5:cout << "error" << endl;
	return 0;
}

int mysystem::exam_power(string A,int file_pos)
{
	int power_ID(0);
	if (A == "DROP")
		power_ID = 0;
	if (A == "INSERT")
		power_ID = 1;
	if (A == "DELETE")
		power_ID = 2;
	if (A == "SELECT")
		power_ID = 3;
	int power_temp(0);
	stringstream ss;
	ss << cur_user[cur_user_ID].table_power[file_pos][power_ID];
	ss >> power_temp;
	if (power_temp > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int mysystem::send_power_req(int power_ID, int file_pos, int user_pos)
{
	string target_file;//相关的文件已获取主人
	target_file = file_name[file_pos] + ".txt";
	string owner;
	ifstream myoperate;
	myoperate.open(target_file);
	myoperate >> owner;
	myoperate.close();
	int owner_pos(0);
	for (int i(0); i < cur_user.size(); i++)
	{
		if (cur_username[i] == owner)
		{
			owner_pos = i;
			break;
		}
	}
	string mytarget = "power_req.txt";
	ifstream readoperate;
	readoperate.open(mytarget);
	if (readoperate.fail())
	{
		cout << "文件不存在" << endl;
		Sleep(2000);
		return 0;
	}
	vector<vector<string>>temp;
	
	for (int j(1); !readoperate.eof(); )
	{
		vector<string>temp2;
		for (int i(0); i < 10; i++)
		{
			string temp3;
			readoperate >> temp3;
			temp2.push_back(temp3);
		}
		temp.push_back(temp2);//这里是把所有的请求都读入
	}
	temp.pop_back();
	vector<string>temp4;
	temp4.push_back(owner);
	string power_target;
	if (power_ID == 0)
	{
		power_target = "DROP";
	}
	if (power_ID == 1)
	{
		power_target = "INSERT";
	}
	if (power_ID == 2)
	{
		power_target = "SELECT";
	}
	if (power_ID == 3)
	{
		power_target = "DELETE";
	}
	temp4.push_back(power_target);
	temp4.push_back(file_name[file_pos]);
	temp4.push_back(cur_username[user_pos]);
	time_t t = time(NULL);
	tm *tp = localtime(&t);
	stringstream myyear;
	string myyears;
	stringstream mymonth;
	string mymonths;
	stringstream myday;
	string mydays;
	stringstream myhour;
	string myhours;
	stringstream mymin;
	string mymins;
	stringstream mysecond;
	string myseconds;
	myyear << tp->tm_year + 1900;
	myyear >> myyears;
	mymonth << tp->tm_mon + 1;
	mymonth >> mymonths;
	myday << tp->tm_mday;
	myday >> mydays;
	myhour << tp->tm_hour;
	myhour >> myhours;
	mymin << tp->tm_min;
	mymin >> mymins;
	mysecond << tp->tm_sec;
	mysecond >> myseconds;
	temp4.push_back(myyears);
	temp4.push_back(mymonths);
	temp4.push_back(mydays);
	temp4.push_back(myhours);
	temp4.push_back(mymins);
	temp4.push_back(myseconds);

	temp.push_back(temp4);

	ofstream outfile(mytarget, ios::out);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
	}
	for (int i(0); i < temp.size(); i++)
	{
		for (int j(0); j < temp[i].size(); j++)
		{
			outfile << temp[i][j];
			if (j == temp[i].size() - 1)
				outfile << endl;
			else
			{
				outfile << " ";
			}
		}
	}
	return 0;
}

int mysystem::exam_power_req()
{
	string target_file;
	vector<vector<string>>temp;
	string mytarget = "power_req.txt";
	ifstream readoperate;
	readoperate.open(mytarget);
	for (int j(1); !readoperate.eof(); )
	{
		vector<string>temp2;
		for (int i(0); i < 10; i++)
		{
			string temp3;
			readoperate >> temp3;
			temp2.push_back(temp3);
		}
		temp.push_back(temp2);//这里是把所有的请求都读入
	}
	temp.pop_back();
	vector<vector<string>> temp15;
	for (int i(0); i < temp.size();)
	{
		if (temp[i][0] == cur_username[cur_user_ID])
		{
			cout << temp[i][3] << " request " << temp[i][1] << " on " << temp[i][2];
			for (int l(4); l < temp[i].size(); l++)
			{
				cout << temp[i][l];
				cout << "  ";
			}
			cout << "Granted?[Y/N]" << endl;

			string myoption;
			cin >> myoption;
			if (myoption == "Y")
			{
				string temp100;
				temp100 = "GRANT " + temp[i][1] + " on " + temp[i][2] + " to " + temp[i][3];
				command_spilted = command_split(temp100, " ");
				grant();
				temp.erase(temp.begin() + i);
			}
			else
				i++;
		}
		else
			i++;
	}
	ofstream outfile(mytarget, ios::out);
	if (!outfile)
	{
		cout << "创建文件失败" << endl;
	}
	for (int i(0); i < temp.size(); i++)
	{
		for (int j(0); j < temp[i].size(); j++)
		{
			outfile << temp[i][j];
			if (j == temp[i].size() - 1)
				outfile << endl;
			else
			{
				outfile << " ";
			}
		}
	}
	return 0;
}

int mysystem::revoke_power(vector<vector<int>>&A, int grantor, int granted,int file_pos,int power_pos)
{
	int power_num = A[grantor][granted];
	A[grantor][granted] = 0;
	stringstream ss;
	ss << cur_user[granted].table_power[file_pos][power_pos];
	int temp_power_num(0);
	ss >> temp_power_num;
	temp_power_num -= power_num;
	stringstream sa;
	sa << temp_power_num;
	string temp;
	sa >> temp;
	cur_user[granted].table_power[file_pos].erase(cur_user[granted].table_power[file_pos].begin() + power_pos);
	cur_user[granted].table_power[file_pos].insert(cur_user[granted].table_power[file_pos].begin() + power_pos,temp);
	if (temp_power_num != 0)//说明他还有权限，那就停止
	{
		return 1;
	}//他已经没有了权限，那就看看他对于哪一些的人进行的了授权，依次的递归继续收回权限
	for (int i(0); i < all_mydata[file_pos].mypower[power_pos][granted].size(); i++)
	{
		if (all_mydata[file_pos].mypower[power_pos][granted][i] != 0)
		{
			revoke_power(A, granted, i, file_pos, power_pos);
		}
	}
	return 0;


}

int mysystem::multi_file()
{
	string file_path;
	file_path=command_spilted[1];
	ifstream myoperate;
	myoperate.open(file_path);
	if (myoperate.fail())
	{
		cout << "文件不存在" << endl;
		Sleep(2000);
		return 0;
	}
	vector<string> all_command;
	string temp1234;
	int count(1);
	while (getline(myoperate, temp1234))
	{
		cout << "正在执行第 " << count << " 条" << endl;
		count++;
		command_spilted = command_split(temp1234, " ");
		int haha1 = command_analyse();
		if (haha1 == 0)
			return 0;
	}
	return 0;
}
