#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<cmath>
#include<vector>
using namespace std;

vector<int> vec;
void radix_sort(int d);
void counting_sort(int exp);
int main(int argc,char** argv)
{
	int d;
	d=atoi(argv[2]);
	ifstream fpp;
	fpp.open(argv[1]);
	ofstream out;
	out.open("radix.txt");
	int num;
	while(fpp>>num)
	{
		vec.push_back(num);
	}

	radix_sort(d);

	for(int i=0;i<vec.size();i++)
	{
		out<<vec[i]<<"\n";
	}

}

void radix_sort(int d)
{
	for(int i=0;i<d;i++)
	{
		counting_sort(pow(10,i));
	}
}

void counting_sort(int exp)
{
	//digit at position is ranging from 0 to 9 total 10 digit
	int barr[vec.size()];
	int arr[10]={0};
	for(int i=0;i<vec.size();i++)
	{
		int x = (vec[i]/exp)%10;
		arr[x]++;
	}

	for(int j=1;j<10;j++)
	{
		arr[j]+=arr[j-1];
	}

	for(int k=vec.size()-1;k>=0;k--)
	{
		int x = (vec[k]/exp)%10;
		barr[arr[x]-1]=vec[k];
		arr[x]--;
	}

	for(int l=0;l<vec.size();l++)
	{
		vec[l]=barr[l];
	}
}