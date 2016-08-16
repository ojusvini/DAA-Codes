#include <stdio.h>
#include <math.h>
#include <limits.h>

double closepair(int x[], int y[], int n, int l, int u);
double distance(int x[], int y[], int l, int u);
double merge(int x[], int y[], int n, int l, int u, int m, double ldist, double rdist);

void quick(int a[], int b[], int low, int up) {

	int pivloc;
	if (low >= up)
		return;
	pivloc = partition_cormen(a, b, low, up);
	quick(a, b, low, pivloc-1);
	quick(a, b, pivloc+1, up);
}

int partition_cormen(int a[], int b[], int low, int up)
{	
	int i, j, pivot, temp, t, p;
	pivot = a[up];
	p = b[up];
	i = low-1;
	
	for (j = low; j <= (up-1); j++) {
		if (a[j] <= pivot) {
			i = i+1;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			t = b[i];
			b[i] = b[j];
			b[j] = t;
		}
	}
	a[up] = a[i+1];
	a[i+1] = pivot;
	b[up] = b[i+1];
	b[i+1] = p;
	
	return (i+1);
}

int main()
{
	int n, i;
	double dist;
	scanf("%d", &n);
	int x[n];
	int y[n];

	for (i = 0; i < n; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}

	quick(x, y, 0, n-1);

	dist = closepair(x, y, n, 0, n-1);
	printf("%lf\n", dist);

	return 0;
}

double closepair(int x[], int y[], int n, int l, int u)
{
	double ldist, rdist, dist, mid;
	int m, i;

	if (l == u)
		return INT_MAX;
	else if (l == u-1) {
		return distance(x, y, l, u);
	}
	else {
		mid = (x[l]+x[u])/2.0;
		for (i = l; i <= u; i++) {
			if (x[i] == mid) {
				m = i;
				break;
			}
			if (x[i] > mid) {
				m = i-1;
				break;
			}
			
		}
		ldist = closepair(x, y, n, l, m);
		rdist = closepair(x, y, n, m+1, u);
		dist = merge(x, y, n, l, u, m, ldist, rdist);
	}
	return dist;
}

double distance(int x[], int y[], int l, int u)
{
	double d;
	d = sqrt(((x[u]-x[l])*(x[u]-x[l])) + ((y[u]-y[l])*(y[u]-y[l])));

	return d;
}

double merge(int x[], int y[], int n, int l, int u, int m, double ldist, double rdist)
{
	int i, j, start, end;
	double dist, mid, d;
	//mid = (x[l]+x[u])/2.0;

	if (ldist <= rdist)
		dist = ldist;
	else
		dist = rdist;
		
	quick(y, x, l, m);
	quick(y, x, m+1, u);
	
	start = m+1;
	end = start+5;	

	for (i = l; i <= m; i++) {
		for (j = start; j<= end&&j <= u; j++) {
			d = distance(x, y, i, j);
			if (d < dist)
				dist = d;
		}
		while(abs(y[start]-y[i+1]) > d)
			start++;
		end=start+5;
	}
	return dist;
}

