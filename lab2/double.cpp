#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <time.h>
using namespace std;

struct node{
double x;
double y;
struct node* prev;
struct node* next;
};

int count(struct node *tail){
	int c =0;
	if(tail==NULL)return c;
	struct node* ptr = tail->next;
	while(ptr!=tail){
		c++;
		ptr = ptr->next;
	}
	c++;
	return c;
}
double eqn(double x1,double y1,double x2,double y2,double x,double y)
{
	if(((x==x1)&&(y==y1))||((x==x2)&&(y==y2))) return 0.000;
	double m = ((double)(y2-y1))/((double)(x2-x1));
	m = ((double)(y-y1)-(m*((double)(x-x1))));
	return m;
}
struct node* insert(struct node *tail,double a,double b)
{	struct node *temp =(struct node *)malloc(sizeof(struct node));
	temp->x = a;
	temp->y = b;
	temp->next = NULL;
	temp->prev = NULL;
	if(tail == NULL){
		temp->next = temp;
		temp->prev = temp;
		tail = temp;
	}
	else {
		temp->prev= tail;
		temp->next = tail->next;
		tail->next->prev = temp;
		tail->next = temp;
		tail = temp;
	}
	return tail;
}
void display(struct node *tail)
{	if(tail==NULL)return;
	struct node* ptr = tail->next;
	while(ptr!=tail){
		printf("x = %lf\ty = %lf\n",ptr->x,ptr->y);
		ptr = ptr->next;
	}
	printf("x = %lf\ty = %lf\n",tail->x,tail->y);
}
bool test_upper(struct node *tail,double a,double b, double c, double d, double &g, double &h)
{
	cout << "HERE UPPER" << endl;
	cout << a << " " << b << " " << c << " " << d << endl;
	struct node* ptr = tail->next;
	while(ptr!=tail){
		printf("x = %d\ty = %d\n",ptr->x,ptr->y);
		if(eqn(a,b,c,d,ptr->x,ptr->y) > 0.00){	
				g = ptr->x;
				h = ptr->y;
				return false;
		}
		ptr = ptr->next;
	}
	if(eqn(a,b,c,d,tail->x,tail->y) > 0.00){	
				g = tail->x;
				h = tail->y;
				return false;
	}
	return true;
}
bool test_lower(struct node *tail,int a,double b, double c, double d, double &g, double &h)
{
	cout << "HERE LOWER" << endl;
	cout << a << " " << b << " " << c << " " << d << endl;
	struct node* ptr = tail->next;
	while(ptr!=tail){
		printf("x = %d\ty = %d\n",ptr->x,ptr->y);
		if(eqn(a,b,c,d,ptr->x,ptr->y) < 0.00){	
				g = ptr->x;
				h = ptr->y;
				return false;
		}
		ptr = ptr->next;
	}
	if(eqn(a,b,c,d,tail->x,tail->y) < 0.00){	
				g = tail->x;
				h = tail->y;
				return false;
	}
	return true;
}

struct node* merge(struct node *convex_left,struct node *convex_right,struct node *tail){
	struct node *res = NULL,*ptr;
	if(count(convex_left)==0){
		res = convex_right;
		return res;
	}
	else if(count(convex_right)==0){
		res = convex_left;
		return res;
	}
	double xhighl,yhighl,xhighr,yhighr;
	double xlowl,ylowl,xlowr,ylowr;
	
	xhighl = convex_left->x;
	yhighl = convex_left->y;
	xlowl = convex_left->x;
	ylowl = convex_left->y;
	ptr = convex_left->next;
	while(ptr!=convex_left){
		if(ptr->y > yhighl){	
		yhighl = ptr->y;
		xhighl = ptr->x;
		}
		if(ptr->y < ylowl){
			ylowl = ptr->y;
			xlowl = ptr->x;
		}
		ptr = ptr->next;
	}
	//cout << xhighl << " " << yhighl<<"      " << xlowl <<" "<<ylowl << endl;
	
	xhighr = convex_right->x;
	yhighr = convex_right->y;
	xlowr = convex_right->x;
	ylowr = convex_right->y;
//	cout << xhighr << " " << yhighr<<"      " << xlowr <<" "<<ylowr << endl;
	
	ptr = convex_right->next;
	while(ptr!=convex_right){
//		cout<<"find high and low in right_convex\n";
		if(ptr->y > yhighr){
		yhighr = ptr->y;
		xhighr = ptr->x;
		}
		if(ptr->y < ylowr){
			ylowr = ptr->y;
			xlowr = ptr->x;
		}
		ptr = ptr->next;
	}
//	cout << xhighr << " " << yhighr<<"      " << xlowr <<" "<<ylowr << endl;
	double g,h;
//	cout<<"Testing upper\n";
	while(test_upper(convex_right,xhighl,yhighl,xhighr,yhighr,g,h) != true){
//		cout<<"Testing upper\n";
		xhighr = g;
		yhighr = h;
	}
//	cout << xhighr << " " << yhighr<<"      " << xlowr <<" "<<ylowr << endl;

	while(test_upper(convex_left,xhighr,yhighr,xhighl,yhighl,g,h) != true){
		
		xhighl = g;
		yhighl = h;
	}

//	cout << "Test_upper passed" << endl;
//	cout << xhighr << " " << yhighr<<"      " << xhighl <<" "<<yhighl << endl;
	while(test_lower(convex_right,xlowl,ylowl,xlowr,ylowr,g,h) != true){
		xlowr = g;
		ylowr = h;
	}

