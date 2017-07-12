
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 1000000+5
using namespace std;
int fa[N];
int stack[N];
int find(int x)
{
	while(fa[x]!=x&&fa[x])
	{
		stack[++stack[0]] = x;
		x=fa[x];
	}
	fa[x] = x;
	while(stack[0])
		fa[stack[stack[0]--]] = x;
	return x;
}
int c[N];
int main()
{
	int n,m,p,q;
    cin>>n>>m>>p>>q;
    for(int i = m;i>=1;i--)
    {
        int x = ((long long)i*p+q)%n+1;
        int y = ((long long)i*q+p)%n+1;
        if(x>y)swap(x,y);
        for(int j = find(x);j<=y;j = find(j))
        {
            c[j] = i;
            fa[j] = j+1;
        }
    }
    for(int i = 1;i<= n;i++)
        printf("%d\n",c[i]);
    return 0;
}
