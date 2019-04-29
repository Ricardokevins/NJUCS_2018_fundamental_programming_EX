#pragma once
#include"alldefine.h"
#include"system.h"

class user {
public:
	vector<string>touch_table;//可操作的数据库
	vector<vector<string>>table_power;//对应每一个数据库
	string username;//用户名
	string password;//用户的密码
};
