#include<iostream>
#include<cstdlib>
#include<fstream>

using namespace std;

void to_lower(char *s) {
	while(*s!='\0') {
		if((*s<='Z')&&(*s>='A')) {
			*s=*s-'A'+'a';
		}
		s++;
	}
}

int mystrlen(char *s) {
	int num(0);
	while(*s!='\0') {
		num++;
		s++;
	}
	return num;
}


int str_equal(char *s1,char *s2) {
	int flag=1;
	int num1=mystrlen(s1);
	int num2=mystrlen(s2);
	int min(0);
	if(num1!=num2) {
		flag=0;
		return flag;
	}
	while(*s1!='\0') {
		if(*s1!=*s2) {
			flag=0;
			break;
		}
		s1++;
		s2++;
	}
	return flag;

}

bool isChar(char ch) {
	if((ch >= 'a' && ch <= 'z')
	        ||ch >= 'A' && ch <= 'Z')
		return true;
	else
		return false;
}

int main() {
	
	ifstream fin;
	fin.open("article.txt");
	if(!fin.good()){
		cout<<"error"<<endl;
		return 0;
	}
	char A[2000]={'\0'};
	fin.getline(A,2000);
	char B[40];
	cin>>B;
	to_lower(B);
	to_lower(A);
	int i(0);
	int flag(0);
	while(A[i]!='\0')
	{
		char C[40];
		for(int j(0);isChar(A[i]);i++,j++)
		{
			C[j]=A[i];
			C[j+1]='\0';
		}
		if(str_equal(C,B))
		{
			cout<<"True"<<endl;
			flag=1;
			return 0;
		}
		i++;
		
	}
	if(flag==0)
	{
		cout<<"Flase"<<endl;
	} 
	return 0;
}

