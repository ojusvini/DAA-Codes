#include<stdio.h>
int min(int a,int b){
	return a<b?a:b;
}
int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	int i,j;
	int c[n+1][k+1];
	for(i=0;i<=n;i++) {
		for(j=0;j<=min(i,k);j++) {
			if(j==0 || j==i) {
				c[i][j]=1;
			} else {
				c[i][j]=c[i-1][j-1]+c[i-1][j];
			}
		}
	}
	printf("%d\n",c[n][k]);
	return 0;
}
