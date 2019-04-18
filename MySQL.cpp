#include<iostream>
#include<vector>
#include<string>
using namespace std;

class user {
public:
	vector<string>touch_table;//可操作的数据库
	vector<vector<int>>table_power;//对应每一个数据库
	vector<int>command_table;//作为子数组保存具体的权限信息，和上面的vector共同构成一个类似于二维数组的东西
	int create();
	int drop();
	int tablelist();
	int insert();
	int mydelete();
	int select();
	int grant();
	int revoke();
private:
	string username;//用户名
	string password;//用户的密码

};

class data {
	vector<string> table_head;//0的位置是ID不是数据的一部分
	vector<vector<string>> real_data;//保存的是多行数据、
	vector<string>single_data;//保存单行的数据
	int hrow;//保存的是真实行数
	int lrow;//保存的是真实列数
};

class system {
	vector<user> cur_user;//保存当前在系统里的用户
	vector<string>table_name;//保存当前存在的数据库名字
	vector<string>file_name;//保存当前存在的文件的名字
	void run();
};
#include"alldefine"
int main()
{
    
}
