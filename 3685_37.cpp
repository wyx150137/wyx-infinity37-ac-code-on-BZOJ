
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int sum[N<<2],n,m;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void update(int p,int l,int r,int x,int c)
{
	if(l==r)
		{sum[p]+=c;return ;}
	int mid = (l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x,c);
	else update(p<<1|1,mid+1,r,x,c);
	sum[p] = sum[p<<1]+sum[p<<1|1];
}
int getans(int p,int l,int r,int no,int s)
{
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(s+sum[p<<1]<no)
		return getans(p<<1|1,mid+1,r,no,s+sum[p<<1]);
	else return getans(p<<1,l,mid,no,s);
}
int check(int p,int l,int r,int a,int b)
{
	if(a>b)return 0;
	if(l>=a&&r<=b)
		return sum[p];
	int mid = (l+r)>>1;
	int ret = 0;
	if(a<=mid)ret+=check(p<<1,l,mid,a,b);
	if(b>mid)ret+=check(p<<1|1,mid+1,r,a,b);
	return ret;
}
void work(int opt)
{
	int x;
	if(opt<=2||opt>=5)x = read();
	x++;
	if(opt==1){if(check(1,1,n,x,x)==0)update(1,1,n,x,1);}
	else if(opt==2){if(check(1,1,n,x,x)==1)update(1,1,n,x,-1);}
	else if(opt==3){if(sum[1]==0)printf("-1\n");else printf("%d\n",getans(1,1,n,1,0)-1);}
	else if(opt==4){if(sum[1]==0)printf("-1\n");else printf("%d\n",getans(1,1,n,sum[1],0)-1);}
	else if(opt==5)
		{	
			int tmp = check(1,1,n,1,x-1);
			if(tmp==0)printf("-1\n");
			else printf("%d\n",getans(1,1,n,tmp,0)-1);
		}
	else if(opt==6)
		{
			int tmp = check(1,1,n,x+1,n);
			if(tmp==0)printf("-1\n");
			else printf("%d\n",getans(1,1,n,sum[1]-tmp+1,0)-1);
		}
	else{if(check(1,1,n,x,x)==1)printf("1\n");else printf("-1\n");}
}
int main()
{
	int x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		x = read();
		work(x);
	}
	return 0;
}
