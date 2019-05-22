// Please use UTF-8 encoding so that the comments can be displayed correctly.
// ��עTODO��������Ҫ���Ƶĵط�
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

	// ���ز�������ʹ��������ԱȽϴ�С
	bool operator <(const Card &other) const;
	bool operator >(const Card &other) const;
};


class DDZPlayer {
protected:
	string name;  // �����
	int position;  // ���λ�ñ�ţ�0Ϊ������1Ϊ�����¼ң�2Ϊ�����ϼ�
	vector<Card> hand;  // ����

	int prePos;  //��һ�����Ƶ���λ�ñ�ţ�-1��ʾ��û���˳�����
	vector<Card> prePlay;  // ��һ�����Ƶ��˳���ʲô�ƣ�

	bool legal(vector<Card> cards);  // �жϵ�ǰ���cards�Ƿ�Ϸ�
	void substractFromHand(vector<Card> cards);  // �ӵ�ǰ������ɾȥcards�е���
public:
	DDZPlayer(string name);  // ���캯������ʼ�������
	string getName();
	virtual void draw(Card card);  // ��cards�е��Ƽ�������
	virtual void draw(vector<Card> cards);  // ��cards�е��Ƽ�������
	virtual void setPosition(int pos);  // ��ʼ���ã���������������
	virtual void showHand();  // ��ӡ����
	virtual void observed(int pos, vector<Card> cards);  // �۲⵽��ҳ���
	virtual vector<Card> play();  // �ֵ��Լ�ʱ������ʲô��
	bool leftNoCard();  // �����Ƿ�������ƣ�
};


class DDZGame {
private:
	static int my_random(int i);  // ϴ��ʱ�õ����������
	vector<DDZPlayer*> players;  // ����������ҵ�ָ��
	void showCards(vector<Card> cards);  // ���һ����

public:
	DDZGame(DDZPlayer *p1, DDZPlayer *p2, DDZPlayer *p3);  // ���캯��
	void run();  // ִ����Ϸ����
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
int addnum(int *A);
int mylegal(int *A);

int main1() {
	srand(0x5942B);

	DDZPlayer p1("Alice"), p2("Bob"), p3("Charlie");
	DDZGame g(&p1, &p2, &p3);
	g.run();

	return 0;
}

int main() {
	string name;
	cout << "Please input your name:" << endl;
	getline(cin, name);
	srand(101240);//0x5942B
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
	transferA( prePlay,apreplay);
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
		mytrue=mylegal(acards);
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

void DDZPlayer::substractFromHand(vector<Card> cards) {
	// ���������hand��ɾ��cards������cards�е���hand�����õó�����������������
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
	// ���ص�ǰ����Ϊ��
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
	// �ƾ���Ĺ��캯������Ҫ�������������Ϊ����
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
	// ��������Ϸ����Ҫ����

	// ȡһ�����Ʋ�ϴ��
	vector<Card> deck = Card::get_new_deck();
	random_shuffle(deck.begin(), deck.end(), my_random);

	// ÿ����ҳ�17���ƣ��������ŵ���
	for (int i = 0; i < 54 - 3; ++i)
		players[i % 3]->draw(deck[i]);

	// ���ѡȡ�����������������������
	// * �����ʵ���Լ��Ľе������̣�
	// * ����Ҫ��DDZPlayer�����������Ӧ�ı������洢������ҽе����������
	// * �ͺ���bool DDZPlayer::bid()�������Լ��Ƿ�Ҫ�е�������
	// * �����play()�����ͽе����Ĺ������������̡�
	int landlordPos = my_random(3);
	for (int i = 54 - 3; i < 54; ++i)
		players[landlordPos]->draw(deck[i]);
	for (int i = 0; i < 3; ++i)
		players[i]->setPosition((i + 3 - landlordPos) % 3); // ��������������λ��
	cout << players[landlordPos]->getName() << " is the landlord." << endl;
	int currentPlayer = landlordPos;

	while (true) {
		// ��ǰ��Ҵ���
		vector<Card> currentCards = players[currentPlayer]->play();
		cout << players[currentPlayer]->getName() << " plays:";
		showCards(currentCards);
		// ������ҿ����˴�����ơ���������ֻ���¼ҿ������ϼ�Ҳ�ܿ�����
		for (int i = 0; i < 3; ++i) {
			// ��ҿ�����λ�ñ�Ŷ��Ǵӵ���Ϊ0��ʼ��
			int relativePos = (currentPlayer + 3 - landlordPos) % 3;
			players[i]->observed(relativePos, currentCards);
		}

		// ����ճ����Ƶ����û��������Ϸ����
		if (players[currentPlayer]->leftNoCard()) {
			bool landlordwins = (currentPlayer == landlordPos);
			cout << (landlordwins ? "Landlord wins!" : "Farmers win!") << endl;
			break;
		}

		// ������һ����ҵ��±�
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

void initialop2(int *A, int *B)//A�ǵ�ǰ������ƣ�B�������γ���
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
	for (int i(3); i < max; i++)//�����ܵ�����
	{
		allnum += A[i];
	}
	return allnum;
}

int mylegal(int *A)
{
	int flag = 0;//Ĭ�����ǲ��Ϸ��ģ���ƥ�䵽�Ϸ������͵�ʱ����и�ֵΪ1
	int cardnum = 0;//ʹ���Ƶ�������Ϊ����Ĳ�����׼
	cardnum = addnum(A);
	int maxnum(0);
	int maxzhang(0);
	maxnum = findmax(A, &maxzhang);//num�������������ص����Ƶ�ֵ
	//�Ƚ����ж�˳�Ӻ�����
	if (maxzhang == 1)
	{
		int myflag2(0);
		for (int i(maxnum); i < max ; i++)
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
		for (int j(3); j < max-1; j++)
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
		for (int j(3); j < max-1; j++)
		{
			if (A[j] == 3)
			{
				if (A[j + 1] == 3)
				{
					flag +=1;
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
		for (int j(3); j < max-2; j++)
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
		for (int j(3); j < max-1; j++)
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

		for (int j(3); j < max-2; j++)
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
		for (int j(3); j < max-2; j++)
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
