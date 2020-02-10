#include<bits/stdc++.h> 
#include<iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
vector<int> x;
vector<int> y;
vector<int> weight;
vector<vector<int>> vect;
vector<int> dincy;
vector<int> selected;
vector<int> dincyfinal;
void relax(int u,int v,int w);
void dijistra(int s);
vector<int>color;
int main(int argc, char *argv[])
{
	ifstream ip;
	ip.open(argv[1]);
	ofstream op1;
	op1.open("output.txt");
	int s=atoi(argv[2]);
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
	//total verices total+1
	vect.resize(total+1);
	for(int i=0;i<x.size();i++)
	{
		vect[x[i]].push_back(y[i]);
		vect[x[i]].push_back(weight[i]);
	}
	/*for(int i=0;i<vect.size();i++)
	{
		cout<<i<<" -> ";
		for(int j=0;j<vect[i].size();j++)
		{
			cout<<vect[i][j]<<" ";
		}
		cout<<endl;
	}*/
	for(int i=0;i<total+1;i++)
	{
		dincy.push_back(INT_MAX);
		color.push_back(0);
	}
	dincy[s]=0;

	//works fine adjacency list works
	dijistra(s);               //problem in dijistra only
	//cout<<selected.size();
	for(int i=0;i<selected.size();i++)
	{
		op1<<selected[i]<<" "<<dincyfinal[i]<<endl;
	}

	return 0;
}

void dijistra(int s)
{
	for(int i=0;i<vect.size();i++)
	{
		int index=-1;
		int min=INT_MAX;
		for(int k=0;k<dincy.size();k++)
		{
			if(color[k]==0)
			{
				if(dincy[k]<min)
				{
					index=k;
					min=dincy[k];
				}
			}
		}
		if(index>=0)
		{
			selected.push_back(index);
			dincyfinal.push_back(dincy[index]);
			for(int j=0;j<vect[index].size();j+=2)
			{
				relax(index,vect[index][j],vect[index][j+1]);
			}
			color[index]=1;
		}

		else
		{
			for(int k=0;k<dincy.size();k++)
			{
				if(color[k]==0)
				{
					selected.push_back(k);
					dincyfinal.push_back(-1);
				}
			}
			return;
		}
		
	}
}

void relax(int u,int v,int w)
{
	if(dincy[v]>(dincy[u]+w))
	{
		dincy[v]=dincy[u]+w;
	}
}
