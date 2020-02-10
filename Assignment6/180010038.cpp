#include<bits/stdc++.h> 
#include<iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
vector<int> vec;
vector<vector<int>> vect;
vector<int>color;
vector<int>dincy;
vector<int>discovery;
vector<int>finish;
int timy;
void bfs(int s);
void dfs_visit(int u);
void dfs(int s);
int main(int argc, char *argv[])
{
	ifstream ip;
	ip.open(argv[1]);
	ofstream op1;
	ofstream op2;
	op1.open("sd.txt");
	op2.open("ts.txt");
	int s=atoi(argv[2]);
	int z1;
	while(ip>>z1)
	{
		vec.push_back(z1);
	}
	int total=*max_element(vec.begin(), vec.end());
	vect.resize(total+1);
	for(int i=0;i<total+1;i++)
	{
		color.push_back(0);
		dincy.push_back(-1);
	}
	color[s]=1;
	dincy[s]=0;
	for(int i=0;i<vec.size();i+=2)
	{
		vect[vec[i]].push_back(vec[i+1]);
	}
	bfs(s);
	for(int i=0;i<total+1;i++)
	{
		op1<<i<<" "<<dincy[i]<<endl;
	}
	color.clear();
	for(int i=0;i<total+1;i++)
	{
		color.push_back(0);
		discovery.push_back(-1);
		finish.push_back(-1);
	}
	dfs(s);
	for(int i=0;i<total+1;i++)
	{
		int max=0;
		int index;
		for(int j=0;j<total+1;j++)
		{
			if(finish[j]>max)
			{
				max=finish[j];
				index=j;
			}

		}
		 finish[index]=-1;
		 op2<<index<<endl;
	}

	return 0;
}

void bfs(int s)
{
	vector<int>queue;
	queue.push_back(s);
	while(queue.size()!=0)
	{
		int u=queue[0];
		queue.erase(queue.begin());
		for(int i=0;i<vect[u].size();i++)
		{
			int v=vect[u][i];
			if(color[v]==0)
			{
				color[v]=1;
				dincy[v]=dincy[u]+1;
				queue.push_back(v);
			}
		}
	}
}

void dfs(int s)
{
	timy=0;
	for(int i=0;i<vect.size();i++)
	{
		if(color[i]==0)
		{
			dfs_visit(i);
		}
	}
}

void dfs_visit(int u)
{
	timy=timy+1;
	discovery[u]=timy;
	color[u]=1;
	for(int i=0;i<vect[u].size();i++)
		{
			int v=vect[u][i];
			if(color[v]==0)
			{
				color[v]=1;
				dfs_visit(v);
			}
		}

		timy=timy+1;
		finish[u]=timy;
}




