#include"alldefine.h"
#include"user.h"
int user::command_analyse()
{
	length_command = command_spilted.size();
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
	if (command_spilted[0] == "quit"&&length_command ==1)
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

vector<string> user::command_split(const string &s, const string &seperator)
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

int user::file_in(string path,mydata &A)
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
	myoperate >> A.lrow;
	myoperate >> A.hrow;
	for (int j(1); !myoperate.eof(); )
	{
		for (int i(0); i < A.lrow + 1; i++)
		{
			string temp;
			myoperate >> temp;
			A.single_data.push_back(temp);
		}
		A.real_data.push_back(A.single_data);
		vector <string>::iterator iter = A.single_data.begin();
		for (; iter != A.single_data.end();)
		{
			iter = A.single_data.erase(iter);
		}
	}
	return 0;
	


}

int user::create(mysystem &mysys)
{
	if (command_spilted[1] == "TABLE"&&length_command>=5)
	{
		if (command_spilted[3] == "FROM")
		{
			if (length_command != 5)
				goto L3;
			string target = command_spilted[2];
			string source = command_spilted[4];
			for (int i(0); i < mysys.file_name.size(); i++)
			{
				if (target == mysys.file_name[i] || source == mysys.table_name[i])
				{
					cout << "文件或者是数据库已经存在" << endl;
					goto L3;
				}
			}
			ifstream loaduser;
			loaduser.open(source);
			mydata A;
			int flag = file_in(source, A);
			if (flag == 1)
			{
				mysys.all_mydata.push_back(A);
				mysys.table_name.push_back(target);
				for (int i(0); i < 4; i++)
				{
					source.pop_back();
				}
				mysys.file_name.push_back(source);
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
				length_command = command_spilted.size();
				if (command_spilted[length_command - 2] != "TO")
					goto L3;
				else
				{
					int length2 = command_spilted[length_command - 3].size();
					if (command_spilted[length_command - 3][length2 - 1] != ')')
						goto L3;
					else
					{
						vector<string> data_para;
						for (int i(3),int j(0); i < length_command - 3; i++,j++)
						{
							data_para[j] = command_spilted[i];
						}
						for (int i(0); i < data_para.size(); i++)
						{
							if (data_para[i][data_para[i].size() - 1] != ',')
							{
								if (i == data_para.size()-1)
									continue;
								else 
								{
									goto L3;
								}
							}
							else
							{
								data_para[i].pop_back();
							}
						}
						int legal(1);
						string target1;//目标表示要创建的数据库的名字
						string source1;//来源表示的是文件的名字
						target1 = command_spilted[3];
						source1 = command_spilted[length_command - 1];
						for (int i(0); i < mysys.file_name.size(); i++)
						{
							if (target1 == mysys.file_name[i] || source1 == mysys.table_name[i])
							{
								cout << "文件或者是数据库已经存在" << endl;
								goto L3;
							}
						}
						ofstream outfile(command_spilted[length_command - 1],ios::out);
						if (!outfile) 
						{
							cout << "创建文件失败" << endl;
							goto L3;
						}
						else
						{
							outfile << mysys.cur_user[mysys.cur_user_ID] << " ";
							outfile << data_para.size() << " ";
							outfile << "0" << endl;
							mysys.cur_user[mysys.cur_user_ID].touch_table.push_back(target1);
							for (int i(0); i < 5; i++)
							{
								mysys.cur_user[mysys.cur_user_ID].command_table.push_back("1");
								mysys.cur_user[mysys.cur_user_ID].table_power.push_back(mysys.cur_user[mysys.cur_user_ID].command_table);
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

int user::drop()
{
	return 0;
}

int user::tablelist()
{
	return 0;
}

int user::insert()
{
	return 0;
}

int user::mydelete()
{
	return 0;
}

int user::select()
{
	return 0;
}

int user::grant()
{
	return 0;
}

int user::revoke()
{
	return 0;
}
