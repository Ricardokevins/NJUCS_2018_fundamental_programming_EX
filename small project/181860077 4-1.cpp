// Please use UTF-8 encoding so that the comments can be displayed correctly.
// 标注TODO的是你需要完善的地方
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <functional>
#define max 18
using namespace std;

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

	// 重载操作符，使得牌面可以比较大小
	bool operator <(const Card &other) const;
	bool operator >(const Card &other) const;
};


class DDZPlayer {
protected:
	string name;  // 玩家名
	int position;  // 你的位置编号，0为地主，1为地主下家，2为地主上家
	vector<Card> hand;  // 手牌

	int prePos;  //上一个出牌的人位置编号，-1表示还没有人出过牌
	vector<Card> prePlay;  // 上一个出牌的人出了什么牌？

	bool legal(vector<Card> cards);  // 判断当前打出cards是否合法
	void substractFromHand(vector<Card> cards);  // 从当前手牌中删去cards中的牌
public:
	DDZPlayer(string name);  // 构造函数，初始化玩家名
	string getName();
	virtual void draw(Card card);  // 将cards中的牌加入手牌
	virtual void draw(vector<Card> cards);  // 将cards中的牌加入手牌
	virtual void setPosition(int pos);  // 初始化用，决定地主后设置
	virtual void showHand();  // 打印手牌
	virtual void observed(int pos, vector<Card> cards);  // 观测到玩家出牌
	virtual vector<Card> play();  // 轮到自己时决定出什么牌
	bool leftNoCard();  // 返回是否打完了牌？
};


class DDZGame {
private:
	static int my_random(int i);  // 洗牌时用到的随机函数
	vector<DDZPlayer*> players;  // 保存三个玩家的指针
	void showCards(vector<Card> cards);  // 输出一组牌

public:
	DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // 构造函数
	void run();  // 执行游戏流程
};


class DDZHumanPlayer : public DDZPlayer {
public:
	DDZHumanPlayer(string name) : DDZPlayer(name) {};
	vector<Card> play();
};

// ----------------------------------------------------------------------------
void zifuchuang(vector<Card> cards);
int *transferA(vector<Card> cards, int *A);
int findmax(int *B, int *num);
void jiexi(int* B, int *type, int *cardm, int* q, int *p);
void myprint(int *B);
void transferB(vector<Card> &cards, int *mycard);
int yingdui(int *B, int *D, int type, int cardm, int q, int p);
void myshowCards(vector<Card> cards);
void initialop2(int *A, int *B);

int main() {
	srand(0x5942B);

	DDZPlayer p1("Alice"), p2("Bob"), p3("Charlie");
	DDZGame g(&p1, &p2, &p3);
	g.run();

	return 0;
}


int main2() {
	string name;
	cout << "Please input your name:" << endl;
	getline(cin, name);

	srand(0x5942B);

	DDZPlayer p1("Alice"), p2("Bob");
	DDZHumanPlayer p3(name);
	DDZGame g(&p1, &p2, &p3);
	g.run();

	return 0;
}


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
	// 玩家类的构造函数
	prePos = -1;
}

string DDZPlayer::getName() {
	return name;
}

bool DDZPlayer::legal(vector<Card> cards) {

	// 通过上家打出的牌prePlay和手牌hand判断cards作为打出牌是否合法
	// TODO：（第二题）请补全这个函数
	return true;
}

void DDZPlayer::substractFromHand(vector<Card> cards) {
	// 这个函数从hand中删除cards。假设cards中的牌hand可以拿得出来（否则会出错）。
	sort(hand.begin(), hand.end(), greater<Card>());
	sort(cards.begin(), cards.end(), greater<Card>());
	vector<Card>::iterator i = hand.begin(), k = cards.begin();
	for (vector<Card>::iterator j = hand.begin(); j != hand.end(); ++j) {
		if (k == cards.end() || *k != *j) *(i++) = *j;
		else if (k != cards.end()) ++k;
	}
	hand.erase(i, hand.end());
}

