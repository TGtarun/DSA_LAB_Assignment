//in this i found timy to reach to any node and profit for cutting a tree
#include<iostream>
#include <cstdlib>  //contain absolute or modulus function
#include<vector>
#include <algorithm>
using namespace std;

vector<int> x;   //vector contain x,y,height,profit etc things of all tree
vector<int> y;
vector<int> profit;
vector<int> weight;
vector<int> height;
vector<int> thick;
vector<int> timy;  //vector contain time to cut each tree from 0,0
vector< vector < int > > proLeft;  //2d vector contain index of all tree which fall if we cut a tree in l,r,u,d
vector< vector < int > > proUp;
vector< vector < int > > proRight;
vector< vector < int > > proDown;
/*void vert(int a,int b,int k,int n);
void horz(int a,int b,int k,int n);*/
void findyProfit(int k,int n);  //find index describe above
void left(int a ,int b,int k);  //func for find left,right,up down index
void down(int a,int b,int k);
void up(int a,int b,int k,int n);
void right(int a,int b,int k,int n);
void run(int n,int k,int t,int xInitial,int yInitial);  //func which check which index to cut
void go_to(int xInitial,int yInitial,int index,char dir);  //print movement 

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

	run(n,k,t,xInitial,yInitial);  
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
		/*horz(i,i,k,n);
		vert(i,i,k,n);*/
		proUp[i].push_back(profit[i]);  //first element of each vector is their net profit in that direction
		proDown[i].push_back(profit[i]);
		proLeft[i].push_back(profit[i]);
		proRight[i].push_back(profit[i]);
		left(i,i,k);    //finding index in left
		right(i,i,k,n);
		up(i,i,k,n);
		down(i,i,k);
	}

}

void run(int n,int k,int t,int xInitial,int yInitial)
{
	findyProfit(k,n);
	int maxu=0;
	int timu;
	int index;
	int flag=0;  //flag is the sign that we find a tree to cut
	char dir;
	int indexback;
	for(int i=0;i<k;i++)   //finding timys for each tree
	{
		timy.push_back(abs(x[i]-xInitial)+abs(y[i]-yInitial)+thick[i]);
	}

	for(int i=0;i<k;i++)
	{
		int max1=max(proLeft[i][0],proRight[i][0]);
   	    int max2=max(proUp[i][0],proDown[i][0]);
   	    int max3=max(max1,max2);  //find max profit for each tree in any direction
   	    if(timy[i]<=t)     //find overall max profit in all tree which is in given time limit
   	    {
   	    	if(max3>maxu)
   	    	{
   	    		maxu=max3;
   	    		timu=timy[i];
   	    		index=i;   //setting index
   	    		indexback=index;
   	    		flag=1;   //flag is the sign that we find a tree to cut
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

	 	if(flag==1)   //we find a tree to cut at index 
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
   	    		proLeft[index].push_back(index);  //also push tree at index
   	    		cuttree=proLeft[index].size();
   	    		sort(proLeft[index].begin()+1,proLeft[index].end());
   	    		for(int j=1;j<cuttree;j++)  //clearing data of all trees
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
   	    	else if(maxu==proRight[index][0])  //check dir
   	    	{
   	    		dir='r';
   	    		go_to(xInitial,yInitial,index,dir);
   	    		xlater=x[index];
   	    		ylater=y[index];
   	    		proRight[index].push_back(index);
   	    		cuttree=proRight[index].size();
   	    		sort(proRight[index].begin()+1,proRight[index].end());
   	    		for(int j=1;j<cuttree;j++)   //erase data
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



void left(int a,int b,int k)  //find profits when tree fall in left direction
{
	for(int i=0;i<k;i++)
	{
		if(y[i]==y[a])
			{                
				if(x[i]<x[a])    //for left //check condition
				{
					if(weight[i]<weight[a] && height[a]>(x[a]-x[i]))
					{
						if(!(count(proLeft[b].begin()+1,proLeft[b].end(),i)))
						{
							proLeft[b].push_back(i);   //pushing index of fallen tree
							proLeft[b][0]+=profit[i];  //increasing profit
							left(i,b,k);  //reciursion
						}
						

					}
				}

			}
	}
}


void right(int a,int b,int k,int n)   //find profits when tree fall in right direction
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
							right(i,b,k,n);
						}

					}
				}

			}
	}
}

void up(int a,int b,int k,int n)  //find profits when tree fall in up direction
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
							up(i,b,k,n);
						}

					}
				}

			}
	}
}

void down(int a,int b,int k)   //find profits when tree fall in downward direction
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

void go_to(int xInitial,int yInitial,int index,char dir)  //print output
{
	if(x[index]>xInitial)   //checking position and decide
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

	if(dir=='l')   //cjeck direction and decide
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

