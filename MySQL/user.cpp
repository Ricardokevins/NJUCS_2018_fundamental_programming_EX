#include"alldefine.h"
#include"user.h"
int user::command_analyse()
{
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
	if (command_spilted[0] == "quit"&&command_spilted.size()==1)
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


int user::create()
{
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
