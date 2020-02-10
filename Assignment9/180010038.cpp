#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;
vector<string> words;
vector<vector<string>> work;
int main(int argc,char* argv[])
{
	ifstream io1;
	ifstream io2;
	ofstream op1;
	io1.open(argv[1]);
	io2.open(argv[3]);
	op1.open("anagrams.txt");
	int m=atoi(argv[2]);
	string str;
	work.resize(m);
	while(io1>>str)
	{
		words.push_back(str);
		int sum=0;
		for (int i = 0; str[i] != '\0'; i++)
        	sum = sum + str[i];
        int index =sum%m;
        work[index].insert(work[index].begin(),str);
        
	}

	string str1;
	while(io2>>str1)
	{
		sort(str1.begin(),str1.end());
		int sum=0;
		for (int i = 0; str1[i] != '\0'; i++)
        	sum = sum + str1[i];
        int index =sum%m;
        for(int j=0;j<work[index].size();j++)
        {
        	string str2= work[index][j];
        	sort(str2.begin(),str2.end());
        	if(str1==str2)
        	{
        		op1<<work[index][j]<<" ";
        	}

        }
        op1<<endl;
	}
return 0;
}