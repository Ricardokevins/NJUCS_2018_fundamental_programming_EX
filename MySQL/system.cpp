#include"alldefine.h"
#include"system.h"

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
	default:
		cout << "输入非法指令" << endl;
		cout << "(mysql)==> ";
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

int mysystem::file_in(string path, mydata &A)
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
									cur_user[i].table_power.push_back(command_temp);
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
			if (cur_user[cur_user_ID].table_power[i][0] == "1")
			{
				pos2 = i;
			}
			else
			{
				cout << "没有相关权限" << endl;
				Sleep(2000);
				return 0;
			}
		}
		else
		{
			cout << "没有相关权限" << endl;
			Sleep(2000);
			return 0;
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
		string target2 = file_name[pos];
		target2.push_back('.');
		target2.push_back('t');
		target2.push_back('x');
		target2.push_back('t');
		const char* p = target2.data();
		if (remove(p) == 0)
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
	cout << "共有"<<cur_user[cur_user_ID].touch_table.size() <<"个"<< endl;
	for (int i(0); i < cur_user[cur_user_ID].touch_table.size(); i++)
	{
		cout << cur_user[cur_user_ID].touch_table[i] << " ";
		for (int j(0); j < 5; j++)
		{
			if (cur_user[cur_user_ID].table_power[i][j] == "1")
			{
				if (j == 0)cout << "DROP";
				if (j == 1)cout << "INSERT";
				if (j == 2)cout << "DELETE";
				if (j == 3)cout << "SELECT";
				if (j == 4)cout << "owner" ;
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
	return 0;
}

int mysystem::mydelete()
{
	return 0;
}

int mysystem::select()
{
	return 0;
}

int mysystem::grant()
{
	return 0;
}

int mysystem::revoke()
{
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


