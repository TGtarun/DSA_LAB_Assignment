#include <iostream>
#include <fstream>                                 //for file library
using namespace std;
struct Node                                        //structre Node contain key , prev pointer and next pointer
{
	int data;
	Node* prev;
	Node* next;
};
Node* findy(int d);                               //function to find presence of a number in dll

Node* heady=NULL;                                 //node pointer to head 

int main(int argc, char *argv[])
{
	ifstream input;                               //input and output files and open 
	input.open(argv[1]);                             
	ofstream output1;
	ofstream output2;
	output1.open("stack1.txt");
	output2.open("queue1.txt");
	ofstream output3;
	output3.open("dll1.txt");

	char ch;
	int n=atoi(argv[2]);                          //n=capacity of a array
	int top=-1;                                   //for stack
	int arrStack[n];                              //array for stack

	int head=0;                                   //initialise head and tail for Queue
	int tail=0;
	int arrQueue[n];                              //array for Queue

	
	while(input>>ch)                              //taking input from file
	{
		int d;
		                                          //print for stack             
		if(ch =='!')
		{
			for(int i=top;i>=0;i--)
			{
				output1<<arrStack[i]<<" ";
			}
			output1<<"\n";
		}

		                                             //print for queue

		if(ch =='!')
		{
			for(int i=head;i!=tail;i=(i+1)%(n+1))
			{
				output2<<arrQueue[i]<<" ";
			}
			output2<<"\n";
		}

		                                              //print for dll
		if(ch =='!')
		{
			Node* x =new Node();
			x=heady;
			while(x!=NULL)
			{
				output3<<(x->data)<<" ";
				x=x->next;
			}
			output3<<"\n";
		
		}

		else
		{
			input>>d;
		                                               //add for stack
			if(ch=='+')
			{
				if(top==n-1)
				{
					output1<<"overflow\n";
				}
				else
				{
					arrStack[top+1]=d;
					top++;
					output1<<"pushed "<<d<<"\n";
				}
			
			}
		                                             //delete for stack
			if(ch=='-')
			{
				if(top==-1)
				{
					output1<<"underflow\n";
				}
				else
				{
					int x=arrStack[top];
					top--;
					output1<<"popped "<<x<<"\n";
				}

			
			}
		                                             //search for stack
			if(ch=='?')
			{
				int count=0;
				for(int i=0;i<=top;i++)
				{
					if(arrStack[i]==d)
					{
						output1<<"found "<<d<<"\n";
						break;
					}
					else
					{
						count++;
					}
				}

				if(count==top+1)
				{
					output1<<"not found "<<d<<"\n";
				}
			
			}
		                                                  //add for queue
			if(ch=='+')
			{
				if((tail+1)%(n+1) ==head)
				{
					output2<<"overflow\n";
				}
				else
				{
					arrQueue[tail]=d;
					tail=(tail+1)%(n+1);
					output2<<"enqueued "<<d<<"\n";
				}
			
			}
		                                                  //delete for queue
			if(ch=='-')
			{
				if(tail==head)
				{
					output2<<"underflow\n";
				}
				else
				{
					int x=arrQueue[head];
					head=(head+1)%(n+1);
					output2<<"dequeued "<<x<<"\n";
				}

			
			}
		                                                  //search for queue
			if(ch=='?')
			{
				int count=0;
				int total=0;
				for(int i=head;i!=tail;i=(i+1)%(n+1))
				{
					total++;
					if(arrQueue[i]==d)
					{
						output2<<"found "<<d<<"\n";
						break;
					}
					else
					{
						count++;
					}

				}
				if(count==total)
				{
					output2<<"not found "<<d<<"\n";
				}
			
			}
		                                                   //add for dll
			if(ch=='+')
			{
				Node* x = new Node();
				x->data=d;
			
				if(heady!=NULL)
				{
					x->next=heady;
					heady->prev=x;
					heady=x;
				}
				else
				{
					heady=x;

				}
			
				output3<<"inserted "<< d <<"\n";
			
			}
		                                                   //delete for dll
			if(ch=='-')
			{
				Node* x=findy(d);
				if(x==NULL)
				{
					output3<<"cannot delete "<<d<<"\n";
				}
				else if(x==heady && x->next==NULL)
				{
					heady=NULL;
					output3<<"deleted "<<d<<"\n";
				}
				else if(x==heady)
				{
					x->next->prev=NULL;
					heady=x->next;
					output3<<"deleted "<<d<<"\n";
				}
				else if(x->next==NULL)
				{
					x->prev->next=NULL;
					output3<<"deleted "<<d<<"\n";
				}
				else
				{
					x->next->prev=x->prev;
					x->prev->next=x->next;
					output3<<"deleted "<<d<<"\n";
				}

			}
		                                                  //search for dll
			if(ch=='?')
			{
				Node* x=findy(d);
				if(x==NULL)
				{
					output3<<"not found "<<d<<"\n";
				}
				else
				{
					output3<<"found "<<d<<"\n";
				}
			}

		}

	}

return 0;
}

Node* findy(int d)
	{
		Node* x=NULL;
		x=new Node();
		x=heady;
		while (x!=NULL)
		{
			if(x->data==d)
			{
				return x;
			}
			else
			{
				x=x->next;
			}
		}
		return x;

	}