void DDZPlayer::showHand() {
	// 输出玩家名和手牌。
	cout << name << " holds: ";
	for (vector<Card>::iterator i = hand.begin(); i != hand.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

void DDZPlayer::draw(Card card) {
	// 将card加入手牌
	hand.push_back(card);
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::draw(vector<Card> cards) {
	// 将cards中的牌加入手牌
	hand.insert(hand.end(), cards.begin(), cards.end());
	sort(hand.begin(), hand.end(), greater<Card>());
}

void DDZPlayer::setPosition(int pos) {
	position = pos;
}

void DDZPlayer::observed(int pos, vector<Card> cards) {
	// 将上一个出牌的人和出了什么牌记录下来。
	// 如果你想记录更多的信息供你的策略使用，可以改动这个函数。
	// 例如，记录已经有哪些牌被打出（记牌器），以推测场上是否可能还存在炸弹。
	if (cards.size() == 0) return;
	prePos = pos;
	prePlay = cards;
}

vector<Card> DDZPlayer::play() {
	// 轮到你出牌，返回打出的牌。
	// TODO：（第一题）请完善这个函数
	// 如果你使用不同的数据结构进行处理，你可以现将hand变量转换为你使用的结构，
	// 处理过后再将打出的牌转换为vector<Card>，存入card变量。
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
		// 位于prePos的玩家打出了prePlay的牌，你需要出什么牌？
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

	// 你需要保证打出的牌是合法的
	// assert函数在参数为false的时候会使程序报错退出。
	// 这样做的好处是，如果你有没注意到的错误导致程序在此报错退出，
	// 你就知道是在出牌的合法性上出了问题，而不用排查程序的其他部分。
	// assert(legal(cards));

	// 将打出的牌从手牌中删去
	substractFromHand(cards);
	//myshowCards(cards);
	//-myshowCards(hand);
	return cards;
}

bool DDZPlayer::leftNoCard() {
	// 返回当前手牌为空
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
	// 生成一副新牌
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
	// 牌局类的构造函数，需要接受三个玩家作为参数
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

void DDZGame::run() {
	// 斗地主游戏的主要流程

	// 取一副新牌并洗牌
	vector<Card> deck = Card::get_new_deck();
	random_shuffle(deck.begin(), deck.end(), my_random);

	// 每个玩家抽17张牌，留下三张底牌
	for (int i = 0; i < 54 - 3; ++i)
		players[i % 3]->draw(deck[i]);

	// 随机选取地主，发给地主最后三张牌
	// * 你可以实现自己的叫地主流程，
	// * 你需要在DDZPlayer类里面加入相应的变量（存储其他玩家叫地主的情况）
	// * 和函数bool DDZPlayer::bid()（返回自己是否要叫地主）。
	// * 请参阅play()函数和叫地主的规则设计这个流程。
	int landlordPos = my_random(3);
	for (int i = 54 - 3; i < 54; ++i)
		players[landlordPos]->draw(deck[i]);
	for (int i = 0; i < 3; ++i)
		players[i]->setPosition((i + 3 - landlordPos) % 3); // 计算与地主的相对位置
	cout << players[landlordPos]->getName() << " is the landlord." << endl;
	int currentPlayer = landlordPos;

	while (true) {
		// 当前玩家打牌
		vector<Card> currentCards = players[currentPlayer]->play();
		cout << players[currentPlayer]->getName() << " plays:";
		showCards(currentCards);
		// 其他玩家看到了打出的牌。（并不是只有下家看到，上家也能看到）
		for (int i = 0; i < 3; ++i) {
			// 玩家看到的位置编号都是从地主为0开始的
			int relativePos = (currentPlayer + 3 - landlordPos) % 3;
			players[i]->observed(relativePos, currentCards);
		}

		// 如果刚出完牌的玩家没有牌了游戏结束
		if (players[currentPlayer]->leftNoCard()) {
			bool landlordwins = (currentPlayer == landlordPos);
			cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
			break;
		}

		// 计算下一个玩家的下标
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
		while (iss >> c) {
			cards.push_back(Card(c));
		}
		// 现在cards是一个vector<Card>，存储了用户输入的牌
		// 你需要检测输入的牌是持有的牌，并且合法。请完成legal函数。
		if (legal(cards)) {
			break;
		}
		else {
			cout << "Illegal cards. Input again." << endl;
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

int findmax(int *B, int *num)//num就是张数，返回的是牌的值
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

void jiexi(int *B, int *type, int *cardm, int* q, int *p)//type保存的是牌的种类，cardm保存的是牌的数值（最小的），q是带的张数（种类，一张还是一对的），p是连续的张数。
{
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
	if (initmax1 == 2)//排除连对的可能性
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
	for (int i(3); i < 18; i++)//计算总的牌数
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
void initialop2(int *A, int *B)//A是当前玩家手牌，B是他本次出牌
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
		int flag = 0;//查看是否有顺子的存在
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
int triblecard(int *cardnum, int q, int p, int *B)//q是起始点，p是带的牌的种类
{
	for (int i(q + 1); i < max; i++)
	{
		if (cardnum[i] > 2)
		{
			cardnum[i] -= 3;//张数减少避免可能的牌重复出
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
			cardnum[i] += 3;//组合失败就重新回去计算
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
int planecard(int *cardnum, int q, int p, int s, int *B)//仍然是q代表的是三的最小的起点，然后后面表示的是带的张数，最后是飞机的连续数目
{
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
int shunzi(int *cardnum, int q, int p, int *B)//仍然q作为开始点的数值，p是连续的数量
{
	for (int i(q + 1); i < max - p + 1; i++)
	{
		int j = i;
		for (; j < 16; j++)//顺子最大到2为止，对应的数值就是15+1
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
		for (; j < 16; j++)//顺子最大到2为止，对应的数值就是15+1
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
int yingdui(int *B, int *D, int type, int cardm, int q, int p)//作为对对手出牌的应对
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
