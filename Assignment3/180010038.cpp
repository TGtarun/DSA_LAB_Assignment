#include<iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;
vector<int> arr;
vector<int> arr1;
void heapSort();
int parent(int i);
int leftChild(int i);
int rightChild(int i);
void maxi();
void extractMax();
void insert(int key);
void increaseKey(int i,int key);
void maxHeapify(int i);
void maxHeapify1(int i); 
ofstream op;


int main(int argc,char*argv[])
{
	ifstream fp;
	fp.open(argv[1]);
	op.open("heap.txt");
	string str;
	while(fp>>str)
	{
		if(str=="insert")
		{
			int d;
			fp>>d;
			insert(d);
			op<<d<<" inserted\n";

		}

		if(str=="sort")
		{
			heapSort();

		}

		if(str=="extract-max")
		{
			extractMax();
		}

		if(str=="maximum")
		{
			maxi();

		}

		if(str=="increase-key")
		{
			int n1,n2;
			fp>>n1>>n2;
			if(n1>arr.size()-1)
			{
				op<<"\n";
			}

			else
			{
				if(arr[n1]>n2)                                     //check whether given index exists or not
				{
					op<<n2<<" is less than the current key at "<<n1<<endl;
				}

				else
				{
					increaseKey(n1,n2);
					op<<"Key at "<<n1<<" changed to "<<n2<<"\n";

				}
			}


		}
	}
	/*for(int i=0; i<arr.size(); i++) {

		op << arr[i] << " ";
	}
	op << endl;*/

	return 0;

}

int parent(int i)
{
	return floor((i-1)/2);
}

int leftChild(int i)
{
	return 2*i+1 ;
}

int rightChild(int i)
{
	return 2*i+2 ;
}

void maxHeapify(int i)
{
	int largest=i;
	if(leftChild(i) < arr.size() && arr[leftChild(i)]>arr[i])
	{
		largest=leftChild(i);
	}

	if(rightChild(i) < arr.size() && arr[rightChild(i)]>arr[largest])
	{
		largest=rightChild(i);
	}

	if(largest!=i)
	{
		int temp=arr[largest];
		arr[largest]=arr[i];
		arr[i]=temp;
		maxHeapify(largest);
	}
}

void increaseKey(int i,int n2)
{
	if(i>arr.size()-1)
	{
		op<<"\n";
		return;
	}

		arr[i]=n2;
		while(i>0 && arr[i]>arr[parent(i)])
		{
			int temp=arr[i];
			arr[i]=arr[parent(i)];
			arr[parent(i)]=temp;
			i=parent(i);
	}
}

void insert(int key)
{
	arr.push_back(-1);
	increaseKey(arr.size()-1,key);
}


void maxi()
{
	if(arr.size()==0)
	{
		op<<"\n";
	}
	else
	{
		op<<arr[0]<<endl;
	}   
}

void extractMax()
{
	int maxu;
	if(arr.size()==0)
	{
		op<<"\n";
		return;
	}
	else
	{
		maxu=arr[0];
		arr[0]=arr[arr.size()-1];
		arr.pop_back();
		maxHeapify(0);
	}

	op<<maxu<<endl;
}


void heapSort()
{
	vector<int> arr2;
	for(int i=0;i<arr.size();i++)
		{
			arr1.push_back(arr[i]);
		}
	/*for (int i=0; i< arr1.size(); i++) {
		op << arr1[i] <<" ";
	}
	op << endl;*/

	while(arr1.size()>0)
	{
		//op << arr1[0] << " "; 
		swap(arr1[0],arr1[arr1.size()-1]);
		arr2.push_back(arr1[arr1.size()-1]);
		arr1.pop_back();
		maxHeapify1(0);
		/*for (int i=0; i<arr1.size(); i++) {
			op << arr1[i] << " ";
		}
		op << endl;*/
	}

	for(int j=arr2.size()-1;j>=0;j--)
	{
		op<<arr2[j]<<" ";
	}

	op<<"\n";

}

void maxHeapify1(int i)
{
	int largest=i;
	if(leftChild(i) < arr1.size() && arr1[leftChild(i)]>arr1[i])
	{
		largest=leftChild(i);
	}
	if(rightChild(i) < arr1.size() && arr1[rightChild(i)]>arr1[largest])
	{
		largest=rightChild(i);
	}
	if(largest!=i)
	{
		swap(arr1[i], arr1[largest]); 
		/*int temp=arr1[largest];
		arr1[largest]=arr1[i];
		arr1[i]=temp;*/
		maxHeapify1(largest);
	}
}