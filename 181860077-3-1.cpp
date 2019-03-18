#include<iostream>
#include<cstdlib>
using namespace std;
#define max 18
//3-10是正常的数据，JQK是11-13，A是14，2是15，最后的是大小王
void mygetnum(char *A, int *B)
{
	for (; *A != '\0'; A++)
	{
		if (*A <= '9'&&*A >= '3')
		{
			int j = *A - '0';
			B[j]++;
			A++;
			continue;

		}
		if (*A == '1'&&*(A + 1) == '0')
		{
			int j = 10;
			B[j]++;
			A += 2;
		}
		if (*A == 'J'&&*(A + 1)!='O')
		{
			int j = 11;
			B[j]++;
			A++;
			continue;
		}
		if (*A == 'Q')
		{
			int j = 12;
			B[j]++;
			A++;
			continue;
		}
		if (*A == 'K')
		{
			int j = 13;
			B[j]++;
			A++;
			continue;
		}
		if (*A == 'A')
		{
			int j = 14;
			B[j]++;
			A++;
			continue;
		}
		if (*A =='2')
		{
			int j =15;
			B[j]++;
			A++;
			continue;
		}
		if (*A == 'j'&&*(A + 1) == 'o')
		{
			int j = 16;
			B[j]++;
			A += 4;
			continue;
		}
		if (*A == 'J'&&*(A + 1) == 'O'&&*(A + 2) == 'K')
		{
			int j = 17;
			B[j]++;
			A += 4;
			continue;
		}
	}
}
int findmax(int *B,int *num)//num就是张数，返回的是牌的值
{
	int pos(3);
	for (int i(3); i < max; i++)
	{
		if (B[i] > B[pos])
		{
			pos = i;
		}
	}
	*num = B[pos];
	return pos;
}
//输出函数
void myprint(int *B)
{
	for (int i(max); i > 2; i--)
	{
		for (int j(0); j < B[i]; j++)
		{
			if (i == 17)
			{
				cout << "JOKER" << " ";
				continue;
			}
			if (i == 16)
			{
				cout << "joker" << " ";
				continue;
			}
			if (i == 15)
			{
				cout << 2 << " ";
				continue;
			}
			if (i == 14)
			{
				cout << "A" << " ";
				continue;
			}
			if (i == 13)
			{
				cout << "K" << " ";
				continue;
			}
			if (i == 12)
			{
				cout << "Q" << " ";
				continue;
			}
			if (i == 11)
			{
				cout << "J" << " ";
				continue;
			}
			cout << i << " ";
		}
	}
	cout << endl;
}
//解析对手的牌
void jiexi(char *A, int *type, int *cardm,int* q,int *p)//type保存的是牌的种类，cardm保存的是牌的数值（最小的），q是带的张数（种类，一张还是一对的），p是连续的张数。
{
	int B[18] = {};
	B[0] = 0;
	B[1] = 0;
	B[2] = 0;
	mygetnum(A,B);
	int allnum(0);
	//计算对方的出牌数
	int initmax1(0);
	int initmax2 = findmax(B, &initmax1);
	if (initmax1 == 1)//顺子的可能性
	{
		if (B[16] == 1 && B[17] == 1)
		{
			*type = 41;
			return;
		}
		int singlenum(0);
		for (int i(3); i < max; i++)
		{
			if (B[i] == 1)
			{
				singlenum++;
			}
		}
		if (singlenum != 1)
		{
			*type = 7;
			*p = singlenum;
			*cardm = initmax2;
			return;
		}

	}
	if (initmax1 == 2)//排除连对的可能性
	{
		int doublenum(0);
		for (int i(3); i < max; i++)
		{
			if (B[i] == 2)
			{
				doublenum++;
			}
		}
		if (doublenum != 1)
		{
			*type = 8;
			*p = doublenum;
			*cardm = initmax2;
			return;
		}
	}
	for (int i(3); i < max; i++)//计算总的牌数
	{
		allnum += B[i];
	}
	if (allnum == 1)
	{
		*type = 1;
		int k(0);
		*cardm = findmax(B, &k);
		return;
	}
	if (allnum == 2)
	{
		*type = 2;
		int k(0);
		*cardm = findmax(B, &k);
		return;
	}
	if (allnum == 3)
	{
		*type = 3;
		int k(0);
		*cardm = findmax(B,&k);
		*q = 0;
		return;
	}
	if (allnum == 4)
	{
		int maxnumzhang = 0;
		int maxnumzhi=findmax(B,&maxnumzhang);
		if (maxnumzhang == 4)
		{
			*type = 4;
			*cardm = maxnumzhi;
			return;
		}
		if (maxnumzhang == 3)
		{
			*type = 3;
			*cardm = maxnumzhi;
			*q = 1;
			return;
		}
	}
	if (allnum == 5)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//三带二
		{
			*type = 3;
			*cardm = maxnumzhi;
			*q = 2;
			return;
		}
	}
	if (allnum == 6)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//飞机不带
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 0;
			*p = 2;
			return;
		}
		if (maxnumzhang == 4)//四带二
		{
			*type = 5;
			*cardm = maxnumzhi;
			*q = 1;
			return;
		}
	}
	if (allnum == 8)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//飞机带一
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 1;
			*p = 2;
			return;
		}
		if (maxnumzhang == 4)//四带二对
		{
			*type = 5;
			*cardm = maxnumzhi;
			*q = 2;
			return;
		}
	}
	if (allnum == 9)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//三飞机不带
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 0;
			*p = 3;
			return;
		}
	}
	if (allnum == 10)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//二飞机带两对
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 2;
			*p = 2;
			return;
		}
	}
	if (allnum == 12)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//三飞机带一
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 1;
			*p = 3;
			return;
		}
	}
	if (allnum == 15)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
		if (maxnumzhang == 3)//三飞机带二
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 2;
			*p = 3;
			return;
		}
	}

}
//对于对手不同的出牌的模式进行思考
int singlecard(int *cardnum, int q)
{
	int B[18] = {};
	for (int i(q+1); i < max; i++)
	{
		if (cardnum[i] > 0)
		{
			cardnum[i]--;
			B[i]++;
			myprint(B);
			return 1;
		}
	}
	return -1;
}
int doublecard(int *cardnum, int q)
{
	int B[18] = {};
	for (int i(q+1); i < max; i++)
	{
		if (cardnum[i] > 1)
		{
			cardnum[i] -= 2;
			B[i]+=2;
			myprint(B);
			return 1;
		}
	}
	return -1;
}
int triblecard(int *cardnum, int q, int p)//q是起始点，p是带的牌的种类
{
	int B[18] = {};
	for (int i(q+1); i < max; i++)
	{
		if (cardnum[i] > 2)
		{
			cardnum[i] -= 3;//张数减少避免可能的牌重复出
			B[i]+=3;
			if (p == 0)
			{
				myprint(B);
				return i;
			}
			for (int j(3); j < max; j++)
			{
				if (cardnum[j] >= p)
				{
					if (p == 1)
					{
						B[j]++;
						cardnum[j]--;
						myprint(B);
						return 0;
					}
					else
					{
						B[j]+=2;
						cardnum[j] -= 2;
						myprint(B);
						return 0;
					}
				}
			}
			cardnum[i] += 3;//组合失败就重新回去计算
			return -1;
		}

	}
	return -1;
}
int bombcard(int *cardnum, int q)
{
	int B[18] = {};
	for (int i(q+1); i < max; i++)
	{
		if (cardnum[i] == 4)
		{
			B[i] += 4;
			myprint(B);
			cardnum[i] -= 4;
			return 0;
		}
	}
	if (cardnum[16] == 1 && cardnum[17] == 1)
	{
		cardnum[16]--; 
		cardnum[17]--;
		B[16]++;
		B[17]++;
		myprint(B);
		return 0;
	}
	return -1;
}
int forthcard(int *cardnum, int q, int p)
{
	int B[18] = {};
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] == 4)
		{
			cardnum[i] -= 4;
			B[i] += 4;
			int d1(0);
			int d2(0);
			int paishu(0);
			for (int j(3); j < max; j++)
			{
				if (cardnum[j] >= p)
				{
					paishu++;
					if (paishu == 1)
					{
						d1 = j;
						if (p == 1)
						{
							B[d1]++;
							cardnum[d1]--;
						}
						else
						{
							B[d1] += 2;
							cardnum[d1] -= 2;

						}
					}
					if (paishu == 2)
					{
						d2 = j;
						if (p == 1)
						{
							B[d2]++;
							cardnum[d2]--;
						}
						else
						{
							B[d2] += 2;
							cardnum[d2] -= 2;

						}
						myprint(B);
						
						return 1;
					}
				}
			}
			cardnum[i] += 4;
			return -1;
		}
	}
	return -1;
}
int planecard(int *cardnum, int q, int p, int s)//仍然是q代表的是三的最小的起点，然后后面表示的是带的张数，最后是飞机的连续数目
{
	int B[18] = {};
	if (s == 2)
	{
		for (int i(q + 1); i < max - 1; i++)
		{
			int k(0);
			for (; k < 2; k++)//从当前的起点开始向后面找s个数值的牌是否也是飞机
			{
				if (cardnum[i + k] < 3)
					break;
			}
			if (k == 2)
			{
				cardnum[i] -= 3;
				B[i] += 3;
				cardnum[i + 1] -= 3;
				B[i + 1] += 3;
				if (p == 0)
				{
					myprint(B);
					return 1;
				}
				int daipaishu(0);
				int d1(0);
				int d2(0);
				for (int d(3); d < max; )
				{
					if (cardnum[d] >= p)
					{
						daipaishu++;
						if (daipaishu == 2)
						{
							d2 = d;
							cardnum[d2] -= p;
							B[d2] += p;
							break;
						}
						else
						{
							d1 = d;
							cardnum[d1] -= p;
							B[d1] += p;
						}

					}
					else
						d++;
				}
				if (daipaishu == 2)
				{
					myprint(B);
					return 0;
				}
				else
				{
					cardnum[i] += 3;
					cardnum[i + 1] += 3;
					if (daipaishu == 1)
					{
						B[d1] -= p;
						cardnum[d1] += p;
					}
					return -1;
				}

			}
		}

	}
	if (s == 3)
	{
		for (int i(q + 1); i < max - 1; i++)
		{
			int k(0);
			for (; k < 3; k++)//从当前的起点开始向后面找s个数值的牌是否也是飞机
			{
				if (cardnum[i + k] < 3)
					break;
			}
			if (k == 3)
			{
				cardnum[i] -= 3;
				cardnum[i + 1] -= 3;
				cardnum[i + 2] -= 3;
				B[i] += 3;
				B[i + 1] += 3;
				B[i + 2] += 3;
				if (p == 0)
				{
					myprint(B);
					return 1;
				}
				int daipaishu(0);
				int d1(0);
				int d2(0);
				int d3(0);
				for (int d(3); d < max; d++)
				{
					if (cardnum[d] >= p)
					{
						daipaishu++;
						if (daipaishu == 1)
						{
							d1 = d;
						}
						if (daipaishu == 2)
						{
							d2 = d;
						}
						if (daipaishu == 3)
						{
							d3 = d;
							break;
						}

					}
				}
				if (daipaishu == 3)
				{
					if (p == 1)
					{
						B[d1]++;
						cardnum[d1]--;
						B[d2]++;
						cardnum[d2]--;
						B[d3]++;
						cardnum[d3]--;
					}
					else
					{
						cardnum[d1] -= 2;
						B[d1] += 2;
						B[d2] += 2;
						cardnum[d2] -= 2;
						B[d3] += 2;
						cardnum[d3] -= 2;
					}
					myprint(B);
					return 0;
				}
				else
				{
					cardnum[i] += 3;
					cardnum[i + 1] += 3;
					cardnum[i + 2] += 3;
					return -1;
				}

			}
		}
		return -1;
	}
	return -1;
}
int shunzi(int *cardnum, int q, int p)//仍然q作为开始点的数值，p是连续的数量
{
	int B[18] = {};
	for (int i(q+1); i < max - p + 1; i++)
	{
		int j = i;
		for (; j < 16; j++)//顺子最大到2为止，对应的数值就是15+1
		{
			if (cardnum[j] < 1)
				break;
		}
		if (j - i >= p)
		{
			for (int ws(p-1); ws >= 0; ws--)
			{
				cardnum[i + ws]--;
				B[i + ws]++;
			}
			myprint(B);
			return 1;
		}
	}
	return -1;
}
int doubleshunzi(int *cardnum, int q, int p)
{
	int B[18] = {};
	for (int i(q+1); i < max - p + 1; i++)
	{
		int j = i;
		for (; j < 16; j++)//顺子最大到2为止，对应的数值就是15+1
		{
			if (cardnum[j] < 2)
				break;
		}
		if (j - i  >= p)
		{
			for (int ws(p - 1); ws >= 0; ws--)
			{
				cardnum[i + ws] -= 2;
				B[i + ws]+=2;
			}
			myprint(B);
			return 1;
		}
	}
	return -1;
}
int main()
{
	int wa(0);
	int wb(0);
	cin >> wa;
	cin >> wb;
	char WA = getchar();
	//A是输入的我的牌
	char A[100] = {};
	A[0] = getchar();
	int i(0);
	for (; A[i] != '\n';)
	{
		i++;
		A[i] = getchar();
		
	}
	A[i] = '\0';
	char C[100] = {};
	C[0] = getchar();//C是对手的牌
	int sj(0);
	for (; C[sj] != '\n';)
	{
		sj++;
		C[sj] = getchar();

	}
	C[sj] = '\0';
	//B是我的手牌,C是对手的
	int B[18] = {};
	B[0] = 0;
	B[1] = 0;
	B[2] = 0;
	mygetnum(A, B);
	int j(1);
	int type = 0;//出牌的种类
	int q = 0;//带牌的种类
	int p = 0;//连续的数目
	int cardm = 0;//牌的起始点
	jiexi(C, &type, &cardm, &q, &p);
	if (type == 1)
	{
		if (singlecard(B, cardm) == -1)
		{
			if (bombcard(B, 2)==-1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 2)
	{
		if (doublecard(B, cardm) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 3)
	{
		if (triblecard(B, cardm, q) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 4)
	{
		if (bombcard(B, cardm) == -1)
		{
			cout << "YAO BU QI" << endl;
			return 0;
			
		}
	}
	if (type == 5)
	{
		if (forthcard(B, cardm, q) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 6)
	{
		if (planecard(B, cardm, q, p) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 7)
	{
		if (shunzi(B, cardm, p) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 8)
	{
		if (doubleshunzi(B, cardm , p ) == -1)
		{
			if (bombcard(B, 2) == -1)
			{
				cout << "YAO BU QI" << endl;
				return 0;
			}
		}
	}
	if (type == 41)
		cout << "YAO BU QI" << endl;
	return 0;


}
