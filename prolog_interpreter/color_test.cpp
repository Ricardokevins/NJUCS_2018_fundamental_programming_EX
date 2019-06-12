#include <iostream>

using namespace std;

  int main()
  {
      cout << "\033[30m 1 first line" << endl;              //black
      cout << "\033[31m 2 second line " << endl;      // red
      cout << "\033[32m 3 third line " << endl;           // green
      cout << "\033[33m 4 fourth line" << endl;         // yellow
      cout << "\033[34m 5 first line" << endl;            // blue
      cout << "\033[35m 6 second line " << endl;    // purple
      cout << "\033[36m 7 third line " << endl;         //  deep green
      cout << "\033[37m 8 first line" << endl;
      cout << "\033[38m 9 second line " << endl;
      cout << "\033[39m 10 third line " << endl;
      //  这些转义符，其后输出的字体会按照前面定义的颜色进行输出，要改变颜色需要重新使用新的颜色转义字符，或者在句子末尾添加 \033 [ 0m  关闭字体颜色属性

       cout << "颜色:" << endl;
      cout << "\033[0m" << endl;
  
      cout << "\033[34m \033[1m Test gaoliang \033[0m" << endl;       //  变粗了 高亮       可以叠加此类转义字符
      cout << "\033[32m \033[1m \033[4m Test xaihuanxian \033[0m" << endl;
  
     cout << "\033[32m \033[7m   Test fanxain \033[0m" << endl;     // 加了背景色
 
     cout << "\033[34m \033[8m Test input hidden:" << endl;
      //string name;
      //cin >> name;
      cout << "\033[0m";
     

     // 使用一些特殊符号的unicode编码进行输出，并改变其填充颜色 

      cout << "\033[31m \u2764 \u2764 \u2764 \u2764" << endl;  // 心型图标
      cout << "\u2605" << endl;  // 星星
      // 通过复制特殊图片
      cout << "卐" << endl;
  }
