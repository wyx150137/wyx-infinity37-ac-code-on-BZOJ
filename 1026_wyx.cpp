
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

int F[15][15];

int solve(int A)
{
	int a[15],top = 0;
	while(A)
	{
		a[++top] = A % 10;
		A /= 10;
	}
	a[top+1] = 0 ;
	int ans = 0;
	for(int i=1;i<top;++i)
		for(int j=1;j<10;++j)
			ans += F[i][j];
	for(int i=1;i<a[top];++i)
		ans += F[top][i];
	for(int i=top-1;i;--i)
	{
		for(int j=0;j<a[i];++j)
			if(abs(j-a[i+1])>1)
				ans += F[i][j];
		if(abs(a[i+1]-a[i]) <= 1)
			break;
	}
	return ans;
}


int main()
{
	for(int i=0;i<10;++i) F[1][i] = 1;
	for(int i=2;i<=11;++i)
		for(int j=0;j<=9;++j)
			for(int k=0;k<=9;++k)
				if(abs(j-k) >= 2)
					F[i][j] += F[i-1][k];
	int A,B;
	while(~scanf("%d%d",&A,&B))
	{
		int tmp1 = solve(A);
		int tmp2 = solve(B+1);
		printf("%d\n",tmp2-tmp1);
	}
}
