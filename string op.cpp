#include<iostream>
#include<cstdlib>
using namespace std;



void mystrcopy(char *a, char *b) {
	while (*b != '\0') {
		*a = *b;
		a++;
		b++;
	}
	*a = '\0';
}
int mystrlen(char *a) 
{
	int num(0);
	while(*a!='\0') 
	{
		num++;
		a++;
	}
	return num;
}
void mystrcat(char *a,char *b)
{
	int numa=mystrlen(a);
	for(int i(0);i<numa;i++)
	{
		a++;
	}
	while(*b!='\0')
	{
		*a=*b;
		a++;
		b++;
	}
	*a='\0';
	
}
int equalstr(char*a,char *b)
{
	int flag(1);
	while(*a!='\0'&&*b!='\0')
	{
		if(*a!=*b)
		{
			flag=0;
			return flag;
		}
		a++;
		b++;
	}
	if(*a!=*b)
	{
		flag=0;
		return flag;
	}
	return flag;

}


//²âÊÔ 
int main()
{
	char A[30];
	char B[30];
	cin>>A;

	int numa=mystrlen(A);
	mystrcopy(B,A);
	cout<<A<<endl;
	cout<<B<<endl<<endl;
	mystrcat(A,B);
	cout<<A<<endl;
	cout<<B<<endl<<endl;
	mystrcopy(A,B);
	cout<<equalstr(A,B)<<endl;
	
	return 0;
	
}
