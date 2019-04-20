//下面的是头文件
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
#include<iomanip>
#include <winbase.h>
#include <functional>
#include <ctime>
#include<time.h>

using namespace std;
class song {//打算是在用一个类的数组来保存很多的歌曲对象实体
public:
	string songname;//歌的名字
	string pinyin;
	string singername;//歌手的名
	int serialnum;//序列号，就是在歌单里的序列
	int ranknum;//排行的位置
	int playstatus;//是否处于播放状态
	int playfrequence;
	int judgefrequence;//播放的次数，作为计算的根据
	double totalscore;//总分，也是计算的根据
	double starnum;//评分数
};

class admin
{
public:
	admin();

	friend class ktvsystem;

	friend class user;

	vector<song> mysong;

	int changepassword();//这两个返回值都是表示状态，改成功和登陆成功

	int login();//登陆函数

	int add_song();//加歌

	int delete_song();//删除歌曲，成功返回1

	int file_in();//加载外面文件的歌曲，加载成功就返回1

	int file_out();//导出文件

	int sort_song();//对歌曲排序

	int admenu();//显示管理员的专用界面，并接受输入的操作值

	int initialsong(song &temp);

	int printall(vector<song>&A);

	int printsong(song &temp);

	int legalID(string A);

	int legalpassword(string B);

	int realprintall();

	int creat_new_account();

	int delete_account();

	int adminselect();

private:
	vector<string> ID;
	vector<string> password;//保存密码
};

class user {
public:
	user();

	friend class ktvsystem;

	friend class admin;

	int usmenu(admin &A);//显示用户界面并返回操作值

	int ordersong(admin &A);//点歌

	int see_playingqueue(admin &A);//查看待播放队列里歌曲

	int make_song_top(admin &A);//置顶

	int change_song(admin &A);//切歌

	int delete_song_inqueue(admin & A);//删除播放队列中的歌

	int judge_song(admin& A);//评分

	int realsee_playingqueue(admin &A);

	int search_song(admin &A);

	int gameplay();

	int pay_bill();

private:
	//int usopnum;//操作值
	vector<int>playing_queue;//正在播放的队列，保存所有的播放的歌曲
	int played_number;
	int discount;
};

class ktvsystem {
public:
	admin A;
	user B;
	int pmainmenu();
	int initialsys();
	void run();
private:
	int syoperationnum;//system的操作代码
};

bool comp_srerial(const song&A, const song&B)
{
	return A.serialnum < B.serialnum;
}

bool comp_starnum(const song&A, const song &B)
{
	return A.starnum > B.starnum;
}

bool comp_frenum(const song&A, const song &B)
{
	return A.playfrequence > B.playfrequence;
}





#define max 18


class Card : public string {
public:
	static const int N_CARD_VALUES;
	static const int N_CARD_SUITS;
	static const string CARD_VALUES[];
	static const string CARD_SUITS[];

	Card(const char* str) :string(str) {};
	Card() :string() {};
	Card(string str) :string(str) {};

	static vector<Card> get_new_deck();

	bool operator <(const Card &other) const;
	bool operator >(const Card &other) const;
};

class DDZPlayer {
protected:
	string name; 
	int position; 
	vector<Card> hand;

	int prePos;
	vector<Card> prePlay; 

	bool legal(vector<Card> cards);  
	void substractFromHand(vector<Card> cards);
public:
	DDZPlayer(string name);  
	string getName();
	virtual void draw(Card card); 
	virtual void draw(vector<Card> cards);  
	virtual void setPosition(int pos); 
	virtual void showHand();  
	virtual void observed(int pos, vector<Card> cards);  
	virtual vector<Card> play(); 
	bool leftNoCard();  
};

class DDZGame {
private:
	static int my_random(int i);
	vector<DDZPlayer*> players;
	void showCards(vector<Card> cards);

public:
	DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  
	int run();
};

class DDZHumanPlayer : public DDZPlayer {
public:
	DDZHumanPlayer(string name) : DDZPlayer(name) {};
	vector<Card> play();
};

void zifuchuang(vector<Card> cards);
int *transferA(vector<Card> cards, int *A);
int findmax(int *B, int *num);
void jiexi(int* B, int *type, int *cardm, int* q, int *p);
void myprint(int *B);
void transferB(vector<Card> &cards, int *mycard);
int yingdui(int *B, int *D, int type, int cardm, int q, int p);
void myshowCards(vector<Card> cards);
void initialop2(int *A, int *B);
int addnum(int *A);
int mylegal(int *A);

bool Card::operator <(const Card &other) const {
	int a = -1, b = -1;
	for (int i = 0; i < N_CARD_VALUES; ++i) {
		if (*this == CARD_VALUES[i]) a = i;
		if (other == CARD_VALUES[i]) b = i;
	}
	return a < b;
}

bool Card::operator >(const Card &other) const {
	return other < *this;
}

DDZPlayer::DDZPlayer(string name) : name(name) {
	// �����Ĺ��캯��
	prePos = -1;
}

string DDZPlayer::getName() {
	return name;
}

bool DDZPlayer::legal(vector<Card> cards) {

	// ͨ���ϼҴ������prePlay������hand�ж�cards��Ϊ������Ƿ�Ϸ�
	int mytrue(0);
	int apreplay[18] = { 0 };//�ϼҴ���Ƶ�ת��
	transferA(prePlay, apreplay);
	int ahand[18] = { 0 };//����ת��������
	transferA(hand, ahand);
	int acards[18] = { 0 };//����ת��������
	transferA(cards, acards);//���жϳ��Ƶ����ڲ���������
	for (int kl(3); kl < max; kl++)
	{
		if (acards[kl] > ahand[kl])
		{
			return 0;
		}
	}
	int mycardnum(0);
	mycardnum = addnum(acards);
	if (prePos == position || prePos == -1)
	{
		if (mycardnum == 0)
		{
			return 0;
		}
		else
			mytrue = mylegal(acards);
		return mytrue;
	}
	if (mycardnum == 0)
	{
		return 1;
	}

	int preplaynum = addnum(apreplay);
	//����Է��ĳ�����
	if (preplaynum == 0)//�Է�û�г���������
	{
		mytrue = mylegal(acards);
	}
	else
	{
		if (preplaynum == mycardnum)
		{
			mytrue = mylegal(acards);//ǰ�����ƺϷ�
			int type = 0;
			int cardm = 0;
			int q = 0;
			int p(0);
			jiexi(apreplay, &type, &cardm, &q, &p);
			int temp[18] = { 0 };
			int res = yingdui(acards, temp, type, cardm, q, p);
			if (res == -1)
				mytrue = 0;
		}
		else
		{
			if (preplaynum == 2 || preplaynum == 4)
			{
				for (int j(3); j < max; j++)
				{
					if (acards[j] == 4)
					{
						mytrue = 1;
					}
				}
				if (acards[17] == 1 && acards[16] == 1)
				{
					mytrue = 1;
				}
			}
		}
	}
	return mytrue;
}

void DDZPlayer::substractFromHand(vector<Card> cards)
{
	sort(hand.begin(), hand.end(), greater<Card>());
	sort(cards.begin(), cards.end(), greater<Card>());
	vector<Card>::iterator i = hand.begin(), k = cards.begin();
	for (vector<Card>::iterator j = hand.begin(); j != hand.end(); ++j)
	{
		if (k == cards.end() || *k != *j) *(i++) = *j;
		else if (k != cards.end()) ++k;
	}
	hand.erase(i, hand.end());
}

