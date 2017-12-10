#include<iostream>
#include<queue>
#include<stack>
#include<math.h>
#include<cstring>

using namespace std;

struct node{
	int info;
	struct node *left;
	struct node *right;
}*root,*newptr,*ptr,*save;

node *create_new_node(int);
void insert(node*,node*);

void preorder_iter();
void inorder_iter();
void postorder_iter();

void preorder_recur(node*);
void inorder_recur(node*);
void postorder_recur(node*);

void printspace(int);
int height_tree(node *);
void display_vertical();

void display_horizontal(node*,int);

int main(){
	root=NULL;
	char ch='y';
	int info;
	string s;
	cout<<"\t\t\tTree \n";
	while (ch=='y' || ch=='Y'){
		if (root==NULL){
			cout<<"\nEnter 1 or 2-digit info of root node: ";
			cin>>info;
			newptr=create_new_node(info);
			root=newptr;
		}
		else{
			cout<<"\nEnter 1 or 2-digit info: ";
			cin>>info;
			newptr=create_new_node(info);
			insert(newptr,root);
		}
		cout<<"\nDo u want to continue(y for yes/n for no): ";
		cin>>ch;
	}
	display_vertical();
  cout<<"Iterative Traversal: "<<endl;
	preorder_iter();
	inorder_iter();
	postorder_iter();

  cout<<"Recursive Traversal: \n";
  cout<<"Preorder Tracersal of tree: \n";
  preorder_recur(root);
  cout<<"\nInorder Tracersal of tree: \n";
  inorder_recur(root);
  cout<<"\nPostorder Tracersal of tree: \n";
  postorder_recur(root);
  cout<<"\n\nHorizontal Display of tree: \n";
	display_horizontal(root,-5);
}
//CREATING NODE
node* create_new_node(int inf){
	ptr=new (struct node);
	ptr->info=inf;
	ptr->left=NULL;
	ptr->right=NULL;
}

//INSERT NODE IN TREE
void insert(node *np,node *ptr1){
	string s;
	cout<<"Enter right or left: ";
	cin>>s;
	if (s=="right"){
		if (ptr1->right==NULL){
			ptr1->right=np;
		}
		else {
			ptr1=ptr1->right;
			insert(np,ptr1);
		}
	}
	else{
		if (ptr1->left==NULL){
			ptr1->left=np;
		}
		else {
			ptr1=ptr1->left;
			insert(np,ptr1 );
		}
	}
}

//PREORDER TRAVERSAL OF TREE
void preorder_iter(){
	cout<<"\nPreorder traversal of tree is: ";
	stack<node *> st;
	st.push(NULL);
	ptr=root;
	while (ptr!=NULL){
		cout<<ptr->info<<"->";
		if (ptr->right!=NULL){
			st.push(ptr->right);
		}
		if (ptr->left!=NULL){
			ptr=ptr->left;
		}
		else{
			ptr=st.top();
			st.pop();
		}
	}
	cout<<"END\n";
}

//INORDER TRAVERSAL OF TREE
void inorder_iter(){
	cout<<"\nInorder traversal of tree is: ";
	stack<node *> st;
	st.push(NULL);
	ptr=root;
	repeat:
		while (ptr!=NULL){
			st.push(ptr);
			ptr=ptr->left;
		}
		ptr=st.top();
		st.pop();
		while (ptr!=NULL){
			cout<<ptr->info<<"->";
			if (ptr->right!=NULL){
				ptr=ptr->right;
				goto repeat;
			}
			else{
				ptr=st.top();
				st.pop();
			}
		}
	cout<<"END\n";
}

