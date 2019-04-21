#include"alldefine.h"
#include"system.h"
int mysystem::read_initial_file()
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

}

int mysystem::load_user()
{
	for (int i(0); i < cur_username.size(); i++)
	{
		string path;
		path=cur_username[i];
		path.append(".txt");
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
			for (int j(0); j < 5; j++)
			{
				loaduser >> imfortemp;
				temp.command_table.push_back(imfortemp);
			}
			temp.table_power.push_back(temp.command_table);
			vector <string>::iterator iter = temp.command_table.begin();
			for (; iter != temp.command_table.end();)
			{
				iter = temp.command_table.erase(iter);
			}
		}
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
		string temp;
		cin >> temp;
		if (temp == "mySQL")
		{
			while (!login_user());
			
		}
		
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
				break;
			}
		}

	}
	if (IDflag == 1 && passwordflag == 1)
	{
		cout << "(mysql)==> login successfully";
		printf("\r");
		cout << "                                                                               "; 
		printf("\r");
		cout << "(mysql) == > ";
		return 1;
	}
L1:	cout << "(mysql)==> fail to login";
	printf("\r");
	cout << "                                                                               ";
	printf("\r");
	return 0;
}