void DDZPlayer::showHand() {
	// �������������ơ�
	cout << name << " holds: ";
	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

void DDZPlayer::draw(Card card) {
	// ��card��������
	hand.push_back(card);
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
	// ��cards�е��Ƽ�������
	hand.insert(hand.end(), cards.begin(), cards.end());
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
	position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
	// ����һ�����Ƶ��˺ͳ���ʲô�Ƽ�¼������
	// ��������¼�������Ϣ����Ĳ���ʹ�ã����ԸĶ����������
	// ���磬��¼�Ѿ�����Щ�Ʊ�������������������Ʋⳡ���Ƿ���ܻ�����ը����
	if (cards.size() == 0) return;
	prePos = pos;
	prePlay = cards;
}

vector<Card> DDZPlayer::play() {
	// �ֵ�����ƣ����ش�����ơ�
	// TODO������һ�⣩�������������
	// �����ʹ�ò�ͬ�����ݽṹ���д�����������ֽ�hand����ת��Ϊ��ʹ�õĽṹ��
	// ���������ٽ��������ת��Ϊvector<Card>������card������
	int A[18] = { 0 };
	transferA(hand, A);
	int B[18] = { 0 };
	vector<Card> cards;
	if (prePos == position || prePos == -1)
	{
		initialop2(A, B);
		transferB(cards, B);
	}
	else
	{
		// λ��prePos����Ҵ����prePlay���ƣ�����Ҫ��ʲô�ƣ�
		int C[18] = { 0 };
		transferA(prePlay, C);
		int type = 0;
		int cardm = 0;
		int q = 0;
		int p(0);

		jiexi(C, &type, &cardm, &q, &p);
		int outputcard[18] = { 0 };
		int res = yingdui(A, outputcard, type, cardm, q, p);
		if (res != -1)
			transferB(cards, outputcard);
	}

	// ����Ҫ��֤��������ǺϷ���
	// assert�����ڲ���Ϊfalse��ʱ���ʹ���򱨴��˳���
	// �������ĺô��ǣ��������ûע�⵽�Ĵ����³����ڴ˱����˳���
	// ���֪�����ڳ��ƵĺϷ����ϳ������⣬�������Ų������������֡�
	// assert(legal(cards));

	// ��������ƴ�������ɾȥ
	substractFromHand(cards);
	//myshowCards(cards);
	//-myshowCards(hand);
	return cards;
}

bool DDZPlayer::leftNoCard() {
	return hand.empty();
}

const int Card::N_CARD_VALUES = 15;

const int Card::N_CARD_SUITS = 4;

const string Card::CARD_VALUES[] = {
	"3", "4", "5", "6",
	"7", "8", "9", "10",
	"J", "Q", "K", "A", "2",
	"joker", "JOKER"
};

const string Card::CARD_SUITS[] = {
	"Spades", "Hearts", "Diamonds", "Clubs"
};

vector<Card> Card::get_new_deck() {
	// ����һ������
	vector<Card> deck;
	for (int i = 0; i < N_CARD_VALUES - 2; ++i) {
		for (int j = 0; j < N_CARD_SUITS; ++j) {
			Card card(CARD_VALUES[i]);
			deck.push_back(card);
		}
	}
	deck.push_back(Card(CARD_VALUES[13]));
	deck.push_back(Card(CARD_VALUES[14]));
	return deck;
}

int DDZGame::my_random(int i) {
	return std::rand() % i;
}

DDZGame::DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3) {
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);
}

void DDZGame::showCards(vector<Card> cards) {
	sort(cards.begin(), cards.end(), greater<Card>());
	for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i) {
		cout << *i << " ";
	}
	if (cards.size() == 0) cout << "YAO BU QI";
	cout << endl << endl;
}

int DDZGame::run()
{
	vector<Card> deck = Card::get_new_deck();
	random_shuffle(deck.begin(), deck.end(), my_random);


	for (int i = 0; i < 54 - 3; ++i)
		players[i % 3]->draw(deck[i]);


	int landlordPos = my_random(3);
	for (int i = 54 - 3; i < 54; ++i)
		players[landlordPos]->draw(deck[i]);
	for (int i = 0; i < 3; ++i)
		players[i]->setPosition((i + 3 - landlordPos) % 3);
	cout << players[landlordPos]->getName() << " is the landlord." << endl;
	int currentPlayer = landlordPos;

	while (true) {
		vector<Card> currentCards = players[currentPlayer]->play();
		cout << players[currentPlayer]->getName() << " plays:";
		showCards(currentCards);
		for (int i = 0; i < 3; ++i)
		{

			int relativePos = (currentPlayer + 3 - landlordPos) % 3;
			players[i]->observed(relativePos, currentCards);
		}

		if (players[currentPlayer]->leftNoCard())
		{
			cout << players[currentPlayer]->getName() << "赢了" << endl;
			Sleep(1000);
			if (landlordPos == 2)
			{
				if (currentPlayer == 2)
				{
					cout << "恭喜得到八折优惠,返回上一级" << endl;
					Sleep(3000);
					return 1;
				}
				else
				{
					cout << "惜败给人工智障失去折扣优惠,返回上一级" << endl;
					Sleep(3000);
					return 0;
				}
			}
			else
			{
				if (currentPlayer != landlordPos)
				{
					cout << "恭喜得到八折优惠,返回上一级" << endl;
					Sleep(3000);
					return 1;
				}
				else
				{
					cout << "惜败给人工智障失去折扣优惠,返回上一级" << endl;
					Sleep(3000);
					return 0;
				}
			}
		}
		currentPlayer = (currentPlayer + 1) % 3;
	}
}

vector<Card> DDZHumanPlayer::play() {
	vector<Card> cards;
	string s, c;
	while (true) {
		showHand();
		cout << "Please input the cards you want to play." << endl;
		getline(cin, s);
		istringstream iss(s);
		while (iss >> c)
		{
			int flag(0);
			for (int j(0); j < 15; j++)
			{
				if (c == Card::CARD_VALUES[j])
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				goto L1;
			}
			cards.push_back(Card(c));
		}
		// ����cards��һ��vector<Card>���洢���û��������
		// ����Ҫ�����������ǳ��е��ƣ����ҺϷ��������legal������
		if (legal(cards)) {
			break;
		}
		else {
		L1:			cout << "Illegal cards. Input again." << endl;
			cards.clear();
		}
	}
	substractFromHand(cards);
	return cards;
}

void myshowCards(vector<Card> cards) {
	sort(cards.begin(), cards.end(), greater<Card>());
	for (vector<Card>::iterator i = cards.begin(); i != cards.end(); ++i) {
		cout << *i << " ";
	}
	if (cards.size() == 0) cout << "YAO BU QI";
	cout << endl << endl;
}

int *transferA(vector<Card> cards, int*haha)
{

	int j(0);
	for (; j < cards.size(); j++)
	{
		for (int k(0); k < 15; k++)
		{
			if (cards[j] == Card::CARD_VALUES[k])
			{
				haha[k + 3]++;
				break;
			}
		}
	}

	return haha;
}

void transferB(vector<Card> &cards, int *mycard)
{
	for (int r(3); r < max; r++)
	{
		for (int d(0); d < mycard[r]; d++)
		{
			cards.push_back(Card::CARD_VALUES[r - 3]);
		}
	}
}

int findmax(int *B, int *num)//num�������������ص����Ƶ�ֵ
{
	int pos(3);
	for (int i(3); i < 18; i++)
	{
		if (B[i] > B[pos])
		{
			pos = i;
		}
	}
	*num = B[pos];
	return pos;
}

void jiexi(int *B, int *type, int *cardm, int* q, int *p)//type��������Ƶ����࣬cardm��������Ƶ���ֵ����С�ģ���q�Ǵ������������࣬һ�Ż���һ�Եģ���p��������������
{
	int allnum(0);
	//����Է��ĳ�����
	int initmax1(0);
	int initmax2 = findmax(B, &initmax1);
	if (initmax1 == 1)//˳�ӵĿ�����
	{
		if (B[16] == 1 && B[17] == 1)
		{
			*type = 41;
			return;
		}
		int singlenum(0);
		for (int i(3); i < 18; i++)
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
	if (initmax1 == 2)//�ų����ԵĿ�����
	{
		int doublenum(0);
		for (int i(3); i < 18; i++)
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
	for (int i(3); i < 18; i++)//�����ܵ�����
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
		*cardm = findmax(B, &k);
		*q = 0;
		return;
	}
	if (allnum == 4)
	{
		int maxnumzhang = 0;
		int maxnumzhi = findmax(B, &maxnumzhang);
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
		if (maxnumzhang == 3)//������
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
		if (maxnumzhang == 3)//�ɻ�����
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 0;
			*p = 2;
			return;
		}
		if (maxnumzhang == 4)//�Ĵ���
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
		if (maxnumzhang == 3)//�ɻ���һ
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 1;
			*p = 2;
			return;
		}
		if (maxnumzhang == 4)//�Ĵ�����
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
		if (maxnumzhang == 3)//���ɻ�����
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
		if (maxnumzhang == 3)//���ɻ�������
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
		if (maxnumzhang == 3)//���ɻ���һ
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
		if (maxnumzhang == 3)//���ɻ�����
		{
			*type = 6;
			*cardm = maxnumzhi;
			*q = 2;
			*p = 3;
			return;
		}
	}

}

void initialop2(int *A, int *B)
{
	for (int i(3); i < max; i++)
	{
		if (A[i] >= 2)
		{
			B[i] += 2;
			A[i] -= 2;
			return;
		}
	}
	if (A[16] && A[17])
	{
		B[16]++;
		B[17]++;
		A[16]--;
		return;
	}
	for (int i(3); i < 12; i++)
	{
		int flag = 0;//�鿴�Ƿ���˳�ӵĴ���
		for (int j(i); j < 16; j++)
		{
			if (A[j] == 0)
				break;
			flag++;
		}
		if (flag >= 5)
		{
			for (int s(0); s < flag; s++)
			{
				B[s + i]++;
				A[s + i]--;
			}
			return;
		}

	}
	for (int i(3); i < max; i++)
	{
		if (A[i] > 0)
		{
			B[i]++;
			A[i]--;
			return;
		}
	}

}

