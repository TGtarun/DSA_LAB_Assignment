//Project 1 First Part Cul Cutters :)
#include<iostream>
#include <cstdlib>  //contains absolute fubction
#include<vector>
#include <algorithm>
using namespace std;

vector<int> timy;
vector<int> x;
vector<int> y;
vector<int> profit;
vector<int> weight;
vector<int> height;
vector<int> thick;




void run(int n,int k,int t,int xInitial,int yInitial);                
void left(vector< vector < int > > &proLeft,int a ,int b,int k);
void down(vector< vector < int > > &proDown ,int a,int b,int k);
void up(vector< vector < int > > &proUp ,int a,int b,int k,int n);
void right(vector< vector < int > > &proRight ,int a,int b,int k,int n);
void go_to(int index,int xInitial,int yInitial, int n,int time,int k);
void go_to_extend(int index,int xInitial,int yInitial,int time);

int xPos = 0 ;           // Our Location
int yPos = 0 ;

int main()
{
	int n,t,k;         //n =grid size t=timy k=total trees
	cin>>t>>n>>k;      //taking input
	int arr[k][6];
	int xInitial=0;
	int yInitial=0;
	for(int i=0;i<k;i++)
	{
		cin>>arr[i][0]>>arr[i][1]>>arr[i][2]>>arr[i][3]>>arr[i][4]>>arr[i][5] ;       // Taking input as array and storing in vector
		x.push_back(arr[i][0]);
		y.push_back(arr[i][1]);
		height.push_back(arr[i][2]);
		thick.push_back(arr[i][3]);
		weight.push_back(height[i]*arr[i][3]*arr[i][4]);
		profit.push_back(height[i]*arr[i][3]*arr[i][5]);
	}

	run(n,k,t,xInitial,yInitial);
	return 0;
}



void run(int n,int k,int t,int xInitial,int yInitial)
{
	
	for(int i=0;i<k;i++)   //finding time for each tree
	{
		timy.push_back(abs(x[i]-xInitial)+abs(y[i]-yInitial)+thick[i]);
	}

	vector< vector < int > > proLeft(k);
	vector< vector < int > > proUp(k);
	vector< vector < int > > proRight(k);
	vector< vector < int > > proDown(k);
	int array[k][4];
	int max_profit=0;
	int index;
	int timeComp=0;
	int extendedIndex;
	int extentTimePro=0;

	for(int i=0;i<k;i++)        //finding max profit from each tree
	{

   	    if(timy[i]<t)
   	    {
   	    	index=i;
   	    	break;

   	    }
   	}    

   	 
	go_to(index,xInitial,yInitial,n,t,k);       // Going to that position

}


void go_to(int index,int xInitial,int yInitial ,int n,int t,int k )
{   int counter=0 ;
	if(x[index]>xInitial)
	{
		for(int i=0;i<(x[index]-xInitial) && counter<t;i++ , counter++)
		{
			cout<<"move right"<<endl;
			xPos++ ;                       // Updating our location
		}
	}

	if(x[index]<xInitial)
	{
		for(int i=0;i<(xInitial-x[index]) && counter<t;i++, counter++)
		{
			cout<<"move left"<<endl;
			xPos-- ;
		}
	}

	if(y[index]>yInitial)
	{
		for(int i=0;i<(y[index]-yInitial) && counter<t;i++, counter++)
		{
			cout<<"move up"<<endl;
			yPos++;
		}
	}

	if(y[index]<yInitial)
	{
		for(int i=0;i<(yInitial-y[index])&& counter<t;i++, counter++)
		{
			cout<<"move down"<<endl;
			yPos--;
		}
	}
    int flag = 0 ; int RemTime ;int  i =0 ;
    for( i=0; i<k ; i++ )
    	{  if(xPos==x[i] && yPos==y[i])
    		{  flag = 1 ;
               RemTime = t - counter ;
               break;
    		}


    	}
   

    if( flag==1 && RemTime>=thick[i])
	{ if(y[index]==n)
	{ 
		cout<<"cut down"<<endl;
    }
    else if(y[index]==0)
	{ 
		cout<<"cut up"<<endl;
    }
    else if(x[index]==n)
	{ 
		cout<<"cut left"<<endl;
    }
    else if(x[index]==0)
	{ 
		cout<<"cut right"<<endl;
    }
    else
    	{  cout<<"cut up" ;}
}
}

