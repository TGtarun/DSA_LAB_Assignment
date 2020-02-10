#include <iostream>       
#include <fstream>
using namespace std;
struct Node                     //structure contain pointer to parent left right and data 
{
	int data;
	Node* right;
	Node* left;
	Node* parent;

};
void inorder(Node* x);          //functions used in code
void preorder(Node* x);
void postorder(Node* x);
Node* maxi(Node* x);
Node* mini(Node* x);
Node* search(Node* x,int k);
Node* successor(Node* x);
Node* predecessor(Node* x);
Node* insert(int d);
void remove(Node* x);

Node* root=NULL;           //initialise root nood as null

ofstream bsy;              //outfile file stream

int main(int argc,char**argv)
{
	ifstream input;
	input.open(argv[1]);     //input file
	bsy.open("bst.txt");
	string str;
	while(input>>str)         //taking input from file as string
	{
		int d;
		if(str=="successor")  
		{
			input>>d;
			Node* x=search(root,d);    //serach weather d is present in bst or not
			if(x==NULL)
			{
				bsy<<d<<" does not exist"<<"\n";
			}
			else
			{
				Node* y=successor(x);
				if(y!=NULL)
				{
					bsy<<y->data<<"\n";
				}
				else
				{
					bsy<<"successor of "<<d<<"does not exist"<<"\n";
				}

			}

		}

		if(str=="predecessor")
		{
			input>>d;
			Node* x=search(root,d);      //serach weather d is present in bst or not
			if(x==NULL)
			{
				bsy<<d<<" does not exist"<<"\n";
			}
			else
			{
				Node* y=predecessor(x);          //call func
				if(y!=NULL)
				{
					bsy<<y->data<<"\n";
				}
				else
				{
					bsy<<"predecessor of "<<d<<"does not exist"<<"\n";
				}

			}

		}

		if(str=="inorder")
		{
			inorder(root);
			bsy<<"\n";
		}

		if(str=="preorder")
		{
			preorder(root);
			bsy<<"\n";
		}

		if(str=="postorder")
		{
			postorder(root);
			bsy<<"\n";
		}

		if(str=="insert")
		{
			input>>d;
			insert(d);
			bsy<<d<<" inserted"<<"\n";

		}

		if(str=="search")
		{
			input>>d;
			Node* x=search(root,d);          //serach weather d is present in bst or not
			if(x!=NULL)
			{
				bsy<<d<<" found"<<"\n";
			}
			else
			{
				bsy<<d<<" not found"<<"\n";
			}

		}

		if(str=="delete")
		{
			input>>d;
			Node* x=search(root,d);           //serach weather d is present in bst or not
			if(x==NULL)
			{
				bsy<<d<<" does not exist"<<"\n";
			}
			else
			{
				remove(x);
				bsy<<d<<" deleted"<<"\n";
			}
	    }

		if(str=="maximum")
		{
			Node* x=maxi(root);           //call func
			if(x!=NULL)
			{
				bsy<<(x->data)<<"\n";
			}

			else
			{
				bsy<<"\n";
			}

		}

		if(str=="minimum")
		{

			Node* x=mini(root);
			if(x!=NULL)
			{
				bsy<<x->data<<"\n";
			}

			else
			{
				bsy<<"\n";
			}

		}
	}

	return 0;
}

void inorder(Node* x)
{
	if(x!=NULL)
	{
		inorder(x->left);
		bsy<<(x->data)<<" ";
		inorder(x->right);
	}
}

void preorder(Node* x)
{
	if(x!=NULL)
	{
		bsy<<x->data<<" ";
		preorder(x->left);
		preorder(x->right);
	}
}

void postorder(Node* x)
{
	if(x!=NULL)
	{
		postorder(x->left);
		postorder(x->right);
		bsy<<x->data<<" ";
	}
}

Node* maxi(Node* x)     //maximum fun
{
	if(x==NULL)
	{
		return x;
	}
	while(x->right!=NULL)
	{
		x=x->right;
	}

	return x;
}

Node* mini(Node* x)           //minimum function
{
	if(x==NULL)
	{
		return x;
	}
	while(x->left!=NULL)
	{
		x=x->left;
	}

	return x;
}

Node* search(Node* x , int k)         //search func
{
	if(x!=NULL && x->data!=k)
	{
		if(x->data >k )
		{
			return search(x->left,k);
		}

		else
		{
			return search(x->right,k);
		}
	}

	return x;
}

Node* successor(Node* x)      //successor func
{
	if(x->right!=NULL)
	{
		return mini(x->right);
	}

	Node* y =x->parent;
	while (y!=NULL && y->right==x)
	{
		x=y;
		y=y->parent;
	}

	return y;
}

Node* predecessor(Node* x)         //predecessor func
{
	if(x->left!=NULL)
	{
		return maxi(x->left);
	}

	Node* y =x->parent;
	while (y!=NULL && y->left==x)
	{
		x=y;
		y=y->parent;
	}

	return y;
}

Node* insert(int d)                 //insert func
{
	Node* x =new Node();
			x->data=d;
			Node* y=root;
			Node* p =NULL;

			if(y==NULL)
			{
				root=x;
			}
			else
			{
				while(y!=NULL)
				{
					p=y;
					if(x->data <y->data)
					{
						y=y->left;
					}
					else
					{
						y=y->right;
					}
				}

				x->parent=p;
				if(x->data<p->data)
				{
					p->left=x;
				}
				else
				{
					p->right=x;
				}

			}

}


void transplant(Node* z,Node* y)               //transplant function
{
	if(z==root)
	{
		root=y;
	}

	else
	{
		if(z->parent->left==z)
		{
			z->parent->left=y;
		}

		else
		{
			z->parent->right=y;
		}
	}

	if(y!=NULL)
	{
		y->parent=z->parent;
	}
}

void remove(Node* x)              //remove func
{
	if(x->left==NULL)
	{
		transplant(x,x->right);
	}
	else if(x->right==NULL)
	{
		transplant(x,x->left);
	}

	else 
	{
		Node* y=mini(x->right);
		if(y->parent!=x)
		{
			transplant(y,y->right);
			y->right=x->right;
			y->right->parent=y;
		}

		transplant(x,y);
		y->left=x->left;
		y->left->parent=y;
		
	}
}