void myprint(int *B)
{
	for (int i(17); i > 2; i--)
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

int singlecard(int *cardnum, int q, int *B)
{
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] > 0)
		{
			cardnum[i]--;
			B[i]++;
			return 1;
		}
	}
	return -1;
}
int doublecard(int *cardnum, int q, int *B)
{
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] > 1)
		{
			cardnum[i] -= 2;
			B[i] += 2;
			return 1;
		}
	}
	return -1;
}
int triblecard(int *cardnum, int q, int p, int *B)//q����ʼ�㣬p�Ǵ����Ƶ�����
{
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] > 2)
		{
			cardnum[i] -= 3;//�������ٱ�����ܵ����ظ���
			B[i] += 3;
			if (p == 0)
			{
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
						return 0;
					}
					else
					{
						B[j] += 2;
						cardnum[j] -= 2;
						return 0;
					}
				}
			}
			cardnum[i] += 3;//���ʧ�ܾ����»�ȥ����
			return -1;
		}

	}
	return -1;
}
int bombcard(int *cardnum, int q, int *B)
{
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] == 4)
		{
			B[i] += 4;
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
		return 0;
	}
	return -1;
}
int forthcard(int *cardnum, int q, int p, int *B)
{
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
int planecard(int *cardnum, int q, int p, int s, int *B)//��Ȼ��q��������������С����㣬Ȼ������ʾ���Ǵ�������������Ƿɻ���������Ŀ
{
	if (s == 2)
	{
		for (int i(q + 1); i < max - 1; i++)
		{
			int k(0);
			for (; k < 2; k++)//�ӵ�ǰ����㿪ʼ�������s����ֵ�����Ƿ�Ҳ�Ƿɻ�
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
			for (; k < 3; k++)//�ӵ�ǰ����㿪ʼ�������s����ֵ�����Ƿ�Ҳ�Ƿɻ�
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
int shunzi(int *cardnum, int q, int p, int *B)//��Ȼq��Ϊ��ʼ�����ֵ��p������������
{
	for (int i(q + 1); i < max - p + 1; i++)
	{
		int j = i;
		for (; j < 16; j++)//˳�����2Ϊֹ����Ӧ����ֵ����15+1
		{
			if (cardnum[j] < 1)
				break;
		}
		if (j - i >= p)
		{
			for (int ws(p - 1); ws >= 0; ws--)
			{
				cardnum[i + ws]--;
				B[i + ws]++;
			}
			return 1;
		}
	}
	return -1;
}
int doubleshunzi(int *cardnum, int q, int p, int *B)
{
	for (int i(q + 1); i < max - p + 1; i++)
	{
		int j = i;
		for (; j < 16; j++)//˳�����2Ϊֹ����Ӧ����ֵ����15+1
		{
			if (cardnum[j] < 2)
				break;
		}
		if (j - i >= p)
		{
			for (int ws(p - 1); ws >= 0; ws--)
			{
				cardnum[i + ws] -= 2;
				B[i + ws] += 2;
			}
			return 1;
		}
	}
	return -1;
}

int yingdui(int *B, int *D, int type, int cardm, int q, int p)//��Ϊ�Զ��ֳ��Ƶ�Ӧ��
{
	if (type == 1)
	{
		if (singlecard(B, cardm, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 2)
	{
		if (doublecard(B, cardm, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 3)
	{
		if (triblecard(B, cardm, q, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 4)
	{
		if (bombcard(B, cardm, D) == -1)
		{
			return -1;

		}
	}
	if (type == 5)
	{
		if (forthcard(B, cardm, q, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 6)
	{
		if (planecard(B, cardm, q, p, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 7)
	{
		if (shunzi(B, cardm, p, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 8)
	{
		if (doubleshunzi(B, cardm, p, D) == -1)
		{
			if (bombcard(B, 2, D) == -1)
			{
				return -1;
			}
		}
	}
	if (type == 41)
	{
		return -1;
	}
	return 1;
}
int addnum(int *A)
{
	int allnum(0);
	for (int i(3); i < max; i++)
	{
		allnum += A[i];
	}
	return allnum;
}
int mylegal(int *A)
{
	int flag = 0;
	int cardnum = 0;
	cardnum = addnum(A);
	int maxnum(0);
	int maxzhang(0);
	maxnum = findmax(A, &maxzhang);
	if (maxzhang == 1)
	{
		int myflag2(0);
		for (int i(maxnum); i < max; i++)
		{
			if (A[i] != 1)
			{
				break;
			}
			myflag2++;
		}
		if (myflag2 > 4)
			flag = 1;
	}
	if (maxzhang == 2)
	{
		int myflag2(0);
		for (int i(maxnum); i < max; i++)
		{
			if (A[i] != 2)
			{
				break;
			}
			myflag2++;
		}
		if (myflag2 > 2)
			flag = 1;
	}
	if (cardnum == 1)
	{
		flag = 1;
	}
	if (cardnum == 2)
	{
		for (int i(3); i < max; i++)
		{
			if (A[i] == 2)
			{
				flag = 1;
				break;
			}
		}
		if (A[16] == 1 && A[17] == 1)
		{
			flag = 1;
		}
	}
	if (cardnum == 3)
	{
		for (int i(3); i < max; i++)
		{
			if (A[i] == 3)
			{
				flag = 1;
				break;
			}
		}
	}
	if (cardnum == 4)
	{
		for (int i(3); i < max; i++)
		{
			if (A[i] == 3)
			{
				flag = 1;
				break;
			}
		}
		for (int j(3); j < max; j++)
		{
			if (A[j] == 4)
			{
				flag = 1;
				break;
			}
		}
	}
	if (cardnum == 5)
	{
		int flag2 = 0;
		for (int i(3); i < max; i++)
		{
			if (A[i] == 3)
			{
				A[i] -= 3;
				flag2 += 1;
				break;
			}
		}
		for (int j(3); j < max; j++)
		{
			if (A[j] == 2)
			{
				flag2 += 1;
			}
		}
		if (flag2 == 2)
		{
			flag = 1;
		}
	}
	if (cardnum == 6)
	{
		for (int j(3); j < max - 1; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1);
		else
		{
			int flag2(0);
			for (int j(3); j < max; j++)
			{
				if (A[j] == 4)
				{
					A[j] -= 4;
					flag2 += 1;
					break;
				}
			}
			for (int s(3); s < max; s++)
			{
				if (A[s] == 2)
				{
					flag2 += 1;
					break;
				}
			}
			if (flag2 == 2)
				flag = 1;
		}
	}
	if (cardnum == 8)
	{
		for (int j(3); j < max - 1; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					flag += 1;
					A[j] -= 3;
					A[j + 1] -= 3;
					break;
				}
			}
		}
		if (flag == 1);
		else
		{
			int flag2 = 0;
			for (int s(3); s < max; s++)
			{
				if (A[s] == 4)
				{
					A[s] -= 4;
					flag2 += 1;
					break;
				}
			}
			for (int h(3); h < max; h++)
			{
				if (A[h] == 2)
				{
					A[h] -= 2;
					flag2 += 1;
				}
			}
			if (flag2 == 3)
			{
				flag = 1;
			}
		}
	}
	if (cardnum == 9)
	{
		for (int j(3); j < max - 2; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					if (A[j + 2] == 3)
					{
						flag += 1;
						A[j] -= 3;
						A[j + 1] -= 3;
						A[j + 2] -= 3;
						break;
					}
				}
			}
		}
	}
	if (cardnum == 10)
	{
		int myflag = 0;
		for (int j(3); j < max - 1; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					myflag += 1;
					A[j] -= 3;
					A[j + 1] -= 3;
					break;
				}
			}
		}
		for (int h(3); h < max; h++)
		{
			if (A[h] == 2)
			{
				A[h] -= 2;
				myflag += 1;
			}
		}
		if (myflag == 3)
		{
			flag = 1;
		}

	}
	if (cardnum == 12)
	{

		for (int j(3); j < max - 2; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					if (A[j + 2] == 3)
					{
						flag += 1;
						A[j] -= 3;
						A[j + 1] -= 3;
						A[j + 2] -= 3;
						break;
					}
				}
			}
		}
	}
	if (cardnum == 15)
	{
		int myflag = 0;
		for (int j(3); j < max - 2; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					if (A[j + 2] == 3)
					{
						myflag += 1;
						A[j] -= 3;
						A[j + 1] -= 3;
						A[j + 2] -= 3;
						break;
					}
				}
			}
		}
		for (int w(3); w < max; w++)
		{
			if (A[w] == 2)
			{
				myflag += 1;
			}
		}
		if (myflag = 4)
			flag = 1;
	}
	return flag;
}

class saolei {
public:
	char show[12][12];//玩家数组
	char mine[12][12];//设计者数组
	void init_board();//初始化雷盘
	void print_player();//打印玩家棋盘
	void print_mine();//打印设计者棋盘
	void set_mine();//给设计者棋盘布雷
	int count_mine(int x, int y);//检测周围8个区域雷的个数
	void safe_mine();//避免第一次被雷炸死
	void open_mine(int x, int y);//坐标周围展开函数
	int sweep_mine();//扫雷函数，踩到雷返回1，没有踩到雷返回0
	int count_show();//判断剩余未知区域的个数，个数为雷数时玩家赢
	int minegame();
};

void saolei::init_board()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			show[i][j] = '*';
			mine[i][j] = '0';
		}
	}
}

void saolei::print_player()
{
	system("cls");
	system("color f1");
	int i = 0;
	int j = 0;
	printf("0  ");
	for (i = 1; i < 12 - 1; i++)
	{
		printf("%d ", i);//打印横标
	}
	printf("\n");
	for (i = 1; i < 12 - 2; i++)//打印竖标
	{
		printf("%d  ", i);
		for (j = 1; j < 12 - 1; j++)
		{
			printf("%c ", show[i][j]);
		}
		printf("\n");
	}
	printf("10 ");//开始打印最后一行
	for (i = 1; i < 12 - 1; i++)
	{
		printf("%c ", show[10][i]);
	}
	printf("\n");
}

void saolei::set_mine()//给设计者棋盘布雷
{
	int x = 0;
	int y = 0;
	int count = 10;//雷总数
	while (count)//雷布完后跳出循环
	{
		int x = rand() % 10 + 1;//产生1-10的随机数，在数组下标为1-10的范围内布雷
		int y = rand() % 10 + 1;//产生1-10的随机数，在数组下标为1-10的范围内布雷
		if (mine[x][y] == '0')//找不是雷的地方布雷
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

int saolei::count_mine(int x, int y)
{
	int count = 0;
	if (mine[x - 1][y] == '1')
		count++;
	if (mine[x - 1][y - 1] == '1')
		count++;
	if (mine[x - 1][y + 1] == '1')
		count++;
	if (mine[x][y - 1] == '1')
		count++;
	if (mine[x][y + 1] == '1')
		count++;
	if (mine[x + 1][y - 1] == '1')
		count++;
	if (mine[x + 1][y] == '1')
		count++;
	if (mine[x + 1][y + 1] == '1')
		count++;
	return count;

}

void saolei::safe_mine()
{
	int x = 0;
	int y = 0;
	char ch = 0;
	int ret = 1;
	printf("输入坐标扫雷\n");
	while (1)
	{
		cin >> x;
		cin >> y;//只能输入1-10，输入错误重新输入
		if (((x >= 1) && (x <= 10)) && ((y >= 1) && (y <= 10)))//判断坐标是否有误
		{
			if (mine[x][y] == '1')//第一次踩到雷后补救
			{
				mine[x][y] = '0';
				while (ret)//在其余有空的地方设置一个雷
				{
					int x1 = rand() % 10 + 1;
					int y1 = rand() % 10 + 1;
					if (mine[x1][y1] == '0' && (x != x1 || y != y1))//找不是雷的地方布雷
					{
						mine[x1][y1] = '1';
						ret--;
						break;
					}
				}break;//跳出此函数
				char ch = count_mine(x, y);
				open_mine(x, y);
			}
			if (mine[x][y] == '0')
			{
				char ch = count_mine(x, y);
				open_mine(x, y);
				break;
			}
		}
		else//坐标错误
		{
			printf("请重新输入坐标\n");
		}
	}

}

void saolei::open_mine(int x, int y)
{
	if (show[x][y] == '*' && ((x >= 1) && (x <= 10)) && ((y >= 1) && (y <= 10)))
	{
		if (count_mine(x, y) != 0)
		{
			show[x][y] = count_mine(x, y) + '0';
		}
		else
		{
			show[x][y] = ' ';
			open_mine(x - 1, y);
			open_mine(x - 1, y - 1);
			open_mine(x - 1, y + 1);
			open_mine(x, y - 1);
			open_mine(x, y + 1);
			open_mine(x + 1, y - 1);
			open_mine(x + 1, y);
			open_mine(x + 1, y + 1);
		}
	}
	return;
}

int saolei::sweep_mine()
{
	int x = 0;
	int y = 0;
	printf("请输入坐标扫雷\n");
	cin >> x;
	cin >> y;//只能输入1-10
	if (((x >= 1) && (x <= 10)) && ((y >= 1) && (y <= 10)))
	{
		if (mine[x][y] == '0')//没踩到雷
		{
			open_mine(x, y);
			if (count_show() == 10)//判断剩余未知区域的个数，个数为雷数时玩家赢
			{
				print_mine();
				printf("恭喜你，你赢了\n");
				return 0;
			}
		}
		else if (mine[x][y] == '1')//踩到雷
		{
			return 1;
		}
	}
	else
	{
		printf("请重新输入：\n");
	}
	return 0;//没踩到雷
}

int saolei::count_show()
{
	int i(0);
	int j(0);
	int count(0);
	for (i = 1; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			if (show[i][j] == '*')
			{
				count++;
			}
		}
	}
	return count;
}

void saolei::print_mine()
{
	system("cls");
	system("color f1");
	int i = 0;
    int j = 0;
    printf("0  ");
    for (i = 1; i < 11; i++)
    {
        printf("%d ", i);//打印横标
    }
    printf("\n");
    for (i = 1; i < 10; i++)//打印竖标
    {
        printf("%d  ", i);
        for (j = 1; j < 11; j++)
        {
            printf("%c ", mine[i][j]);
        }
        printf("\n");
    }
    printf("10 ");//开始打印最后一行
    for (i = 1; i < 11; i++)
    {
        printf("%c ", mine[10][i]);
    }
    printf("\n");
}

int saolei::minegame()
{
	int x(0);
	int y(0);
	int ret(0);
	init_board();//初始化棋盘
	set_mine();//给设计者棋盘布雷
	//print_mine();//打印设计者棋盘
	print_player();//打印玩家棋盘
	safe_mine();//避免第一次被炸死
	if (count_show() == 10)//一步就赢的情况
	{
		print_mine();
		cout<<"恭喜你，你赢了获得折扣机会\n";
		Sleep(2000);
		return 1;
	}print_player();//打印玩家棋盘
	while (1)//循环扫雷
	{
		int ret = sweep_mine();//扫雷，踩到雷返回1，没有踩到雷返回0
		if (count_show() == 10)
		{
			print_mine();//打印设计者数组
			cout << "恭喜你，你赢了获得折扣机会\n";
			Sleep(2000);
			return 1;
		}
		if (ret)//判断是否踩到雷
		{
			cout<<"很遗憾，你输了不能享受折扣\n";
			Sleep(1000);
			print_mine();//打印设计者棋盘
			cout << "正在返回上一级" << endl;
			Sleep(2000);
			return 0;
		}print_player();//打印玩家棋盘
	}
	return 0;
}



//下面的是源代码
#include"alldefined.h"
//备注歌曲的序列号和在数组里面的下标是不一样的
#pragma warning(disable : 4996)
int main()
{
	ktvsystem cursys;
	cursys.run();
	return 0;	
}


admin::admin(void)
{
	ID.push_back("NJUCS");
	ID.push_back("NJUCSNB");
	password.push_back("NJUCS1");
	password.push_back("NJUCSNB1");
}

int admin::admenu()
{
	system("cls");
	system("color f1");
	cout << "\n\n\t\t\t＋==============================＋\n";
	cout << "\t\t\t ｜                            \n";
	cout << "\t\t\t ｜ 1->查看所有的歌曲            \n";
	cout << "\t\t\t ｜ 2->添加歌曲                 \n";
	cout << "\t\t\t ｜ 3->批量的导入歌曲            \n";
	cout << "\t\t\t ｜ 4->批量的导出歌曲            \n";
	cout << "\t\t\t ｜ 5->删除歌曲                  \n";
	cout << "\t\t\t ｜ 6->歌曲排序                  \n";
	cout << "\t\t\t ｜ 7->管理员账号操作          \n";
	cout << "\t\t\t ｜ 8->退出                     \n";
	cout << "\t\t\t ｜                             \n";
	cout << "\t\t\t＋==============================＋\n";
	rewind(stdin);
	while (1)
	{
		char op;
		int adnumtemp(0);
		rewind(stdin);
		cin >> op;
		rewind(stdin);
		if (op<'0' || op>'8')
		{
			adnumtemp = 100;
		}
		else
		{
			adnumtemp = op - '0';
		}
		switch (adnumtemp)
		{
		case 1:realprintall(); break;
		case 2:add_song(); break;
		case 3:file_in(); break;
		case 4:file_out(); break;
		case 5:delete_song(); break;
		case 6:sort_song(); break;
		case 7:adminselect(); break;
		case 8:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋==============================＋\n";
		cout << "\t\t\t ｜                            \n";
		cout << "\t\t\t ｜ 1->查看所有的歌曲            \n";
		cout << "\t\t\t ｜ 2->添加歌曲                 \n";
		cout << "\t\t\t ｜ 3->批量的导入歌曲            \n";
		cout << "\t\t\t ｜ 4->批量的导出歌曲            \n";
		cout << "\t\t\t ｜ 5->删除歌曲                  \n";
		cout << "\t\t\t ｜ 6->歌曲排序                  \n";
		cout << "\t\t\t ｜ 7->管理员账号操作          \n";
		cout << "\t\t\t ｜ 8->退出                     \n";
		cout << "\t\t\t ｜                             \n";
		cout << "\t\t\t＋==============================＋\n";
		rewind(stdin);
	}
	return 1;
}

int admin::login()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t｜  *********管理员登陆********  \n");
	printf("\t\t\t｜ 管理员ID：                    \n");
	printf("\t\t\t｜ 管理员密码：                  \n");
	printf("\t\t\t＋==============================＋\n");
	rewind(stdin);

	string IDtemp;
	string passwordtemp;
	int IDlegal(1);
	int passwordlegal(1);
	int boolsuccess(0);
	char  temp = 's';
	int times(0);
	while (!boolsuccess&&times < 3)
	{
		boolsuccess = 1;
		rewind(stdin);
		IDtemp.clear();
		passwordtemp.clear();
		cout << "|********输入你的账号，请注意输入格式********|" << endl;
		while (IDlegal)
		{
			IDlegal = 0;
			temp = 's';
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if ((temp >= 'a'&&temp <= 'z') || (temp >= 'A'&&temp <= 'Z') || (temp >= '0'&&temp <= '9'))
				{
					//putchar('*');
					putchar(temp);
					IDtemp += temp;
				}
				else
				{
					if (temp != '\r' && temp != '\n')
					{
						if ((temp & 0xff) == 8)
						{
							if (IDtemp.length() > 0)
							{
								cout << temp << " " << temp;
								IDtemp.pop_back();
							}
							rewind(stdin);
							continue;
						}
						else
						{
							IDlegal = 1;
							cout << '\r';
							cout << "|*******输入了非法字符，请重新输入*******|" << endl;
							rewind(stdin);
							continue;
						}
					}
					else
					{
						IDlegal = 0;
						cout << endl;
					}

				}
			}
			if (IDtemp.length() >= 12)
			{
				cout << "|*******输入过长，请重新输入*******|" << endl;
				IDlegal = 1;
				IDtemp.clear();
				rewind(stdin);
			}
		}
		IDlegal = 1;
		cout << "|*******输入你的密码，请注意输入格式*******|" << endl;
		while (passwordlegal)
		{
			if (passwordlegal == 1)
			{
				passwordtemp.clear();
			}
			rewind(stdin);
			temp = 's';
			passwordlegal = 0;
			while (temp != '\r'&&temp != '\n')
			{
				temp = _getch();
				if (temp != '\r'&&temp != '\b'&&temp != '\n')
				{
					putchar('*');
					passwordtemp += temp;
				}
				if ((temp & 0xff) == 8)
				{
					if (passwordtemp.length() > 0)
					{
						cout << temp;
						cout << " ";
						cout << temp;
						passwordtemp.pop_back();
					}
					rewind(stdin);
					continue;
				}
			}
			cout << endl;
			if (legalpassword(passwordtemp))
			{
				passwordlegal = 0;
			}
			else
			{
				passwordlegal = 1;
				cout << "|***输入不合法，请重新输入***|" << endl;
			}
		}
		passwordlegal = 1;
		int IDflag = 0;
		for (int i(0); i < ID.size(); i++)
		{
			if (IDtemp == ID[i] && passwordtemp == password[i])
			{
				IDflag = 1;
			}
		}
		if (IDflag == 0)
		{
			boolsuccess = 0;
			times++;
			cout << "|***账号或者密码不对吧***|" << endl;
			cout << "你还有" << 3 - times << "次的机会" << endl;
			continue;
		}
		
	}
	if (times == 3)
	{
		cout << "|*****你根本就不是管理员，再见！******|" << endl;
		Sleep(1500);
		return 0;
	}
	cout << "小伙子，没想到你也是管理员啊" << endl;
	cout << "正在跳转页面" << endl;
	Sleep(1500);
	admenu();
	return 1;
}

int admin::file_out()
{
	fstream myoperate;
	myoperate.open("ktvsong.txt", ofstream::out);
	if (myoperate.fail())
	{
		cout << "文件导出失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int length(0);
	length = mysong.size();
	for (int i(0); i < length; i++)
	{
		string mysinger;
		mysinger = mysong[i].singername;
		myoperate << mysinger << " ";

		string mysongname;
		mysongname = mysong[i].songname;
		myoperate << mysongname << " ";

		string mypinyin;
		mypinyin = mysong[i].pinyin;
		myoperate << mypinyin << " ";
		myoperate << endl;
	}
	cout << "文件导出成功,返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::file_in()
{
	ifstream infile;
	string filesite;
	int sus(0);
	int fai(0);
	cout << "输入导入的文件名" << endl;
	rewind(stdin);
	cin >> filesite;
	infile.open(filesite);
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	int n = mysong.size();
	for (int j(1); !infile.eof(); )
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.judgefrequence = 0;
		temp.playfrequence = 0;
		temp.totalscore = 0;
		if (temp.judgefrequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore / temp.judgefrequence;
		temp.serialnum = j + n;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		int flag = 0;
		for (int i(0); i < mysong.size(); i++)
		{
			if (temp.songname == mysong[i].songname&&temp.singername == mysong[i].singername)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			fai++;
		}
		else
		{
			sus++;
			j++;
			mysong.push_back(temp);
		}
	}
	cout << "文件导入成功" << endl;
	cout << "导入成功 " << sus << "首" << "，失败了 " << fai << "首" << endl;
	cout << "正在返回上一级" << endl;
	Sleep(2000);
	return 1;
}

int admin::add_song()
{
	song temp;
	cout << "input singer name" << endl;
	string singer;
	cin >> singer;
	temp.singername = singer;

	cout << "input song name" << endl;
	rewind(stdin);
	string songname;
	cin >> songname;
	temp.songname = songname;

	cout << "input song pinyin" << endl;
	string mypinyin;
	rewind(stdin);
	cin >> mypinyin;
	temp.pinyin = mypinyin;

	int i = mysong.size();
	temp.serialnum = i + 1;

	initialsong(temp);
	for (int i(0); i < mysong.size(); i++)
	{
		if (temp.singername == mysong[i].singername&&temp.songname == mysong[i].songname)
		{
			cout << "已经有这一首歌了，即将返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
	}
	mysong.push_back(temp);
	cout << "歌曲添加成功正在返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::delete_song()
{
	cout << "请输入你想删除的歌曲的编号" << endl;
	int serielnumber;
	cin >> serielnumber;
	if (serielnumber<1 || serielnumber>mysong.size())
	{
		cout << "输入不合法，即将返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	for (int i(0); i < mysong.size(); i++)
	{
		if (mysong[i].serialnum == serielnumber)
		{
			mysong.erase(mysong.begin() + i);
		}
	}
	for (int i(0); i < mysong.size(); i++)
	{
		mysong[i].serialnum = i + 1;
	}
	cout << "删除成功！！！" << endl;
	Sleep(2000);
	return 1;
}

int admin::initialsong(song&temp)
{
	temp.judgefrequence = 0;
	temp.playstatus = 0;
	temp.ranknum = 0;
	temp.starnum = 0;
	temp.totalscore = 0;
	temp.playfrequence = 0;
	return 0;
}

int admin::printall(vector<song>&A)
{
	int pagenum(1);
	int maxpage(0);
	int songsize = A.size();
	maxpage = songsize / 5;
	if (maxpage * 5 != songsize)
	{
		maxpage++;
	}
	system("cls");
	system("color f1");
	cout << "这是第 " << pagenum << " 页" << endl;
	cout << left << setw(10) << "序列号" << "|";
	cout << left << setw(30) << "歌手" << "|";
	cout << left << setw(30) << "歌名" << "|";
	cout << left << setw(15) << "评分" << "|";
	cout << left << setw(15) << "播放次数" << endl;
	for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
	{
		song temp = A[i + pagenum * 5];
		printsong(temp);
	}
	cout << endl;
	cout << "按上或下翻页。按esc退出浏览模式" << endl;
	char ch;
	while ((ch = _getch()) != 0x1B)
	{
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 80)
			{
				system("cls");
				system("color f1");
				if (pagenum == maxpage)
				{
					cout << "已经是最后一页啦！" << endl;
				}
				else
					pagenum++;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
			if (ch == 72)
			{
				system("cls");
				system("color f1");
				if (pagenum == 1)
				{
					cout << "已经是第一页啦！" << endl;
				}
				else
					pagenum--;
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
			}
		}
		else
		{
			{
				system("cls");
				system("color f1");
				cout << "这是第 " << pagenum << " 页" << endl;
				cout << left << setw(10) << "序列号" << "|";
				cout << left << setw(30) << "歌手" << "|";
				cout << left << setw(30) << "歌名" << "|";
				cout << left << setw(15) << "评分" << "|";
				cout << left << setw(15) << "播放次数" << endl;
				for (int i(-5); i < 0 && (i + pagenum * 5) < songsize; i++)
				{
					song temp = A[i + pagenum * 5];
					printsong(temp);
				}
				cout << endl;
				cout << "按上或下翻页。按esc退出浏览模式" << endl;
				cout << "**********不合法的按键************" << endl;
			}
		}
		rewind(stdin);
	}
	return 0;
}

int admin::printsong(song&temp)
{
	cout << left << setw(10) << temp.serialnum << "|";
	cout << left << setw(30) << temp.singername << "|";
	cout << left << setw(30) << temp.songname << "|";
	cout << left << setw(15) << temp.starnum << "|";
	cout << left << setw(15) << temp.playfrequence << "|";
	if (temp.playstatus == 1)
		cout << "--playing" << " ";
	cout << endl;
	return 0;
}

int admin::changepassword()
{
	string tempID;
	cout << "输入你要改密码的ID" << endl;
	rewind(stdin);
	cin >> tempID;
	int i(0);
	for (; i < ID.size(); i++)
	{
		if (ID[i] == tempID)
		{
			cout << "找到了这个ID" << endl;
			int legalchange(1);
			while (legalchange)
			{
				cout << "请输入新的密码" << endl;
				rewind(stdin);
				string temp;
				cin >> temp;
				if (temp == password[i])
				{
					cout << "和旧密码一样，请重新输入" << endl;
					continue;
				}
				string confirm;
				cout << "请再输入一次确认密码" << endl;
				rewind(stdin);
				cin >> confirm;
				if (temp != confirm)
				{
					cout << "前后密码输入不一致请重新输入" << endl;
					temp.clear();
					confirm.clear();
					rewind(stdin);
					continue;
				}
				if (!legalpassword(temp))
				{
					cout << "输入的密码不合法" << endl;
					temp.clear();
					confirm.clear();
					rewind(stdin);
					continue;
				}
				cout << "密码更改成功，即将为你跳转页面" << endl;
				password[i] = temp;
				legalchange = 0;
			}
			Sleep(2000);
			return 1;
		}
	}
	cout << "没有这个ID，正在返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::sort_song()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t｜ 1->序列号排序                \n");
	printf("\t\t\t｜ 2->评分排序                   \n");
	printf("\t\t\t｜ 3->播放次数排序                 \n");
	printf("\t\t\t｜ 请输入选项[ ]                 \n");
	printf("\t\t\t｜                              \n");
	printf("\t\t\t＋==============================＋\n");
	char i;
	int opnum;
	rewind(stdin);
	cin >> i;
	if (i<'1' || i>'3')
	{
		cout << "输入不合法，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	opnum = i - '0';
	if (opnum == 1)
	{
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	if (opnum == 2)
	{
		sort(mysong.begin(), mysong.end(), comp_starnum);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	if (opnum == 3)
	{
		sort(mysong.begin(), mysong.end(), comp_frenum);
		cout << "正在排序中" << endl;
		Sleep(1000);
		realprintall();
		sort(mysong.begin(), mysong.end(), comp_srerial);
		cout << "正在返回上一级" << endl;
		Sleep(1500);
		return 1;
	}
	cout << "输入不合法，返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int admin::legalID(string A)
{
	int legalnum(1);
	if (A.length() > 20)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z') || (A[i] >= '0'&&A[i] <= '9'))
			legalnum = 1;
		else
		{
			legalnum = 0;
			break;
		}
	}
	return legalnum;

}

int admin::legalpassword(string A)
{
	int wordlegalnum(0);
	int numberlegalnum(0);
	if (A.length() > 12)
	{
		return 0;
	}
	for (int i(0); i < A.length(); i++)
	{
		if ((A[i] >= 'a'&&A[i] <= 'z') || (A[i] >= 'A'&&A[i] <= 'Z'))
		{
			wordlegalnum += 1;
		}
		else
			if ((A[i] >= '0'&&A[i] <= '9'))
			{
				numberlegalnum += 1;
			}
	}
	if (numberlegalnum > 0 && wordlegalnum > 0)
	{
		return 1;
	}
	else
		return 0;
}

int admin::realprintall()
{
	printall(mysong);
	char i;
	cout << "任意输入返回" << endl;
	rewind(stdin);
	cin >> i;
	return 0;
}

int admin::creat_new_account()
{
	string tempID;
	string temppassword;
	cout << "输入新的ID" << endl;
	cin >> tempID;
	if (!legalID(tempID))
	{
		cout << "ID的格式不合法，创建失败，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	vector<string>::iterator iter;
	for (iter = ID.begin(); iter != ID.end(); iter++)
	{
		if (*iter == tempID)
		{
			cout << "本ID已经存在了，返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
	}
	cout << "输入对应的密码，注意格式" << endl;
	rewind(stdin);
	cin >> temppassword;
	if (!legalpassword(temppassword))
	{
		cout << "密码的格式不合法，创建失败，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	ID.push_back(tempID);
	password.push_back(temppassword);
	cout << "创建成功,正在返回上一级" << endl;
	Sleep(2000);
	return 0;

}

int admin::delete_account()
{
	string tempID;
	cout << "输入你要删除的ID名" << endl;
	rewind(stdin);
	cin >> tempID;
	for (int i(0);i<ID.size(); i++)
	{
		if (ID[i] == tempID)
		{
			cout << "找到了这个ID" << endl;
			if (ID.size() == 1)
			{
				cout << "这个已经是最后一个管理员账号了，不得删除" << endl;
				Sleep(2000);
				return 0;
			}
			ID.erase(ID.begin()+i);
			password.erase(password.begin()+i);
			cout << "正在删除这个账号" << endl;
			Sleep(2000);
			return 0;
		}
	}
	cout << "没有这个账号，正在返回上一级" << endl;
	Sleep(2000);
	return 0;
	
}

int admin::adminselect()
{
	system("cls");
	system("color f1");
	cout << "\n\n\t\t\t＋==============================＋\n";
	cout << "\t\t\t ｜                            \n";
	cout << "\t\t\t ｜ 1->修改密码                  \n";
	cout << "\t\t\t ｜ 2->添加管理员                  \n";
	cout << "\t\t\t ｜ 3->删除管理员                  \n";
	cout << "\t\t\t ｜ 4->退出                     \n";
	cout << "\t\t\t ｜                             \n";
	cout << "\t\t\t＋==============================＋\n";
	rewind(stdin);
	while (1)
	{
		char op;
		int adnumtemp(0);
		rewind(stdin);
		cin >> op;
		rewind(stdin);
		if (op<'0' || op>'4')
		{
			adnumtemp = 100;
		}
		else
		{
			adnumtemp = op - '0';
		}
		switch (adnumtemp)
		{
		case 1:changepassword(); break;
		case 2:creat_new_account(); break;
		case 3:delete_account(); break;
		case 4:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl;
		}
		system("cls");
		system("color f1");
		cout << "\n\n\t\t\t＋==============================＋\n";
		cout << "\t\t\t ｜                            \n";
		cout << "\t\t\t ｜ 1->修改密码                  \n";
		cout << "\t\t\t ｜ 2->添加管理员                  \n";
		cout << "\t\t\t ｜ 3->删除管理员                  \n";
		cout << "\t\t\t ｜ 4->退出                     \n";
		cout << "\t\t\t ｜                             \n";
		cout << "\t\t\t＋==============================＋\n";
		rewind(stdin);
	}
	return 1;
}


int ktvsystem::pmainmenu()
{
	while (1)
	{
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋==============================＋\n");
		printf("\t\t\t｜                              \n");
		printf("\t\t\t｜  1->用户直达                 \n");
		printf("\t\t\t｜  2->管理员登陆               \n");
		printf("\t\t\t｜  3->退出系统                \n");
		printf("\t\t\t｜  请输入选项[]                  \n");
		printf("\t\t\t｜                              \n");
		printf("\t\t\t＋==============================＋\n");
		rewind(stdin);
		char temp;
		cin >> temp;
		rewind(stdin);
		if (temp<'1' || temp>'3')
		{
			cout << "输入错误,请重新输入" << endl;
			Sleep(1000);
		}
		else
		{
			syoperationnum = temp - '0';
			return syoperationnum;
		}
	}
}

void ktvsystem::run()
{
	initialsys();
	Sleep(1500);
	int opnumtemp = 100;
	while (opnumtemp != 3)
	{
		opnumtemp = pmainmenu();
		if (opnumtemp != 3 && opnumtemp != 1 && opnumtemp != 2)
		{
			cout << "输入错了，请输入合法的字符！！！" << endl;
			opnumtemp = 111;
			rewind(stdin);
			continue;
		}
		switch (opnumtemp)
		{
		case 3:cout << "再见，感谢使用，欢迎下次再来" << endl; break;
		case 1:B.usmenu(A); break;
		case 2:A.login(); break;
		}
	}
}

int ktvsystem::initialsys()
{
	//初始化歌曲库读入
	system("cls");
	system("color f1");
	cout << "欢迎使用本KTV点歌系统     " << endl;
	cout << "初始化系统中，请稍后    " << endl;
	ifstream infile;
	infile.open("ktvsong.txt");
	if (infile.fail())
	{
		cout << "文件导入失败!!!" << endl;
		Sleep(2000);
		return 0;
	}
	for (int j(1); !infile.eof(); j++)
	{
		song temp;
		infile >> temp.singername;
		infile >> temp.songname;
		infile >> temp.pinyin;
		temp.judgefrequence = 0;
		temp.playfrequence = 0;
		temp.totalscore = 0;
		if (temp.judgefrequence == 0)
		{
			temp.starnum = 0;
		}
		else
			temp.starnum = temp.totalscore / temp.judgefrequence;
		temp.serialnum = j;
		temp.playstatus = 0;
		temp.starnum = 0;
		temp.ranknum = 0;
		A.mysong.push_back(temp);
	}
	A.mysong.pop_back();
	cout << "初始化成功" << endl;
	return 1;
}




user::user()
{
	played_number = 0;
}

int user::usmenu(admin &A)
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋=====================================＋\n");
	printf("\t\t\t｜                                   \n");
	printf("\t\t\t｜ 1->点歌                            \n");
	printf("\t\t\t｜ 2->置顶歌曲                        \n");
	printf("\t\t\t｜ 3->删除歌曲                        \n");
	printf("\t\t\t｜ 4->歌曲评分                        \n");
	printf("\t\t\t｜ 5->查看已点歌曲                    \n");
	printf("\t\t\t｜ 6->播放选择                        \n");
	printf("\t\t\t｜ 7->搜索歌曲                        \n");
	printf("\t\t\t｜ 8->娱乐免单                        \n");
	printf("\t\t\t｜ 9->结账功能                        \n");
	printf("\t\t\t｜ 0->退出                            \n");
	printf("\t\t\t｜                                    \n");
	printf("\t\t\t＋=====================================＋\n");
	rewind(stdin);
	int adnumtemp = 100;
	while (1)
	{
		char temp;
		rewind(stdin);
		cin >> temp;
		if (temp < '0')
		{
			adnumtemp = 100;
		}
		else
			adnumtemp = temp - '0';
		switch (adnumtemp)
		{
		case 1:ordersong(A); break;
		case 2:make_song_top(A); break;
		case 3:delete_song_inqueue(A); break;
		case 4:judge_song(A); break;
		case 5:realsee_playingqueue(A); break;
		case 6:change_song(A); break;
		case 7:search_song(A); break;
		case 8:gameplay(); break;
		case 9:pay_bill(); break;
		case 0:cout << "再见" << endl; return 0;
		default:cout << "输入有误，请重新输入" << endl; Sleep(1000);
		}
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋=====================================＋\n");
		printf("\t\t\t｜                                   \n");
		printf("\t\t\t｜ 1->点歌                            \n");
		printf("\t\t\t｜ 2->置顶歌曲                        \n");
		printf("\t\t\t｜ 3->删除歌曲                        \n");
		printf("\t\t\t｜ 4->歌曲评分                        \n");
		printf("\t\t\t｜ 5->查看已点歌曲                    \n");
		printf("\t\t\t｜ 6->播放选择                        \n");
		printf("\t\t\t｜ 7->搜索歌曲                        \n");
		printf("\t\t\t｜ 8->娱乐免单                        \n");
		printf("\t\t\t｜ 9->结账功能                        \n");
		printf("\t\t\t｜ 0->退出                            \n");
		printf("\t\t\t｜                                    \n");
		printf("\t\t\t＋=====================================＋\n");
		rewind(stdin);
	}
	return 1;
}

int user::ordersong(admin &A)
{
	while (1)
	{
		system("cls");
		system("color f1");
		A.printall(A.mysong);
		cout << "输入你想点的歌曲的编号" << endl;
		int i(0);
		rewind(stdin);
		cin >> i;
		if (i<1 || i>A.mysong.size())
		{
			cout << "输入的号码不合法，返回上一级" << endl;
			Sleep(2000);
			return 0;
		}
		for (int j(0); j < playing_queue.size(); j++)
		{
			if (playing_queue[j] == i)
			{
				cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
				Sleep(2000);
				return 0;
			}
		}
		if (i != -1)
		{
			playing_queue.push_back(i);
			cout << "添加成功" << endl;
		}
		cout << "继续点歌？输入1继续，其他键返回" << endl;
		char nextop;
		rewind(stdin);
		cin >> nextop;
		if (nextop == '1');
		else
			return 1;
	}

}

int user::make_song_top(admin &A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		Sleep(1000);
		return 0;
	}
	cout << "输入你想置顶的歌曲的编号" << endl;
	int i(0);
	rewind(stdin);
	cin >> i;
	if (i<1 || i>A.mysong.size())
	{
		cout << "没有这首歌，返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	playing_queue.insert(playing_queue.begin(), i);
	vector<int>::iterator it;
	for (it = playing_queue.begin() + 1; it != playing_queue.end(); )
	{
		if (*it == i)
		{
			it = playing_queue.erase(it);
		}
		else
		{
			++it;
		}
	}
	cout << "置顶成功，正在返回上一级" << endl;
	Sleep(2000);
	return 0;
}

int user::delete_song_inqueue(admin&A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		cout << "正在返回上一级" << endl;
		Sleep(1000);
		return 0;
	}
	cout << "输入你想删除的歌的编号" << endl;
	int number;
	rewind(stdin);
	cin >> number;
	if (number < 1)
	{
		cout << "输入有误，将会返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	vector<int>::iterator it;
	int flag = 0;
	for (it = playing_queue.begin(); it != playing_queue.end(); )
	{
		if (*it == number)
		{
			it = playing_queue.erase(it);
			flag = 1;
		}
		else
		{
			++it;
		}
	}
	if (flag == 1)
	{
		cout << "删除成功,正在返回上一级" << endl;
	}
	else
	{
		cout << "没有这一首歌" << endl;
	}
	Sleep(2000);
	return 0;
}

int user::judge_song(admin&A)
{
	double star;
	int IDnum;
	system("cls");
	system("color f1");
	A.printall(A.mysong);
	cout << "输入你要评分的歌曲对应的ID号" << endl;
	rewind(stdin);
	cin >> IDnum;
	if (IDnum<1 || IDnum>A.mysong.size())
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "输入你的评分，介于1-5分" << endl;
	rewind(stdin);
	cin >> star;

	if (star < 1 || star>5)
	{
		cout << "输入有误，返回到上一级" << endl;
		Sleep(2000);
		return 0;
	}
	A.mysong[IDnum - 1].totalscore += star;
	A.mysong[IDnum - 1].judgefrequence += 1;
	A.mysong[IDnum - 1].starnum = A.mysong[IDnum - 1].totalscore / A.mysong[IDnum - 1].judgefrequence;
	cout << "评分成功，正在返回上一级" << endl;
	Sleep(2000);
	return 1;
}

int user::see_playingqueue(admin&A)
{
	if (playing_queue.size() == 0)
	{
		cout << "空空如也的歌单，先去点首试试？" << endl;
		Sleep(1000);
		return 0;
	}
	vector<song>result;
	for (int i(0); i < playing_queue.size(); i++)
	{
		result.push_back(A.mysong[playing_queue[i] - 1]);
	}
	A.printall(result);
	return 0;
}

int user::realsee_playingqueue(admin &A)
{
	see_playingqueue(A);
	char i;
	cout << "输入任意数字返回" << endl;
	rewind(stdin);
	cin >> i;
	return 0;
}

int user::change_song(admin &A)
{
	system("cls");
	system("color f1");
	see_playingqueue(A);
	if (playing_queue.size() == 0)
	{
		cout << "准备返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	cout << "请输入你想开始播放的歌曲的编号" << endl;
	int number;
	rewind(stdin);
	cin >> number;
	if (number < 1)
	{
		cout << "输入有问题，准备回到上一级" << endl;
		Sleep(2000);
		return 1;
	}
	for (int i(0); i < playing_queue.size(); i++)
	{
		if (number == playing_queue[i])
		{
			A.mysong[number - 1].playstatus = 1;
			A.mysong[number - 1].playfrequence++;
			for (int i(0); i < playing_queue.size(); i++)
			{
				if (playing_queue[i] == number)
					continue;
				A.mysong[playing_queue[i] - 1].playstatus = 0;
			}
			cout << "切歌成功，准备返回上一级" << endl;
			played_number++;
			Sleep(2000);
			return 0;
		}
	}
	cout << "播放列表没有这首，准备返回上一级" << endl;
	Sleep(2000);
	return 0;

}

int user::search_song(admin &A)
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋==============================＋\n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t｜ 1->歌名搜索                      \n");
	printf("\t\t\t｜ 2->歌手搜索                      \n");
	printf("\t\t\t｜ 3->拼音搜索                      \n");
	printf("\t\t\t｜ 请输入选项[ ]                    \n");
	printf("\t\t\t｜ ｜\n");
	printf("\t\t\t＋==============================＋\n");
	vector<song>result;
	string temp;
	int i(0);
	rewind(stdin);
	cin >> i;
	if (i == 1)
	{
		cout << "输入查找对象的歌名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size(); i++)
		{
			if (A.mysong[i].songname == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	if (i == 2)
	{
		cout << "输入查找对象的歌手名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size(); i++)
		{
			if (A.mysong[i].singername == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	if (i == 3)
	{
		cout << "输入查找对象的拼音名" << endl;
		rewind(stdin);
		cin >> temp;
		for (int i(0); i < A.mysong.size(); i++)
		{
			if (A.mysong[i].pinyin == temp)
			{
				result.push_back(A.mysong[i]);
			}
		}
		if (result.size() == 0)
		{
			cout << "没有找到,返回上一级" << endl;
			Sleep(1500);
			return 0;
		}
		A.printall(result);
		cout << "输入1点歌,其他键返回" << endl;
		rewind(stdin);
		char s;
		cin >> s;
		if (s == '1')
		{
			while (1)
			{
				cout << "输入你想点的歌曲的编号" << endl;
				int i(0);
				rewind(stdin);
				cin >> i;
				if (i<1 || i>A.mysong.size())
				{
					cout << "输入的号码不合法，返回上一级" << endl;
					Sleep(2000);
					return 0;
				}
				for (int j(0); j < playing_queue.size(); j++)
				{
					if (playing_queue[j] == i)
					{
						cout << "歌单里面已经有这一首歌了,准备返回上一级" << endl;
						Sleep(2000);
						return 0;
					}
				}
				if (i != -1)
				{
					playing_queue.push_back(i);
					cout << "添加成功" << endl;
				}
				cout << "继续点歌？输入1继续，其他键返回" << endl;
				char nextop;
				rewind(stdin);
				cin >> nextop;
				if (nextop == '1');
				else
					return 1;
			}
		}
		return 0;
	}
	cout << "输入不合法" << endl;
	return 0;
}

int user::gameplay()
{
	system("cls");
	system("color f1");
	printf("\n\n\t\t\t＋=====================================＋\n");
	printf("\t\t\t｜                                   \n");
	printf("\t\t\t｜ 1->斗地主游戏                            \n");
	printf("\t\t\t｜ 2->扫雷                        \n");
	printf("\t\t\t｜ 3->退出                        \n");
	printf("\t\t\t｜                                    \n");
	printf("\t\t\t＋=====================================＋\n");
	rewind(stdin);
	int adnumtemp = 100;
	while (1)
	{
		char temp;
		rewind(stdin);
		cin >> temp;
		if (temp < '0')
		{
			adnumtemp = 100;
		}
		else
			adnumtemp = temp - '0';
		if (adnumtemp == 1)
		{
			cout << "欢迎使用斗地主游戏功能" << endl;
			string name;
			cout << "输入你的玩家名:" << endl;
			rewind(stdin);
			getline(cin, name);
			time_t t;
			time(&t);
			srand(t);
			DDZPlayer p1("电脑玩家1"), p2("电脑玩家2");
			DDZHumanPlayer p3(name);
			DDZGame g(&p1, &p2, &p3);
			discount += g.run();
			if (discount > 2)
				discount = 2;
			return 0;
		}
		if (adnumtemp == 2)
		{
			saolei bomb;
			discount += bomb.minegame();
			if (discount > 2)
				discount = 2;
		}
		if (adnumtemp == 3)
		{
			cout << "正在返回上一级" << endl;
			Sleep(2000);
			return 0;

		}
		system("cls");
		system("color f1");
		printf("\n\n\t\t\t＋=====================================＋\n");
		printf("\t\t\t｜                                   \n");
		printf("\t\t\t｜ 1->斗地主游戏                            \n");
		printf("\t\t\t｜ 2->2048                        \n");
		printf("\t\t\t｜ 3->退出                        \n");
		printf("\t\t\t｜                                    \n");
		printf("\t\t\t＋=====================================＋\n");
		rewind(stdin);
	}

}

int user::pay_bill()
{
	cout << "正在计算你的账单" << endl;
	Sleep(1500);
	double own_money(0);
	own_money = played_number * 3.0;
	if (played_number == 0)
	{
		cout << "一首歌都还没有唱，无法结账！快去消费，为你返回上一级" << endl;
		Sleep(2000);
		return 0;
	}
	double realmoney(0);
	realmoney = own_money;
	double payed_money(0);
	if (discount == 1)
	{
		realmoney = own_money * 0.8;
	}
	if (discount == 2)
	{
		realmoney = own_money * 0.6;
	}
	int flag(0);
	while (!flag)
	{
		cout << "你唱了 " << played_number << "首歌" << endl;
		cout << "应付 " << realmoney << "元" << endl;
		double paying_money(0.0);
		cout << "输入你付的金额数" << endl;
		cin >> paying_money;
		payed_money += paying_money;
		if (payed_money < realmoney)
		{
			cout << "不够 "<< realmoney-payed_money<<" 元，请继续付款" << endl;
		}
		else
			if (payed_money == realmoney)
			{
				flag = 1;
				cout << "正在为你打印发票" << endl;
				Sleep(1500);
			}
			else
			{
				flag = 1;
				cout << "找零" << payed_money - realmoney << "元，请收好" << endl;
				cout << "正在为你打印发票" << endl;
				Sleep(1500);
			}
	}
	time_t t = time(NULL);
	tm *tp = localtime(&t);
	system("cls");
	system("color f1");
	cout << "|===============================================================  " << endl;
	cout << "|                          超级KTV2.0                  " << endl;
	cout << "|                           用户发票                   " << endl;
	cout << "|     尊敬的客户你好  ：                " << endl;
	cout << "|     你共消费  " << own_money << "  元" << endl;
	cout << "|     折后价  " << realmoney << "  元" << endl;
	cout << "|     支付  " << payed_money << "  元" << endl;
	cout << "|     找零  " << payed_money - realmoney << "  元" << endl;
	cout << "|                                            " << tp->tm_year + 1900 << "年" << tp->tm_mon + 1 << "月" << tp->tm_mday << "日" << endl;
	cout << "|                                            " << tp->tm_hour << "时" << tp->tm_min << "分" << tp->tm_sec << "秒" << endl;
	cout << "|" << endl;
	cout << "|=============================================================== " << endl;
	cout << "按任意键返回上一级" << endl;
	played_number = 0;
	char nonemean;
	cin >> nonemean;
	return 0;
}

