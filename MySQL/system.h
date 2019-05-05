#pragma once
#include"alldefine.h"
#include"user.h"

class mysystem {
public:
	friend class user;
	vector<string> cur_username;//保存当前在系统里的用户
	vector<user>cur_user;
	vector<string>table_name;//保存当前存在的数据库名字
	vector<string>file_name;//保存当前存在的文件的名字
	vector<string> command_spilted;
	int length_command;
	vector<mydata>all_mydata;

	vector<string> command_split(const string &s, const string &seperator);

	int cur_user_ID;

	bool login_ornot;

	int initial_file_out();//这个是为了实现文件里intial和内存区的同步

	void run();

	int read_initial_file();

	int update_user_file(int i);

	int load_user();

	int login_user();

	int read_power_file();

	int update_powerfile(int i);

	int exam_power(string A,int file_pos);

	int revoke_power(vector<vector<int>> &A, int grantor, int granted,int file_pos,int power_pos);

	int send_power_req(int power_ID,int file_pos,int user_pos);
	int exam_power_req();
	int multi_file();

	int create();
	int drop();
	int tablelist();
	int insert();
	int mydelete();
	int select();
	int grant();
	int revoke();
	int command_analyse();
	int read_table_file();
	int file_in(string path, mydata &A);
	int  file_out(string path,mydata &A);

};
