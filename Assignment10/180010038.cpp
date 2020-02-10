#include<iostream>
#include<vector>
using namespace std;
vector<int>data;
void extended_euclids(int a,int b);
int main(int argc,char*argv[])
{
	if(argc==3)
	{
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	extended_euclids(a,b);
	cout<<data[0]<<" "<<data[1]<<" "<<data[2]<<endl;
	}
	else
	{
		cout<<"give 2 numbers"<<endl;
	}
	return 0;
}
void extended_euclids(int a, int b)
{
	if(b==0)
	{
		data.clear();
		data.push_back(a);
		data.push_back(1);
		data.push_back(0);
	}

	else
	{
		extended_euclids(b,a%b);
		int temp= data[1];
		data[1]= data[2];
		int temo1= a/b;
		data[2]= temp - (temo1*data[2]);
		
	}
}

