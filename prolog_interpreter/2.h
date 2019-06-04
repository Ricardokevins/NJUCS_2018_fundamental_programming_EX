#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<fstream>
#include<ctime>
#include<cmath>
using namespace std;

class outtoken {//这个是用来记录一下外来引入的那些名词    jingbo  di....
public:
	string origin;//表示的原来的字符
	int order;//记录一下序列号
	int num;//记录一下这个字符是有多少个
};

class mysymbol {//这个是用来记录那一些本来就是在prolog的语法体系中的字符   :-
public:
	string origin;//表示的原来的字符
	int order;;//记录一下序列号
	int num;//记录一下这个字符是有多少个

};

class myerror {//这个是用来记录一下错误的信息的
public:
	int line_num;//记录错误的位置
	int kind;//错误的种类
	string origin;//原来的错误的种类的字符
};

class myrelation {
public:
	vector<vector<int>>rela_data;//预计是使用一个双重的vector来保存某种关系，每一层的vector是一个偏序格
};

class double_rela {
public:
	vector<int>double_rela_data;//保存的是子关系，也就是说这个关系的组成
};

class myvariable {
public:
	string origin;
	int order;
	int num;

};



class mystatus {
public:
	int num;//状态序列号
};

class myevent {
public:
	int num;
	vector<string> cin_event;
};



class mysystem {
public:
	vector<myerror> cur_error;
	vector<mysymbol> cur_symbol;
	vector<outtoken> cur_token;
	vector<myvariable>cur_varible;
	vector<myrelation>cur_relation;
	vector<string> cur_infor;
	int file_in(string path);
	int run();
	int take_in(string a,int b);//这里的a就是这一行的文字信息，b是行数
	int detect_event(char a);
};
