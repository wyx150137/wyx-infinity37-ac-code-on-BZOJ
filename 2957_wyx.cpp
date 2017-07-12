
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
const int N = 100000+5;
const int M = N << 2;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

double Max[M];
int cnt[M];

int calc(int k,int L,int R,double val)
{
	if(L == R) return val < Max[k];
	int mid = (L + R) >> 1;
	if(val >= Max[k<<1]) return calc(k<<1|1,mid+1,R,val);
	else return cnt[k] - cnt[k<<1] + calc(k<<1,L,mid,val);
}

void change(int k,int L,int R,int pos,double val)
{
	if(L == R) 
	{
		cnt[k] = 1;
		Max[k] = val;
		return;
	}
	int mid = (L+R) >> 1;
	if(pos <= mid) change(k<<1,L,mid,pos,val);
	else change(k<<1|1,mid+1,R,pos,val);
	Max[k] = max(Max[k<<1],Max[k<<1|1]);
	cnt[k] = cnt[k<<1] + calc(k<<1|1,mid+1,R,Max[k<<1]);
}

int main()
{
	int n = read(), m = read(), x , y;
	for(int i=1;i<=m;++i){
		x = read() ,y = read();
		change(1,1,n,x,(double)y/x);
		printf("%d\n",cnt[1]);
	}
}
