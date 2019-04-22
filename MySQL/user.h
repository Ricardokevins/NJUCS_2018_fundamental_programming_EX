#pragma once
#include"alldefine.h"
#include"system.h"

class user {
public:
	vector<string>touch_table;//可操作的数据库
	vector<vector<string>>table_power;//对应每一个数据库
	vector<string>command_table;//作为子数组保存具体的权限信息，和上面的vector共同构成一个类似于二维数组的东西
	int create(mysystem &mysys);
	int drop();
	int tablelist();
	int insert();
	int mydelete();
	int select();
	int grant();
	int revoke();
	int command_analyse();
	int file_in(string path,mydata &A);
	int  file_out(mydata A);
	vector<string> command_split(const string &s, const string &seperator);
	vector<string> command_spilted;
	int length_command;
	string username;//用户名
	string password;//用户的密码

};
