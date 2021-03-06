#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adj[20][20];
int sp[20][20];
int n;
int nodes = 0;
int a[33];

struct node{
	int val;
	struct node *lchild;
	struct node *rchild;
	struct node *parent;
	int n1;
	int n2;
};
struct node *root=NULL;
void swap1(struct node *a,struct node *b){
	int t;
	t = a->val;
	a->val = b->val;
	b->val = t;
	t = a->n1;
	a->n1 = b->n1;
	b->n1 = t;
	t = a->n2;
	a->n2 = b->n2;
	b->n2 = t;	
}
void check(struct node *n) {
	int t;
	if(n==root) return;
	if(n->parent->val > n->val) {
		swap1(n,n->parent);
		check(n->parent);
	}
}

int getbinary() {
	memset(a,0,sizeof(a));
	if(nodes == 0) return 0;
	int n = nodes,i = 0;
	while(n!=0){
		a[i]=n%2;
		n=n/2;
		i++;
	}
	return i;
}

void createnode(int value,int node1,int node2) {
	struct node *n = (struct node *)malloc(sizeof(struct node));
	n->val = value;
	n->lchild = NULL;
	n->rchild = NULL;
	n->parent = NULL;
	n->n1 = node1;
	n->n2 = node2;
	nodes++;
	if(nodes == 1) {
		root = n;
	}
	else {
		struct node *t = root;
		struct node *parent = NULL; 
		int l = getbinary();
		int i;
		for(i=l-2;i>=0;i--){
			parent = t;
			if(a[i]==0) 
				t =t->lchild;
			else
				t= t->rchild;
			if(t==NULL){
				if(a[i]==0) parent->lchild = n;
				else parent->rchild = n;
				n->parent = parent;
				check(n);
			}  
		}
	}
}


void inorder(struct node *n){
	if(n == NULL)
		return;
	inorder(n->lchild);
	printf("%d \t",n->val);
	inorder(n->rchild);
}
void maxify(struct node *n)
{
	if(n->lchild==NULL && n->rchild== NULL) return;
	struct node *small = n;
	int temp;
	if(n->lchild->val < n->val) small = n->lchild;
	if((n->rchild!=NULL) && (small->val > n->rchild->val)) small = n->rchild;
	if(small!=n) {
		swap1(small,n);
		maxify(small);
	}
}

struct node *del() {
	if(root==NULL){
		printf("Empty heap\n");
		return root;
	}
	int l = getbinary();
	struct node *t= root;
	struct node *parent = NULL;
	int i,temp;
	if(l==1){
		root = NULL;
		nodes = 0;
		return t;
	}
	for(i=l-2;i>=0;i--){
		parent = t;
		if(a[i]==0) t =t->lchild;
		else t= t->rchild;
	}
	if(a[0]==0) {
		swap1(parent->lchild,root);
		t = parent->lchild;
		parent->lchild = NULL;
		maxify(root);
	}
	else {
		swap1(parent->rchild,root);
		t = parent->rchild;
		parent->rchild = NULL;
		maxify(root);
	}
	nodes--;
	return t;
}
void display(int adj[20][20])
{
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d\t",adj[i][j]);
		}
		printf("\n");
	}
}

void prim(int v)
{	int i,j,k,n1,n2,newnode,edge,f1,f2;
	if(v>n) {
		printf("Invalid root\n");
		return;
	}
	
	printf("root Vertex = %d\n",v);
	for(i=0;i<n;i++) for(j = 0;j<n;j++) sp[i][j] = -1;
	struct node *t;
	//sp[v][v] = 0;
	for(i = 0;i<n;i++) createnode(adj[v][i],v,i);
	t = del();
	edge = t->val;
	n1 = t->n1;
	n2 = t->n2;
	free(t);
	printf("edge = %d n1 = %d n2 = %d\n",edge,n1,n2);
	if(n1==v) newnode = n2;
	else n2 = newnode;
	sp[v][newnode] =adj[v][newnode];
	sp[newnode][v]= adj[v][newnode];
	
	for(i = 2;i<n;i++){
		for(j = 0;j<n;j++) createnode(adj[newnode][j],newnode,j);
		f1 = f2=0;
		while(f1==0 && f2==0){
			t = del();
			if(t==NULL) return;
			edge = t->val;
			n1 = t->n1;
			n2 = t->n2;
			free(t);
			for(k = 0;k<n;k++){
				f1 = 1;
				if(sp[n1][k]!=-1){
					f1 = 0;
					break;
				}
			}
			for(k = 0;k<n;k++){
				f2 = 1;
				if(sp[n2][k]!=-1){
					f2 = 0;
					break;
				} 
			}
		}		
		if(f1 == 1) {
			newnode = n1;
			sp[newnode][n2] = edge;
			sp[n2][newnode] = edge;
		}
		else if(f2 == 1){
			newnode = n2;
			sp[newnode][n1] = edge;
			sp[n1][newnode] = edge;
		}
		printf("edge = %d n1 = %d n2 = %d\n",edge,n1,n2);
	}
	display(sp);
}
void create_graph()
{	int i,j, max_edges, origin, dest, wt;
//	printf("Enter no. of verticies: ");
//	scanf("%d", &n);
//	max_edges = n*(n-1)/2;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			adj[i][j] = 999999;
			sp[i][j] = -1;
		}
	}
/*	for (i = 0; i < max_edges; i++) {
		printf("Enter edges: origin: destination weight(-1 -1 to QUIT)\n");
		scanf("%d %d", &origin, &dest);
		if (origin == -1 && dest == -1)
			break;
	//	printf("Enter the weight: ");
		scanf("%d", &wt);
		if (origin >= n || origin < 0 || dest >= n || dest < 0) {
			printf("Invalid edge\n");
			i--;
		}
		else {
			adj[origin][dest] = wt;
			adj[dest][origin] = wt;
		}
	}*/
	n = 4;
	adj[0][0] = adj[1][1]=adj[2][2] = adj[3][3] = 9999;
	 adj[2][3] =adj[3][2]= 9999;	
	adj[0][1] = 7;	adj[1][0] = 7;
	adj[0][2] = 3;	adj[2][0] = 3;
	adj[0][3] = 4;	adj[3][0] = 4;
	adj[1][2] = 5;	adj[2][1] = 5;
	adj[1][3] = 2;	adj[3][1] = 2;
}

int main()
{
	create_graph();
	prim(0);
}
