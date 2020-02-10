#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;
int partition(int p,int r);
void merge_sort(int p , int r);
void quick_sort(int p,int r);
void merge(int p, int q,int r);
vector<int> arr;
vector<int> arr1;
ofstream op1;
ofstream op2;

int main(int argc ,char*argv[])
{
	ifstream fp;
	fp.open(argv[1]);
	op1.open("mergesort.txt");  //output1 for merge  // output2 for quick
	op2.open("quicksort.txt");

	int d;
	while(fp>>d)
	{
		arr.push_back(d);
		arr1.push_back(d);
	}

	merge_sort(0,arr.size()-1);
	quick_sort(0,arr1.size()-1);
	for(int i=0;i<arr.size();i++)
	{
		op1<<arr[i]<<"\n";
		op2<<arr[i]<<"\n";
	}

	return 0;
}

void merge_sort(int p , int r)
{
	if(p<r)
	{
		int q=floor((p+r)/2);
		merge_sort(p,q);
		merge_sort(q+1,r);
		merge(p,q,r);
	}
}

void merge(int p, int q,int r)
{
	int left[q-p+2];
	int right[r-q+1];
	for(int i=0;i<=q-p;i++)
	{
		left[i]=arr1[p+i];
	}

	for(int i=0;i<=r-q-1;i++)
	{
		right[i]=arr1[q+i+1];
	}

	left[q-p+1]=std::numeric_limits<int>::max();
	right[r-q]=std::numeric_limits<int>::max();

	int a=0,b=0;
	for(int i=p;i<=r;i++)
	{
		if(left[a]<right[b])
		{
			arr1[i]=left[a];
			a++;
		}

		else
		{
			arr1[i]=right[b];
			b++;
		}
	}
}

void quick_sort(int p,int r)
{
	if(p<r)
	{
		int q=partition(p,r);
		quick_sort(p,q-1);
		quick_sort(q+1,r);
	}
}

int partition(int p,int r)
{
	int a=arr[r];
	int i=p;
	for(int j=p;j<r;j++)
	{
		if(arr[j]<=a)
		{
			int temp=arr[j];
			arr[j]=arr[i];
			arr[i]=temp;
			i++;

		}
	}

	int tempo=arr[r];
	arr[r]=arr[i];
	arr[i]=tempo;
	return i;
}