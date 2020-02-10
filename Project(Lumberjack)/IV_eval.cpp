//in this i found timy to reach to any node and profit for cutting a tree
#include<iostream>
#include <cstdlib>  //contain absolute fubction
#include<vector>
#include <algorithm>
using namespace std;

vector<int> x;
vector<int> y;
vector<int> profit;
vector<int> weight;
vector<int> height;
vector<int> thick;
vector<int> timy;
vector< vector < int > > proLeft;
vector< vector < int > > proUp;
vector< vector < int > > proRight;
vector< vector < int > > proDown;
void findyProfit(int k,int n);
void left(int a ,int b,int k);
void down(int a,int b,int k);
void up(int a,int b,int k);
void right(int a,int b,int k);
void run(int n,int k,int t,int xInitial,int yInitial);
void run1(int n,int k,int t,int xInitial,int yInitial);
void go_to(int xInitial,int yInitial,int index,char dir);

int main()
{
	int n,t,k;         //n =grid size t=time k=total trees
	cin>>t>>n>>k;      //taking input
	int arr[k][6];     //array for input
	int xInitial=0;
	int yInitial=0;
	for(int i=0;i<k;i++) 
	{
		cin>>arr[i][0]>>arr[i][1]>>arr[i][2]>>arr[i][3]>>arr[i][4]>>arr[i][5] ;
		x.push_back(arr[i][0]);    //copying all values in global vector containg all charachteristics of tree
		y.push_back(arr[i][1]);
		height.push_back(arr[i][2]);
		thick.push_back(arr[i][3]);
		weight.push_back(height[i]*arr[i][3]*arr[i][4]);
		profit.push_back(height[i]*arr[i][3]*arr[i][5]);
	}
			if(k>4000){
				run(n,k,t,xInitial,yInitial);
			}
			else{
				run1(n,k,t,xInitial,yInitial);
			}
	return 0;
}

void findyProfit(int k,int n)
{
		proLeft.resize(k);
		proRight.resize(k);
		proUp.resize(k);
		proDown.resize(k);
	for(int i=0;i<k;i++)
	{
		proUp[i].push_back(profit[i]);
		proDown[i].push_back(profit[i]);
		proLeft[i].push_back(profit[i]);
		proRight[i].push_back(profit[i]);
		left(i,i,k);
		right(i,i,k);
		up(i,i,k);
		down(i,i,k);
	}

}

