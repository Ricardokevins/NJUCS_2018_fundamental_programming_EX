#include "Einstein.h"
#include<vector>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<algorithm>
#include<cstring>
using namespace std;
int TOTAL_NODE;//总结点数
int YOUR_CHOICE_RED_WINS;
int YOUR_CHOICE_BLUE_WINS;
struct ARREYANDIJ
{
	int value;
	int i;
	int j;
};
int string_to_int(string str);
string int_to_string(int num);
void copyarrey(int a[][5],int b[][5])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			b[i][j] = a[i][j];
		}
	}
}
int get_a_rand(int a,int b)
{
	return (rand() % (b - a + 1)) + a;
}
int getrootcolor(int dice)
{
	if(dice<=6&&dice>=1)
	{
		return 0;
	}
	else if(dice<=12&&dice>=7)
	{
		return 1;
	}
}
int rootcolor = 0;
int jud_end(const int cb[][5])
{
	//1表示蓝赢，0表示红赢，-1表示没有结束
	if(cb[0][0]<=12&&cb[0][0]>=7)
	{
		return 1;
	}
	if(cb[4][4]<=6&&cb[4][4]>=1)
	{
		return 0;
	}
	int bluenum = 0;
	for (int i = 0; i < 5; i++)
	{
		int flag = 0;
		for (int j = 0; j < 5; j++)
		{
			if (cb[i][j] <= 12 && cb[i][j] >= 7)
			{
				bluenum++;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (bluenum == 0)return 0;
	int rednum = 0;
	for(int i=0;i<5;i++)
	{
		int flag = 0;
		for(int j=0;j<5;j++)
		{
			if (cb[i][j] <= 6 && cb[i][j] >= 1)
			{
				rednum++;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (rednum == 0)return 1;
	return -1;
}
void bluego(int cb[][5])
{
	int bluedice = get_a_rand(7, 12);//得到蓝色方的骰子
	int biggestsmall = -1, bsi = -1, bsj = -1, smallestbig = -1, sbi = -1, sbj = -1;
	int equali = -1, equalj = -1;
	for(int i=0;i<5;i++)
	{
		int flag = 0;
		for(int j=0;j<5;j++)
		{
			if(cb[i][j]==bluedice)
			{
				equali = i;
				equalj = j;
				flag = 1;
				break;
			}
			if (cb[i][j]<bluedice&&cb[i][j]>biggestsmall&&cb[i][j] <= 12 && cb[i][j] >= 7)
			{
				biggestsmall = cb[i][j];
				bsi = i;
				bsj = j;
			}
			if (cb[i][j] > bluedice && cb[i][j] < smallestbig&&cb[i][j] <= 12 && cb[i][j] >= 7)
			{
				smallestbig = cb[i][j];
				sbi = i;
				sbj = j;
			}
		}
		if (flag == 1)break;
	}
	if(equali!=-1)
	{
		//有与骰子相同的棋子
		if (equali != 0 && equalj != 0)
		{
			//有三个方向可走
			int direction = get_a_rand(1, 3);
			if(direction==1)
			{
				cb[equali - 1][equalj] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
			if(direction==2)
			{
				cb[equali][equalj-1] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
			if(direction==3)
			{
				cb[equali - 1][equalj - 1] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
		}
		else if(equali==0&&equalj!=0)
		{
			//只能往左走
			cb[equali][equalj - 1] = cb[equali][equalj];
			cb[equali][equalj] = 0;
		}
		else if (equali != 0 && equalj == 0)
		{
			//只能往上走
			cb[equali - 1][equalj] = cb[equali][equalj];
			cb[equali][equalj] = 0;
		}
	}
	else
	{
		//没有与骰子相同的棋子
		int smallorbig = get_a_rand(1, 2);
		if(smallorbig==1&&bsi!=-1)
		{
			//走小的
			if (bsi != 0 && bsj != 0)
			{
				//有三个方向可走
				int direction = get_a_rand(1, 3);
				if (direction == 1)
				{
					cb[bsi - 1][bsj] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
				if (direction == 2)
				{
					cb[bsi][bsj - 1] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
				if (direction == 3)
				{
					cb[bsi - 1][bsj - 1] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
			}
			else if (bsi == 0 && bsj != 0)
			{
				//只能往左走
				cb[bsi][bsj - 1] = cb[bsi][bsj];
				cb[bsi][bsj] = 0;
			}
			else if (bsi != 0 && bsj == 0)
			{
				//只能往上走
				cb[bsi - 1][bsj] = cb[bsi][bsj];
				cb[bsi][bsj] = 0;
			}
		}
		else if(smallorbig==2&&sbi!=-1)
		{
			//走大的
			if (sbi != 0 && sbj != 0)
			{
				//有三个方向可走
				int direction = get_a_rand(1, 3);
				if (direction == 1)
				{
					cb[sbi - 1][sbj] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
				if (direction == 2)
				{
					cb[sbi][sbj - 1] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
				if (direction == 3)
				{
					cb[sbi - 1][sbj - 1] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
			}
			else if (sbi == 0 && sbj != 0)
			{
				//只能往左走
				cb[sbi][sbj - 1] = cb[sbi][sbj];
				cb[sbi][sbj] = 0;
			}
			else if (sbi != 0 && sbj == 0)
			{
				//只能往上走
				cb[sbi - 1][sbj] = cb[sbi][sbj];
				cb[sbi][sbj] = 0;
			}
		}
	}
}
void redgo(int cb[][5])
{
	int reddice = get_a_rand(1, 6);//得到红色方的骰子
	int biggestsmall = -1, bsi = -1, bsj = -1, smallestbig = -1, sbi = -1, sbj = -1;
	int equali = -1, equalj = -1;
	for (int i = 0; i < 5; i++)
	{
		int flag = 0;
		for (int j = 0; j < 5; j++)
		{
			if (cb[i][j] == reddice)
			{
				equali = i;
				equalj = j;
				flag = 1;
				break;
			}
			if (cb[i][j]<reddice&&cb[i][j]>biggestsmall&&cb[i][j] <= 6 && cb[i][j] >= 1)
			{
				biggestsmall = cb[i][j];
				bsi = i;
				bsj = j;
			}
			if (cb[i][j] > reddice && cb[i][j] < smallestbig&&cb[i][j] <= 6 && cb[i][j] >= 1)
			{
				smallestbig = cb[i][j];
				sbi = i;
				sbj = j;
			}
		}
		if (flag == 1)
			break;
	}
	if (equali != -1)
	{
		//有与骰子相同的棋子
		if (equali != 4 && equalj != 4)
		{
			//有三个方向可走
			int direction = get_a_rand(1, 3);
			if (direction == 1)
			{
				cb[equali + 1][equalj] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
			if (direction == 2)
			{
				cb[equali][equalj + 1] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
			if (direction == 3)
			{
				cb[equali + 1][equalj + 1] = cb[equali][equalj];
				cb[equali][equalj] = 0;
			}
		}
		else if (equali == 4 && equalj != 4)
		{
			//只能往右走
			cb[equali][equalj + 1] = cb[equali][equalj];
			cb[equali][equalj] = 0;
		}
		else if (equali != 4 && equalj == 4)
		{
			//只能往下走
			cb[equali + 1][equalj] = cb[equali][equalj];
			cb[equali][equalj] = 0;
		}
	}
	else
	{
		//没有与骰子相同的棋子
		int smallorbig = get_a_rand(1, 2);
		if (smallorbig == 1&&bsi!=-1)
		{
			//走小的
			if (bsi != 4 && bsj != 4)
			{
				//有三个方向可走
				int direction = get_a_rand(1, 3);
				if (direction == 1)
				{
					cb[bsi + 1][bsj] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
				if (direction == 2)
				{
					cb[bsi][bsj + 1] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
				if (direction == 3)
				{
					cb[bsi + 1][bsj + 1] = cb[bsi][bsj];
					cb[bsi][bsj] = 0;
				}
			}
			else if (bsi == 4 && bsj != 4)
			{
				//只能往左走
				cb[bsi][bsj + 1] = cb[bsi][bsj];
				cb[bsi][bsj] = 0;
			}
			else if (bsi != 4 && bsj == 4)
			{
				//只能往上走
				cb[bsi + 1][bsj] = cb[bsi][bsj];
				cb[bsi][bsj] = 0;
			}
		}
		else if (smallorbig == 2&&sbi!=-1)
		{
			//走大的
			if (sbi != 4 && sbj != 4)
			{
				//有三个方向可走
				int direction = get_a_rand(1, 3);
				if (direction == 1)
				{
					cb[sbi + 1][sbj] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
				if (direction == 2)
				{
					cb[sbi][sbj + 1] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
				if (direction == 3)
				{
					cb[sbi + 1][sbj + 1] = cb[sbi][sbj];
					cb[sbi][sbj] = 0;
				}
			}
			else if (sbi == 4 && sbj != 4)
			{
				//只能往左走
				cb[sbi][sbj + 1] = cb[sbi][sbj];
				cb[sbi][sbj] = 0;
			}
			else if (sbi != 4 && sbj == 4)
			{
				//只能往上走
				cb[sbi + 1][sbj] = cb[sbi][sbj];
				cb[sbi][sbj] = 0;
			}
		}
	}
}
long double vucb(int nodewin,int nodegame,int allnodegame)
{
	return (long double)(((long double)nodewin / (long double)nodegame) + (long double)1.38*(long double)sqrt((2 * log((long double)allnodegame)) / (long double)nodegame));
}
long double vucbrtn(int nodewin, int nodegame, int allnodegame)
{
	return (long double)(((long double)nodewin / (long double)nodegame));// +(long double)1.38*(long double)sqrt((2 * log((long double)allnodegame)) / (long double)nodegame));
}


class CHESSBOARD
{public:
	int cb_of_CHESSBOARD[5][5];
	//int proornot;
	CHESSBOARD(int cb_noclass[5][5]);
	CHESSBOARD();
};
CHESSBOARD::CHESSBOARD(int cb_noclass[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cb_of_CHESSBOARD[i][j] = cb_noclass[i][j];
		}
	}
	//proornot = -1;
}
CHESSBOARD::CHESSBOARD()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cb_of_CHESSBOARD[i][j] = 0;
		}
	}
}



class NODE
{public:
	NODE* parent;//父结点
	vector<NODE*> children;//子结点
	CHESSBOARD chessboard;//结点对应的棋盘
	vector<CHESSBOARD> prochessboard;//用一个数组存储可拓展的棋盘
	int gamenum;//总对局数
	int redwinnum;//red总胜场数
	int bluewinnum;//blue
	int redderta;//单场的胜负情况,red方胜利为1，我方失败为0
	int bluederta;//              blue
	int color;//红色为0，蓝色为1
	int rootdice;
	//int rootcolor;
	NODE();
	//int getrootcolor(int dice);
	void backup(NODE* node);//回溯
	vector<CHESSBOARD> get_procb(NODE* node);//得到可拓展的棋盘
	int simulate(const int cb1[][5]);//模拟棋局的函数，返回的是derta
	int jud_if_node_is_endnode(NODE*node);//判断是否为终止结点
};
NODE::NODE()
{
	parent = NULL;
	gamenum = 0;
	redwinnum = 0;
	redderta = 0;
	bluewinnum = 0;
	bluederta = 0;
	color = -1;
	//rootcolor = getrootcolor(dice);
}
vector<CHESSBOARD> NODE::get_procb(NODE*node)
{
	vector<CHESSBOARD> rtn;
	if (node != NULL && node->parent == NULL)
	{
		//node是根结点，则可拓展棋盘由dice决定
		int biggestsmall = -1, bsi = -1, bsj = -1, smallestbig = 13, sbi = -1, sbj = -1;
		int equali = -1, equalj = -1;
		int bounce1, bounce2;
		if(rootdice<=6&&rootdice>=1)
		{
			bounce1 = 1;
			bounce2 = 6;
		}
		else 
		{
			bounce1 = 7;
			bounce2 = 12;
		}
		for (int i = 0; i < 5; i++)
		{
			int flag = 0;
			for (int j = 0; j < 5; j++)
			{
				if (node->chessboard.cb_of_CHESSBOARD[i][j] == rootdice)
				{
					equali = i;
					equalj = j;
					flag = 1;
					break;
				}
				else if (node->chessboard.cb_of_CHESSBOARD[i][j] < rootdice && node->chessboard.cb_of_CHESSBOARD[i][j] > biggestsmall && chessboard.cb_of_CHESSBOARD[i][j] >= bounce1&&chessboard.cb_of_CHESSBOARD[i][j] <= bounce2)
				{
					biggestsmall = node->chessboard.cb_of_CHESSBOARD[i][j];
					bsi = i;
					bsj = j;
				}
				else if (node->chessboard.cb_of_CHESSBOARD[i][j] > rootdice && node->chessboard.cb_of_CHESSBOARD[i][j] < smallestbig && chessboard.cb_of_CHESSBOARD[i][j] >= bounce1 && chessboard.cb_of_CHESSBOARD[i][j] <= bounce2)
				{
					smallestbig = node->chessboard.cb_of_CHESSBOARD[i][j];
					sbi = i;
					sbj = j;
				}
			}
			if (flag == 1)
				break;
		}
		if (equali != -1)
		{
			//有与骰子点数相同的棋
			if (rootcolor == 0)
			{//红色方
				int r[5][5];
				int d[5][5];
				int rd[5][5];
				copyarrey(node->chessboard.cb_of_CHESSBOARD, r);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, d);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, rd);
				if (equali != 4 && equalj != 4)
				{
					//有三个方向可走
					r[equali][equalj + 1] = r[equali][equalj];
					r[equali][equalj] = 0;
					d[equali + 1][equalj] = d[equali][equalj];
					d[equali][equalj] = 0;
					rd[equali + 1][equalj + 1] = rd[equali][equalj];
					rd[equali][equalj] = 0;
					CHESSBOARD CBr(r);
					CHESSBOARD CBd(d);
					CHESSBOARD CBrd(rd);
					rtn.push_back(CBr);
					rtn.push_back(CBd);
					rtn.push_back(CBrd);
				}
				else if (equali != 4 && equalj == 4)
				{
					//到最右边，只能往下走
					d[equali + 1][equalj] = d[equali][equalj];
					d[equali][equalj] = 0;
					CHESSBOARD CBd(d);
					rtn.push_back(CBd);
				}
				else if (equali == 4 && equalj != 4)
				{
					//到最下边，只能往右走
					r[equali][equalj + 1] = r[equali][equalj];
					r[equali][equalj] = 0;
					CHESSBOARD CBr(r);
					rtn.push_back(CBr);
				}
			}
			else if (rootcolor == 1)
			{//蓝色方
				int l[5][5];
				int u[5][5];
				int lu[5][5];
				copyarrey(node->chessboard.cb_of_CHESSBOARD, l);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, u);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, lu);
				if (equali != 0 && equalj != 0)
				{
					//有三个方向可走
					l[equali][equalj - 1] = l[equali][equalj];
					l[equali][equalj] = 0;
					u[equali - 1][equalj] = u[equali][equalj];
					u[equali][equalj] = 0;
					lu[equali - 1][equalj - 1] = lu[equali][equalj];
					lu[equali][equalj] = 0;
					CHESSBOARD CBl(l);
					CHESSBOARD CBu(u);
					CHESSBOARD CBlu(lu);
					rtn.push_back(CBl);
					rtn.push_back(CBu);
					rtn.push_back(CBlu);
				}
				else if (equali != 0 && equalj == 0)
				{
					//到最左边，只能往上走
					u[equali - 1][equalj] = u[equali][equalj];
					u[equali][equalj] = 0;
					CHESSBOARD CBu(u);
					rtn.push_back(CBu);
				}
				else if (equali == 0 && equalj != 0)
				{
					//到最上边，只能往左走
					l[equali][equalj - 1] = l[equali][equalj];
					l[equali][equalj] = 0;
					CHESSBOARD CBl(l);
					rtn.push_back(CBl);
				}
			}

		}
		else
		{
			//没有与骰子相同点数的棋
			//此时最多6种拓展
			if(bsi!=-1)
			{
				//存在biggestsmall
				if (rootcolor == 0)
				{//红色方
					int r[5][5];
					int d[5][5];
					int rd[5][5];
					copyarrey(node->chessboard.cb_of_CHESSBOARD, r);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, d);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, rd);
					if (bsi != 4 && bsj != 4)
					{
						//有三个方向可走
						r[bsi][bsj + 1] = r[bsi][bsj];
						r[bsi][bsj] = 0;
						d[bsi + 1][bsj] = d[bsi][bsj];
						d[bsi][bsj] = 0;
						rd[bsi + 1][bsj + 1] = rd[bsi][bsj];
						rd[bsi][bsj] = 0;
						CHESSBOARD CBr(r);
						CHESSBOARD CBd(d);
						CHESSBOARD CBrd(rd);
						rtn.push_back(CBr);
						rtn.push_back(CBd);
						rtn.push_back(CBrd);
					}
					else if (bsi != 4 && bsj == 4)
					{
						//到最右边，只能往下走
						d[bsi + 1][bsj] = d[bsi][bsj];
						d[bsi][bsj] = 0;
						CHESSBOARD CBd(d);
						rtn.push_back(CBd);
					}
					else if (bsi == 4 && bsj != 4)
					{
						//到最下边，只能往右走
						r[bsi][bsj + 1] = r[bsi][bsj];
						r[bsi][bsj] = 0;
						CHESSBOARD CBr(r);
						rtn.push_back(CBr);
					}
				}
				else if (rootcolor == 1)
				{//蓝色方
					int l[5][5];
					int u[5][5];
					int lu[5][5];
					copyarrey(node->chessboard.cb_of_CHESSBOARD, l);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, u);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, lu);
					if (bsi != 0 && bsj != 0)
					{
						//有三个方向可走
						l[bsi][bsj - 1] = l[bsi][bsj];
						l[bsi][bsj] = 0;
						u[bsi - 1][bsj] = u[bsi][bsj];
						u[bsi][bsj] = 0;
						lu[bsi - 1][bsj - 1] = lu[bsi][bsj];
						lu[bsi][bsj] = 0;
						CHESSBOARD CBl(l);
						CHESSBOARD CBu(u);
						CHESSBOARD CBlu(lu);
						rtn.push_back(CBl);
						rtn.push_back(CBu);
						rtn.push_back(CBlu);
					}
					else if (bsi != 0 && bsj == 0)
					{
						//到最左边，只能往上走
						u[bsi - 1][bsj] = u[bsi][bsj];
						u[bsi][bsj] = 0;
						CHESSBOARD CBu(u);
						rtn.push_back(CBu);
					}
					else if (bsi == 0 && bsj != 0)
					{
						//到最上边，只能往左走
						l[bsi][bsj - 1] = l[bsi][bsj];
						l[bsi][bsj] = 0;
						CHESSBOARD CBl(l);
						rtn.push_back(CBl);
					}
				}
			}
			if(sbi!=-1)
			{
				//存在smallestbig
				if (rootcolor == 0)
				{//红色方
					int r[5][5];
					int d[5][5];
					int rd[5][5];
					copyarrey(node->chessboard.cb_of_CHESSBOARD, r);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, d);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, rd);
					if (sbi != 4 && sbj != 4)
					{
						//有三个方向可走
						r[sbi][sbj + 1] = r[sbi][sbj];
						r[sbi][sbj] = 0;
						d[sbi + 1][sbj] = d[sbi][sbj];
						d[sbi][sbj] = 0;
						rd[sbi + 1][sbj + 1] = rd[sbi][sbj];
						rd[sbi][sbj] = 0;
						CHESSBOARD CBr(r);
						CHESSBOARD CBd(d);
						CHESSBOARD CBrd(rd);
						rtn.push_back(CBr);
						rtn.push_back(CBd);
						rtn.push_back(CBrd);
					}
					else if (sbi != 4 && sbj == 4)
					{
						//到最右边，只能往下走
						d[sbi + 1][sbj] = d[sbi][sbj];
						d[sbi][sbj] = 0;
						CHESSBOARD CBd(d);
						rtn.push_back(CBd);
					}
					else if (sbi == 4 && sbj != 4)
					{
						//到最下边，只能往右走
						r[sbi][sbj + 1] = r[sbi][sbj];
						r[sbi][sbj] = 0;
						CHESSBOARD CBr(r);
						rtn.push_back(CBr);
					}
				}
				else if (rootcolor == 1)
				{//蓝色方
					int l[5][5];
					int u[5][5];
					int lu[5][5];
					copyarrey(node->chessboard.cb_of_CHESSBOARD, l);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, u);
					copyarrey(node->chessboard.cb_of_CHESSBOARD, lu);
					if (sbi != 0 && sbj != 0)
					{
						//有三个方向可走
						l[sbi][sbj - 1] = l[sbi][sbj];
						l[sbi][sbj] = 0;
						u[sbi - 1][sbj] = u[sbi][sbj];
						u[sbi][sbj] = 0;
						lu[sbi - 1][sbj - 1] = lu[sbi][sbj];
						lu[sbi][sbj] = 0;
						CHESSBOARD CBl(l);
						CHESSBOARD CBu(u);
						CHESSBOARD CBlu(lu);
						rtn.push_back(CBl);
						rtn.push_back(CBu);
						rtn.push_back(CBlu);
					}
					else if (sbi != 0 && sbj == 0)
					{
						//到最左边，只能往上走
						u[sbi - 1][sbj] = u[sbi][sbj];
						u[sbi][sbj] = 0;
						CHESSBOARD CBu(u);
						rtn.push_back(CBu);
					}
					else if (sbi == 0 && sbj != 0)
					{
						//到最下边，只能往右走
						l[sbi][sbj - 1] = l[sbi][sbj];
						l[sbi][sbj] = 0;
						CHESSBOARD CBl(l);
						rtn.push_back(CBl);
					}
				}
			}
		}
	}
	else if (node != NULL && node->parent != NULL)
	{
		//node不是根结点,可拓展棋盘由所有棋子的位置决定
		if(color==0)
		{
			//下一步是红色方走棋
			vector<ARREYANDIJ> valueandij;
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					if(node->chessboard.cb_of_CHESSBOARD[i][j]<=6&& node->chessboard.cb_of_CHESSBOARD[i][j]>=1)
					{
						ARREYANDIJ vij;
						vij.value = node->chessboard.cb_of_CHESSBOARD[i][j];
						vij.i = i;
						vij.j = j;
						valueandij.push_back(vij);
					}
				}
			}
			//现在valueandij里面是所有红色方的棋子以及其坐标
			for(int i=0;i<valueandij.size();i++)
			{
				int tempcbr[5][5];
				int tempcbd[5][5];
				int tempcbrd[5][5];
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcbr);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcbd);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcbrd);
				if(valueandij[i].i!=4&&valueandij[i].j!=4)
				{
					tempcbrd[valueandij[i].i + 1][valueandij[i].j + 1] = tempcbrd[valueandij[i].i][valueandij[i].j];
					tempcbrd[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD rd(tempcbrd);
					rtn.push_back(rd);//rightdown

					tempcbd[valueandij[i].i + 1][valueandij[i].j] = tempcbd[valueandij[i].i][valueandij[i].j];
					tempcbd[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD d(tempcbd);
					rtn.push_back(d);//down

					tempcbr[valueandij[i].i][valueandij[i].j + 1] = tempcbr[valueandij[i].i][valueandij[i].j];
					tempcbr[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD r(tempcbr);
					rtn.push_back(r);//right
				}
				else if(valueandij[i].i!=4&&valueandij[i].j==4)
				{
					tempcbd[valueandij[i].i + 1][valueandij[i].j] = tempcbd[valueandij[i].i][valueandij[i].j];
					tempcbd[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD d(tempcbd);
					rtn.push_back(d);
				}
				else if(valueandij[i].i==4&&valueandij[i].j!=4)
				{
					tempcbr[valueandij[i].i][valueandij[i].j + 1] = tempcbr[valueandij[i].i][valueandij[i].j];
					tempcbr[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD r(tempcbr);
					rtn.push_back(r);//right
				}
			}
		}
		else if(color==1)
		{
			//下一步是蓝色方走棋
			vector<ARREYANDIJ> valueandij;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (node->chessboard.cb_of_CHESSBOARD[i][j] <= 12 && node->chessboard.cb_of_CHESSBOARD[i][j] >= 7)
					{
						ARREYANDIJ vij;
						vij.value = node->chessboard.cb_of_CHESSBOARD[i][j];
						vij.i = i;
						vij.j = j;
						valueandij.push_back(vij);
					}
				}
			}
			//现在valueandij里面是所有蓝色方的棋子以及其坐标
			for (int i = 0; i < valueandij.size(); i++)
			{
				int tempcbl[5][5];
				int tempcbu[5][5];
				int tempcblu[5][5];
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcbl);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcbu);
				copyarrey(node->chessboard.cb_of_CHESSBOARD, tempcblu);
				if (valueandij[i].i != 0 && valueandij[i].j != 0)
				{
					tempcblu[valueandij[i].i - 1][valueandij[i].j - 1] = tempcblu[valueandij[i].i][valueandij[i].j];
					tempcblu[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD lu(tempcblu);
					rtn.push_back(lu);//leftup

					tempcbu[valueandij[i].i - 1][valueandij[i].j] = tempcbu[valueandij[i].i][valueandij[i].j];
					tempcbu[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD u(tempcbu);
					rtn.push_back(u);//up

					tempcbl[valueandij[i].i][valueandij[i].j - 1] = tempcbl[valueandij[i].i][valueandij[i].j];
					tempcbl[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD l(tempcbl);
					rtn.push_back(l);//left
				}
				else if (valueandij[i].i != 0 && valueandij[i].j == 0)
				{
					tempcbu[valueandij[i].i - 1][valueandij[i].j] = tempcbu[valueandij[i].i][valueandij[i].j];
					tempcbu[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD u(tempcbu);
					rtn.push_back(u);//up
				}
				else if (valueandij[i].i == 0 && valueandij[i].j != 0)
				{
					tempcbl[valueandij[i].i][valueandij[i].j - 1] = tempcbl[valueandij[i].i][valueandij[i].j];
					tempcbl[valueandij[i].i][valueandij[i].j] = 0;
					CHESSBOARD l(tempcbl);
					rtn.push_back(l);//left
				}
			}
		}
	}
	return rtn;
}
int NODE::simulate(const int cb1[][5])
{
	int cb2[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cb2[i][j] = cb1[i][j];
		}
	}
	/*对于颜色的理解：
	simulate是接着当前node对应的chessboard的下一步开始模拟
	而最初根结点记载的color是由dice决定
	如dice是1-6，为红色走棋，color记载红色，即0
	根结点的chessboard是另一方走棋后的棋盘
	也就是说，如果color是0，下一步模拟就是红色先走，
	如果color是1，下一步就是蓝色先走了
	*/
	if (color == 1)
	{//当前结点的棋盘是红色方走棋后的棋盘，对应的下一步是蓝色方走棋
		//可做优化：某方走棋后某方不可能立即输
		while (jud_end(cb2) == -1)
		{
			bluego(cb2);
			if (jud_end(cb2) == 1)
			{//蓝色方胜利
				return 1;
			}
			if(jud_end(cb2)==0)
			{
				return 0;
			}
			redgo(cb2);
			if (jud_end(cb2) == 0)
			{//红色方胜利
				return 0;
			}
			if (jud_end(cb2) == 1)
			{
				//蓝色方胜利
				return 1;
			}
		}
	}
	else if(color==0)
	{//当前结点的棋盘是蓝色方走棋后的棋盘，对应的下一步是红色方走棋
	//可做优化：某方走棋后某方不可能立即输
		while (jud_end(cb2) == -1)
		{
			redgo(cb2);
			if (jud_end(cb2) == 1)
			{
				return 1;
			}
			if (jud_end(cb2) == 0)
			{
				return 0;

			}
			bluego(cb2);
			if (jud_end(cb2) == 1)
			{
				return 1;
			
			}
			if (jud_end(cb2) == 0)
			{		
				return 0;		
			}
		}
	}
}//////////////////////////////////////////////////////////////////////////
void NODE::backup(NODE* node)
{
	while(node!=NULL&&node->parent!=NULL)
	{
		node->gamenum++;
		node->redwinnum += node->redderta;
        node->bluewinnum += node->bluederta;
		node->parent->redderta = (node->redderta);
		node->parent->bluederta = (node->bluederta);
		node = node->parent;
	}
}
int NODE::jud_if_node_is_endnode(NODE*node)
{
	if(jud_end(node->chessboard.cb_of_CHESSBOARD)!=-1)
	{
		//结束了
		return 1;
	}
	else return 0;//没结束
}



class TREE
{public:
	NODE* new_a_node(NODE*v);
	NODE* bestchild(NODE* his_parent);
	NODE* bestchildrtn(NODE*root);
	NODE* get_tail(NODE*treeroot);//这个是treepolicy
	int totalgames_of_allnodes;//所有结点的总访问数,每次simulate不能忘了它
	TREE();
};
TREE::TREE()
{
	totalgames_of_allnodes = 0;
}
NODE* TREE::get_tail(NODE*treeroot)
{
	NODE*v = treeroot;
	while(v->jud_if_node_is_endnode(v)==0&&v!=NULL)
	{//当v不是终止结点时执行如下操作：
		if(v->children.size()<v->prochessboard.size())
		{
			return new_a_node(v);
		}
		else 
		{
			v = bestchild(v);
		}
	}
	return v;
}
NODE* TREE::new_a_node(NODE*v)
{
	NODE* newchild = new NODE;//new一个新的结点
	newchild->parent = v;//初始化子结点的父结点
	newchild->chessboard = v->prochessboard[v->children.size()];//初始化子结点的棋盘
	newchild->color = 1 - v->color;//与父结点颜色不同
	newchild->prochessboard = newchild->get_procb(newchild);//得到子结点可拓展的棋盘
	newchild->rootdice = v->rootdice;
	v->children.push_back(newchild);//父结点存入子结点
	return newchild;
}
NODE* TREE::bestchild(NODE*his_parent)
{
	int indexofbestone = 0;
	NODE*temp0 = his_parent->children[0];
	double max;
	if (his_parent->color == 0)//red
	{
		max = vucb(temp0->redwinnum, temp0->gamenum, totalgames_of_allnodes);
		for (int i = 1; i < his_parent->children.size(); i++)
		{
			NODE* temp1 = his_parent->children[i];
			//NODE* temp2 = his_parent->children[i];
			if (vucb(temp1->redwinnum, temp1->gamenum, totalgames_of_allnodes) > max)
			{
				max = vucb(temp1->redwinnum, temp1->gamenum, totalgames_of_allnodes);
				indexofbestone = i;
			}
		}
	}
	else
	{ 
		max = vucb(temp0->bluewinnum, temp0->gamenum, totalgames_of_allnodes);
		for (int i = 1; i < his_parent->children.size(); i++)
		{
			NODE* temp1 = his_parent->children[i];
			//NODE* temp2 = his_parent->children[i];
			if (vucb(temp1->bluewinnum, temp1->gamenum, totalgames_of_allnodes) > max)
			{
				max = vucb(temp1->bluewinnum, temp1->gamenum, totalgames_of_allnodes);
				indexofbestone = i;
			}
		}
	}
	//return的这个bestchild是对于其parent->color这一方最好的
	return his_parent->children[indexofbestone];
}
NODE * TREE::bestchildrtn(NODE * root)
{
	int indexofbestone = 0;
	NODE*temp0 = root->children[0];
	if (rootcolor == 0)//red
	{
		double max = vucbrtn(temp0->redwinnum, temp0->gamenum, totalgames_of_allnodes);
		for (int i = 1; i < root->children.size(); i++)
		{
			NODE* temp1 = root->children[i];
			if (vucbrtn(temp1->redwinnum, temp1->gamenum, totalgames_of_allnodes) > max)
			{
				max = vucbrtn(temp1->redwinnum, temp1->gamenum, totalgames_of_allnodes);
				indexofbestone = i;
			}
		}
	}
	else
	{
		double max = vucbrtn(temp0->bluewinnum, temp0->gamenum, totalgames_of_allnodes);
		for (int i = 1; i < root->children.size(); i++)
		{
			NODE* temp1 = root->children[i];
			if (vucbrtn(temp1->bluewinnum, temp1->gamenum, totalgames_of_allnodes) > max)
			{
				max = vucbrtn(temp1->bluewinnum, temp1->gamenum, totalgames_of_allnodes);
				indexofbestone = i;
			}
		}
	}
	return root->children[indexofbestone];
}


NODE* UCTsearch(int cb_noclass[5][5],int color,int diceofr)
{
	CHESSBOARD cb0(cb_noclass);//先把数组棋盘（根）变成棋盘类的对象

	NODE *root = new NODE;//初始化父结点为空，gamenum和winnum为0，derta和color为-1
	root->chessboard = cb0;//初始化棋盘为初始根棋盘
	root->color = color;
	root->rootdice = diceofr;
	root->prochessboard = root->get_procb(root);//得到可拓展的棋盘
	
	//建立根结点

	TREE tree;
	NODE*v = NULL;
	int starttime = clock();
	int now = clock();
	while(now-starttime<4600)
	{
		v = tree.get_tail(root);
		int whowin = v->simulate(v->chessboard.cb_of_CHESSBOARD);
		if(whowin==0)
		{
			//表示模拟结果是红色赢
			v->redderta = 1;
			v->bluederta = 0;
		}
		else if(whowin==1)
		{
			//表示模拟结果是蓝色赢
			v->bluederta = 1;
			v->redderta = 0;
		}
		tree.totalgames_of_allnodes++;
		v->backup(v);
		now = clock();
	}
	cout << "------------------------------------------" << endl;
	cout << "******************************************" << endl;
	cout << "totalgame:" << tree.totalgames_of_allnodes << endl;////////////////////////////////tobedeleted
	TOTAL_NODE = tree.totalgames_of_allnodes;
	if (root->color == 0)
	{
		for (int i = 0; i < root->children.size(); i++)
		{
			cout << "children" << i << "'s wins(red): " << root->children[i]->redwinnum << " children" << i << "'s totalgames: " << root->children[i]->gamenum << " children" << i << "'s winrate(red):  " << vucbrtn(root->children[i]->redwinnum, root->children[i]->gamenum, tree.totalgames_of_allnodes) << endl;
		}
	}
	else if(root->color==1)
	{
		for (int i = 0; i < root->children.size(); i++)
		{
			cout << "children" << i << "'s wins(blue): " << root->children[i]->bluewinnum << " children" << i << "'s totalgames: " << root->children[i]->gamenum << " children" << i << "'s totalgames(blue): " << vucbrtn(root->children[i]->bluewinnum, root->children[i]->gamenum, tree.totalgames_of_allnodes) << endl;

		}
	}
	cout << "******************************************" << endl;
	NODE*r= tree.bestchildrtn(root);
	cout <<"the number of red wins you choose: "<< r->redwinnum << endl;
	cout << "the number of blue wins you choose: " << r->bluewinnum << endl;
	cout << "******************************************" << endl;
	return r;
}

string tobesent(const int cb0[5][5], const int cb1[5][5], int color)
{
	string rtn;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (cb1[i][j] != cb0[i][j] && cb1[i][j] == 0)
			{
				//原棋盘cb0[i][j]处有某棋，移动后变成0
				if(color==0)
				{
					//红方，判断右下
					if(i!=4&&j!=4)
					{
						if (cb1[i + 1][j + 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|rightdown";
						else if (cb1[i + 1][j] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|down";
						else if (cb1[i][j + 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|right";
					}
					else if(i!=4&&j==4)
					{
						if (cb1[i + 1][j] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|down";
					}
					else if(j!=4&&i==4)
					{
						if (cb1[i][j + 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|right";
					}
				}
				else if(color==1)
				{
					//蓝方，判断左上
					if (i != 0 && j != 0)
					{
						if (cb1[i - 1][j - 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|leftup";
						else if (cb1[i - 1][j] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|up";
						else if (cb1[i][j - 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|left";
					}
					else if (i != 0 && j == 0)
					{
						if (cb1[i - 1][j] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|up";
					}
					else if (j != 0 && i == 0)
					{
						if (cb1[i][j - 1] == cb0[i][j]) rtn = int_to_string(cb0[i][j]) + "|left";
					}
				}
			
			}
		}
	}
	return rtn;
}

int string_to_int(string str)
{
	int rtn = 0;
	if(str.size()==1)
	{
		rtn = str[0] - '0';
	}
	else if(str.size()==2)
	{
		rtn = (str[0] - '0') * 10 + str[1] - '0';
	}
	return rtn;
}

string int_to_string(int num)
{
	string rtn;
	if(num>=10&&num<=99)
	{
		rtn.push_back('1');
		num = num - 10;
		rtn.push_back((char)(num + '0'));
	}
	else if(num<10&&num>=0)
	{
		rtn.push_back((char)(num + '0'));
	}
	return rtn;
}


/*int send()
{
	//1|rightdown  或 1|right 或 1|down
	//10|leftup 或 10|left 或 10|up
}*/


void onetotwo(int a[],int b[][5])
{
	for(int i=0;i<25;i++)
	{
		if(0<=i&&i<5)
		{
			b[0][i - 0] = a[i];
		}
		else if(5<=i&&i<10)
		{
			b[1][i - 5] = a[i];
		}
		else if(10<=i&&i<15)
		{
			b[2][i - 10] = a[i];
		}
		else if(15<=i&&i<20)
		{
			b[3][i - 15] = a[i];
		}
		else if(20<=i&&i<25)
		{
			b[4][i - 20] = a[i];
		}
	}
}


void twotoone(int b[][5],int a[])
{
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for(int j=0;j<5;j++)
		{
			a[k] = b[i][j];
			k++;
		}
	}
}


void cleantree(NODE*root)
{
	for (int i = 0; i < root->children.size(); i++)
	{
		cleantree(root->children[i]);
	}
	delete root;
}


Einstein::Einstein()
{
	this->clientsocket.connectServer();
	clientsocket.sendMsg(ID);
}

Einstein::~Einstein()
{
	this->clientsocket.close();
}

int Einstein::parse(std::string s)
{
	
	//[[0, 6, 2, 0, 0], [5, 1, 0, 0, 0], [4, 0, 0, 0, 8], [0, 0, 0, 10, 7], [0, 0, 9, 11, 12]]|1
	string str_of_dice ;
	vector<vector<string> > strbox;
	vector<string> temprow;
	for(int i=0;i<s.size();i++)
	{
		string tempone;
		if(s[i]<='9'&&s[i]>='0')
		{
			tempone.push_back(s[i]);
			if(s[i+1]<='9'&&s[i+1]>='0')
			{
				tempone.push_back(s[i + 1]);
				i++;
			}
			temprow.push_back(tempone);
		}		
		if(temprow.size()==5)
		{
			strbox.push_back(temprow);
			temprow.clear();
		}
		if(strbox.size()==5)
		{
			for(int j=i+1;j<s.size();j++)
			{
				if(s[j]>='0'&&s[j]<='9')
				{
					str_of_dice.push_back(s[j]);
					if(j+1<s.size()&&s[j+1]>='0'&&s[j+1]<='9')
					{
						str_of_dice.push_back(s[j + 1]);
						break;
					}
				}
			}
			break;
		}
	}
	//now the strbox is the string form (double vector) of box
	//the str_of_dice is the string form of dice
	dice = string_to_int(str_of_dice);
	vector<string> str_of_chessboard;
	for(int i=0;i<strbox.size();i++)
	{
		for(int j=0;j<strbox[i].size();j++)
		{
			str_of_chessboard.push_back(strbox[i][j]);
		}
	}
	for(int i=0;i<25;i++)
	{
		chessboard[i] = string_to_int(str_of_chessboard[i]);
	}
	//now the chessboard and the dice have been modified.
	return 0;
}

int Einstein::handle()
{
	srand((unsigned int)(time(NULL)));
	
	if (this->clientsocket.recvMsg() == 1)
		return 0;
	//get the first address of Msg
	string msg = this->clientsocket.getRecvMsg();
	parse(msg);
	int cb2[5][5];
	rootcolor = getrootcolor(dice);
	onetotwo(chessboard, cb2);
	NODE*node=UCTsearch(cb2, rootcolor,dice);
	string sent = tobesent(cb2, node->chessboard.cb_of_CHESSBOARD, rootcolor);
	const char*p = (char*)sent.data();
	this->clientsocket.sendMsg(p);
	cout << "******************************************" << endl;
	cout << "the step: " << p << endl;
	cout << "******************************************" << endl;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			cout << node->chessboard.cb_of_CHESSBOARD[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************************" << endl;
	cout << "__________________________________________" << endl;
	NODE*root = node->parent;
	cleantree(root);
	return 1;
}

int Einstein::logging(std::string s)
{
	return 0;
}

int Einstein::writelog()
{
	return 0;
}
