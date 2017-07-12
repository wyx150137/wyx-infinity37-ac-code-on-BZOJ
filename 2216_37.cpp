
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 500005;
struct E
{int l,r,p;}que[N];
int a[N],n;
double f[N],g[N];
double cal(int j,int i)
{
	return a[j]+sqrt(abs(i-j))-a[i];
}
int L,R;
int find(E a,int x)
{
	int l = a.l,r = a.r;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(cal(a.p,mid)>cal(x,mid))l = mid+1;
		else r = mid;
	}
	return l;
}
void work(double *F)
{
	L = 0,R = -1;
	for(int i = 1;i<= n;i++)
	{
		que[L].l++;
		while(L<=R&&que[L].l>que[L].r)L++;
		if(L>R||cal(i,n)>cal(que[R].p,n))
		{
			while(L<=R&&cal(que[R].p,que[R].l)<cal(i,que[R].l))
				R--;
			if(L>R)
				que[++R] = (E){i,n,i};
			else
			{
				int t = find(que[R],i);
				que[R].r = t-1;
				que[++R] = (E){t,n,i};
			}
		}
		F[i] = cal(que[L].p,i);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	work(f);
	for(int i = 1;i<=(n>>1);i++)swap(a[i],a[n-i+1]);
	work(g);
	for(int i = 1;i<= n;i++)
		printf("%d\n",max(0,(int)ceil(max(g[n-i+1],f[i]))));
	return 0;
}