//POSTORDER TRAVERSAL OF TREE
//Valid onlu for 32-bit version
void postorder_iter(){
	cout<<"\nPostorder traversal of tree is: ";
	stack<int> st;
	st.push(0);
	ptr=root;
	step2:
		while (ptr!=NULL){
			st.push(int(ptr));
			if (ptr->right!=NULL){
				st.push(-1*(int(ptr->right)));
			}
			ptr=ptr->left;
		}
		ptr=NULL;
		int x=st.top();
		ptr=(node*)(x);
		st.pop();
		while (x>0){
			x=st.top();
			cout<<ptr->info<<"->";
			ptr=(node*)(x);
			st.pop();

		}
		if (x<0){
			x=-1*x;
			ptr=(node*)(x);
			goto step2;
		}
	cout<<"END\n";
}
//PREORDER
void preorder_recur(node *np){
  if (np==NULL){
    return;
  }
  cout<<np->info<<" ";
  preorder_recur(np->left);
  preorder_recur(np->right);
}
//INORDER
void inorder_recur(node *np){
  if (np==NULL){
    return;
  }
  inorder_recur(np->left);
  cout<<np->info<<" ";
  inorder_recur(np->right);
}
//POSTORDER
void postorder_recur(node *np){
  if (np==NULL){
    return;
  }
  postorder_recur(np->left);
  postorder_recur(np->right);
  cout<<np->info<<" ";
}
//Display a binary tree in VERTICAL tree format
void printspace(int n){//for printing desired number of spaces
	for (int i=0;i<n;i++){
		cout<<" ";
	}
}
int height_tree(node * p){//for calculating depth of tree
	if (p==NULL){
		return 0;
	}
	else{
		int ldepth=height_tree(p->left);
		int rdepth=height_tree(p->right);
		if (ldepth>rdepth){
			return(ldepth+1);
		}
		else{
			return(rdepth+1);
		}
	}
}
void display_vertical(){//printing tree
	if (root==NULL){
		cout<<"NULL\n";
		return;
	}
	queue<node *> q;
	q.push(root);
	int ar[10000];
	int i=0;
	memset(ar,-1,sizeof ar);
	int count=0;
	int height=height_tree(root);
	//converting tree into an array
	while (!q.empty()){
		ptr=q.front();
		q.pop();
		count++;

		if (ptr!=NULL){
			ar[i]=ptr->info;
			i++;
			q.push(ptr->left);
			q.push(ptr->right);
		}
		else{
			i++;
			q.push(NULL);
			q.push(NULL);
		}
		if (log2(count+1)==height){
			break;
		}
	}
	//display tree
	cout<<"\nVertical display of tree: \n";
	int x=height;
	for (int i=1;i<=pow(2,height-1);i*=2){
		int z=pow(2,x-1)-1;
		printspace(z*2);
		for (int j=i-1;j<(i*2)-1;j++){
			if (ar[j]!=-1){
				if (ar[j]/10==0){
					cout<<"0";
				}
				cout<<ar[j];
				printspace((pow(2,x)-1)*2);
			}
			else{
				cout<<"  ";
				printspace((pow(2,x)-1)*2);
			}
		}
		cout<<endl;
		printspace((z*2)-1);
		if (i!=pow(2,height-1)){
			for (int j=i-1;j<(i*2)-1;j++){
				if (ar[j]!=-1){
					if (ar[2*(j+1)-1]!=-1){
						cout<<"/";
					}
					else{
						cout<<" ";
					}
					cout<<"  ";
					if (ar[2*(j+1)]!=-1){
						cout<<"\\";
					}
					else{
						cout<<" ";
					}
					//cout<<"/  \\";
					printspace(((pow(2,x)-1)*2)-2);
				}
				else{
					printspace(4);
					printspace(((pow(2,x)-1)*2)-2);
				}
			}
		}
		cout<<endl;
		x--;
	}
}
//Display a binary tree in HORIZONTAL tree format
void display_horizontal(node *np,int space){
	if (np==NULL){
		return;
	}
	space+=5;
	display_horizontal(np->right,space);
	printspace(space);
	cout<<np->info<<endl;
	display_horizontal(np->left,space);
}
