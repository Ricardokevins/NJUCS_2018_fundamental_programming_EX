#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
#include <functional>
#include <conio.h>
#include<cstring> 
#include <stdio.h>
#include<string>
#include<cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <Windows.h>
#pragma once
#include<iomanip>
#include <winbase.h>
using namespace std;

class mydata {
	vector<string> table_head;//0的位置是ID不是数据的一部分
	vector<vector<string>> real_data;//保存的是多行数据、
	vector<string>single_data;//保存单行的数据
	int hrow;//保存的是真实行数
	int lrow;//保存的是真实列数
};

