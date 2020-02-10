#include<bits/stdc++.h> 
#include<iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
vector<int> arr;
void krushkals(int v);    //kruskals functin
bool find_set(int a,int b); //for dus
void uni(int a,int b); //for union dus

vector<int>x;
vector<int>y;
vector<int>weight;
ofstream op1;
int main(int argc, char *argv[])
{
	ifstream ip;
	ip.open(argv[1]);
	
	op1.open("mst.txt");
	int z1;
	while(ip>>z1)
	{
		x.push_back(z1);
		ip>>z1;
		y.push_back(z1);
		ip>>z1;
		weight.push_back(z1);
	}
	int total=max(*max_element(x.begin(), x.end()),*max_element(y.begin(), y.end()));
   		krushkals(total+1);
	
	return 0;
}

void krushkals(int v)   //same also discuss in class
{
	arr.resize(v);
	for(int i=0;i<v;i++)
	{
		arr[i]=i;
	}

	for(int i=0;i<x.size();i++)
	{
		int index=0;
		int min=weight[0];
		for(int j=0;j<x.size();j++)
		{
			if(weight[j]<=min)
			{
				min=weight[j];
				index=j;
			}
		}

		if(!find_set(x[index],y[index]))
		{
			op1<<x[index]<<" "<<y[index]<<" "<<weight[index]<<endl;
			uni(x[index],y[index]);
		}
		weight[index]=INT_MAX;
	}

}

bool find_set(int a,int b)
{
	if(arr[a]==arr[b]) //if value same return t
	{
		return true;
	}
	return false;  //else false
}

void uni(int a,int b)
{
	int flag=arr[a];
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]==flag)
		{
			arr[i]=arr[b];
		}
	}
}