	while(test_lower(convex_left,xlowr,ylowr,xlowl,ylowl,g,h) != true){
		xlowl = g;
		ylowl = h;	
	}
//	cout << "Test_lower passed" << endl;
//	cout << xlowr << " " << ylowr<<"     " << xlowl <<" " <<ylowl << endl;
//	display(convex_left);	
	ptr = convex_left->next;
	while(ptr->x!=xhighl||ptr->y!=yhighl){
		ptr = ptr->next;
	}
//	cout<<ptr->x<<ptr->y;
	while(ptr->x!= xlowl || ptr->y != ylowl){
		res = insert(res,ptr->x,ptr->y);
		ptr = ptr->next;
	}
	res = insert(res,ptr->x,ptr->y);
	//display(res);
//	display(convex_right);
	ptr = convex_right->next;
	while(ptr->x!=xlowr||ptr->y!=ylowr){
//		cout<<"Testing for lower";
		ptr = ptr->next;
	}
//	cout<<ptr->x<<ptr->y;
	while(ptr->x!= xhighr || ptr->y != yhighr){
//		cout<<"Testing for higher\n";
		res = insert(res,ptr->x,ptr->y);
		ptr = ptr->next;
	}
	res = insert(res,ptr->x,ptr->y);
	return res;
}

struct node* convexhull(struct node *tail,int n,double xmin,double xmax){
	struct node* res = NULL,*p = NULL, *ptr = NULL;
	if(n==0){
		return res;
	}
	else if(n==1){
		res = insert(res,tail->x,tail->y);
		return res;
	}
	else if(n==2){
		res = insert(res,tail->x,tail->y);
		res = insert(res,tail->prev->x,tail->prev->y);
		return res;
	}
	else {
		printf("Here!!!\n");
		int flag = 0;
		double k = tail->next->x;
		p = tail->next->next;
		ptr = tail->next;
		while(p!=ptr){
			if(p->x!=k){
				printf("Here flag = 1!!!\n");
				flag = 1;
				break;
			}
			p = p->next;
		}
		if(flag == 0){			
		//	res = insert(res,tail->next->x,tail->next->y);
			res = insert(res,tail->x,tail->y);
			res = insert(res,tail->next->x,tail->next->y);
			printf("Here flag = 0!!!\n");
			return res;
		}
	else {
			printf("Here flag = 1!!!!\n");
			double xmid;
			xmid = (xmin+xmax)/2;
			if(xmid == xmax) xmid = xmid-1;
//			cout<<"XMID = "<<xmid<<endl;
			struct node *left = NULL, *right = NULL;
			int c1=0;
			int c2=0;
			cout<<"tail to be divided\n";
			display(tail);
			ptr = tail->next;
			while(ptr->x <= xmid && ptr!=tail){
					left=insert(left,ptr->x,ptr->y);
					cout<<"Inserting in left\n";
					ptr = ptr->next;
					c1++;
			}
			if(ptr==tail && ptr->x<=xmid) {
				left=insert(left,ptr->x,ptr->y);
				c1++;
				cout<<"Inserting in left in if\n!";
			}
			//display(left);
			else {
				while(ptr!=tail){
					cout<<"Inserting in right\n";
					right = insert(right,ptr->x,ptr->y);
					ptr = ptr->next;
					c2++;
				}
				cout<<"Inserting in right!\n";
				right = insert(right,tail->x,tail->y);
				c2++;				
			}
			
			cout<<"LEFT IS\n";
			display(left);
			cout<<"RIGHT IS\n";
			display(right);
			struct node *left_hull = NULL, *right_hull = NULL;
			left_hull = convexhull(left,c1,xmin,xmid);
			right_hull = convexhull(right,c2,xmid+1,xmax);
			cout<<"LEFT HULL IS\n";
			display(left_hull);
			cout<<"RIGHT HULL IS\n";
			display(right_hull);						
			res = merge(left_hull,right_hull,tail);
			return res;
		}
	}
}


int main()
{	struct node *tail = NULL,*res = NULL;
	int n, i;
	pair<double,double> p[100];
//	printf("Enter the no of elements in the array: ");
	scanf("%d", &n);
	double x[n];
	double y[n];
/*	srand((unsigned int)time(NULL));
	double a = 5.0;*/
	for (i = 0; i < n; i++) {
		scanf("%lf%lf",&x[i],&y[i]);
		/*x[i] = (((double)rand()/(double)(RAND_MAX))*a);
		y[i] = (((double)rand()/(double)(RAND_MAX))*a);*/
		p[i] = make_pair(x[i],y[i]);
	}
	sort(p,p+n);
	for (i = 0; i < n; i++) {
		x[i] = p[i].first;
		y[i]  = p[i].second;
	}
	double xmin = x[0];
	double xmax = x[n-1];
	for(i=0;i<n;i++) tail = insert(tail,x[i],y[i]);
	display(tail);
	res = convexhull(tail,n,xmin,xmax);
	cout<<"HULL IS:\n";
	display(res);
	//printf("%lf\t",equ(0,0,1,1,4,3));	
}
