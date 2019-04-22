#pragma once
#include"alldefine.h"
#include"user.h"
class mysystem {
public:
	vector<string> cur_username;//保存当前在系统里的用户
	vector<user>cur_user;
	vector<string>table_name;//保存当前存在的数据库名字
	vector<string>file_name;//保存当前存在的文件的名字
	int cur_user_ID;

	bool login_ornot;

	void run();

	int read_initial_file();

	int load_user();

	int login_user();
};