void run1(int n,int k,int t,int xInitial,int yInitial)
{
	findyProfit(k,n);
	int maxu=0;
	int timu;
	float ratio=0;
	int index;
	int flag=0;
	char dir;
	int indexback;
	for(int i=0;i<k;i++)   //finding timys for each tree
	{
		timy.push_back(abs(x[i]-xInitial)+abs(y[i]-yInitial)+thick[i]);
	}

	for(int i=1;i<k;i++)
	{
		int max1=max(proLeft[i][0],proRight[i][0]);
   	    int max2=max(proUp[i][0],proDown[i][0]);
   	    int max3=max(max1,max2);
   	    if(timy[i]<=t)
   	    {
   	    	if((float)(max3/timy[i])>ratio)
   	    	{
   	    		ratio=max3/timy[i];
   	    		maxu=max3;
   	    		timu=timy[i];
   	    		index=i;
   	    		indexback=index;
   	    		flag=1;
   	    	}

   	    	if((float)(max3/timy[i])==ratio)
   	    	{
   	    		timu=min(timu,timy[i]);
   	    		if(timu==timy[i])       //this thing i add new
   	    		{
   	    			index=i;
   	    		}
   	    		else
   	    		{
   	    			index=indexback;
   	    		}
   	    		flag=1;
   	    	}
   	    }

	}

	 	if(flag==1)
   	    {
   	    	//finding which direction to cut
   	    	int cuttree;
   	    	int xlater;
   	    	int ylater;
   	    	if(maxu==proLeft[index][0])
   	    	{
   	    		dir='l';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proLeft[index].push_back(index);
   	    		cuttree=proLeft[index].size();
   	    		sort(proLeft[index].begin()+1,proLeft[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proLeft[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proRight[index][0])
   	    	{
   	    		dir='r';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proRight[index].push_back(index);
   	    		cuttree=proRight[index].size();
   	    		sort(proRight[index].begin()+1,proRight[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proRight[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proUp[index][0])
   	    	{
   	    		dir='u';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proUp[index].push_back(index);
   	    		cuttree=proUp[index].size();
   	    		sort(proUp[index].begin()+1,proUp[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proUp[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proDown[index][0])
   	    	{
   	    		dir='d';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proDown[index].push_back(index);
   	    		cuttree=proDown[index].size();
   	    		sort(proDown[index].begin()+1,proDown[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proDown[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	timy.clear();
   	    	run1(n,k-cuttree+1,t-timu,xlater,ylater);
   	    }
}

void run(int n,int k,int t,int xInitial,int yInitial)
{
	findyProfit(k,n);
	int maxu=0;
	int timu;
	int index;
	int flag=0;
	char dir;
	int indexback;
	for(int i=0;i<k;i++)   //finding timys for each tree
	{
		timy.push_back(abs(x[i]-xInitial)+abs(y[i]-yInitial)+thick[i]);
	}

	for(int i=1;i<k;i++)
	{
		int max1=max(proLeft[i][0],proRight[i][0]);
   	    int max2=max(proUp[i][0],proDown[i][0]);
   	    int max3=max(max1,max2);
   	    if(timy[i]<=t)
   	    {
   	    	if(max3>maxu)
   	    	{
   	    		maxu=max3;
   	    		timu=timy[i];
   	    		index=i;
   	    		indexback=index;
   	    		flag=1;
   	    	}

   	    	if(max3==maxu)
   	    	{
   	    		timu=min(timu,timy[i]);
   	    		if(timu==timy[i])       //this thing i add new
   	    		{
   	    			index=i;
   	    		}
   	    		else
   	    		{
   	    			index=indexback;
   	    		}
   	    		flag=1;
   	    	}
   	    }

	}

	 	if(flag==1)
   	    {
   	    	//finding which direction to cut
   	    	int cuttree;
   	    	int xlater;
   	    	int ylater;
   	    	if(maxu==proLeft[index][0])
   	    	{
   	    		dir='l';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proLeft[index].push_back(index);
   	    		cuttree=proLeft[index].size();
   	    		sort(proLeft[index].begin()+1,proLeft[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proLeft[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proRight[index][0])
   	    	{
   	    		dir='r';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proRight[index].push_back(index);
   	    		cuttree=proRight[index].size();
   	    		sort(proRight[index].begin()+1,proRight[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proRight[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proUp[index][0])
   	    	{
   	    		dir='u';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proUp[index].push_back(index);
   	    		cuttree=proUp[index].size();
   	    		sort(proUp[index].begin()+1,proUp[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proUp[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	else if(maxu==proDown[index][0])
   	    	{
   	    		dir='d';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proDown[index].push_back(index);
   	    		cuttree=proDown[index].size();
   	    		sort(proDown[index].begin()+1,proDown[index].end());
   	    		for(int j=1;j<cuttree;j++)
   	    		{
   	    			int i=proDown[index][j]-j+1;
   	    			x.erase(x.begin()+i);
   	    			y.erase(y.begin()+i);
   	    			weight.erase(weight.begin()+i);
   	    			height.erase(height.begin()+i);
   	    			thick.erase(thick.begin()+i);
   	    			profit.erase(profit.begin()+i);
   	    		}
   	    		proLeft.clear();
   	    		proRight.clear();
   	    		proUp.clear();
   	    		proDown.clear();
   	    	}
   	    	timy.clear();
   	    	run(n,k-cuttree+1,t-timu,xlater,ylater);
   	    }
}



void left(int a,int b,int k)
{
	for(int i=0;i<k;i++)
	{
		if(y[i]==y[a])
			{                
				if(x[i]<x[a])    //for left
				{
					if(weight[i]<weight[a] && height[a]>(x[a]-x[i]))
					{
						if(!(count(proLeft[b].begin()+1,proLeft[b].end(),i)))
						{
							proLeft[b].push_back(i);
							proLeft[b][0]+=profit[i];
							left(i,b,k);
						}
						

					}
				}

			}
	}
}


void right(int a,int b,int k)
{
	for(int i=0;i<k;i++)
	{
		if(y[i]==y[a])
			{                
				if(x[i]>x[a])    //for right
				{
					if(weight[i]<weight[a] && height[a]>(x[i]-x[a]))
					{
						if((count(proRight[b].begin()+1,proRight[b].end(),i))==0)
						{
							proRight[b].push_back(i);
							proRight[b][0]+=profit[i];
							right(i,b,k);
						}

					}
				}

			}
	}
}

void up(int a,int b,int k)
{
	for(int i=0;i<k;i++)
	{
		if(x[i]==x[a])
			{                
				if(y[i]>y[a])    //for up
				{
					if(weight[i]<weight[a] && height[a]>(y[i]-y[a]))
					{
						if((count(proUp[b].begin()+1,proUp[b].end(),i))==0)
						{
							proUp[b].push_back(i);
							proUp[b][0]+=profit[i];
							up(i,b,k);
						}

					}
				}

			}
	}
}

void down(int a,int b,int k)
{
	for(int i=0;i<k;i++)
	{
		if(x[i]==x[a])
			{                
				if(y[i]<y[a])    //for down
				{
					if(weight[i]<weight[a] && height[a]>(y[a]-y[i]))
					{
						if((count(proDown[b].begin()+1,proDown[b].end(),i))==0)
						{
							proDown[b].push_back(i);
							proDown[b][0]+=profit[i];
							down(i,b,k);
						}

					}
				}

			}
	}
}

void go_to(int xInitial,int yInitial,int index,char dir)
{
	if(x[index]>xInitial)
	{
		for(int i=0;i<(x[index]-xInitial);i++)
		{
			cout<<"move right"<<endl;
		}
	}

	if(x[index]<xInitial)
	{
		for(int i=0;i<(xInitial-x[index]);i++)
		{
			cout<<"move left"<<endl;
		}
	}

	if(y[index]>yInitial)
	{
		for(int i=0;i<(y[index]-yInitial);i++)
		{
			cout<<"move up"<<endl;
		}
	}

	if(y[index]<yInitial)
	{
		for(int i=0;i<(yInitial-y[index]);i++)
		{
			cout<<"move down"<<endl;
		}
	}

	if(dir=='l')
	{
		cout<<"cut left"<<endl;
	}

	else if(dir=='r')
	{
		cout<<"cut right"<<endl;
	}

	else if(dir=='u')
	{
		cout<<"cut up"<<endl;
	}

	else if(dir=='d')
	{
		cout<<"cut down"<<endl;
	}

}