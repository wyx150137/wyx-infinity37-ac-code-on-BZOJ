
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,m,top,num;
int a[N],st[N],en[N],v[N];
void quit()
{
	puts("0");
	exit(0);
}
struct data
{
	int col[N],cnt,nex[N],pre[N],mn[N];
	void work()
	{
		top=0;
		for(int i=1;i<=cnt;i++) v[i] = read();
		for(int i=1;i<cnt; i++) nex[v[i]] = v[i+1];
		for(int i=n,t;i>=1;i--)
		{
			en[i]=0;
			if(col[i]==v[cnt])en[i]=i;
			else if((t=nex[col[i]])&&pre[t]) en[i]=en[pre[t]];
			if(col[i]==v[1]&&en[i])st[++top]=i;
			pre[col[i]]=i;
		}
		st[top+1]=1;
		for(int i=1;i<=top;i++)
			for(int j=st[i]-1;j>=st[i+1];j--)
				mn[j]=en[st[i]];
	}
}a1,a2;

struct seg
{
	int l,r;
	seg(){}
	seg(int l,int r):l(l),r(r){}
	friend bool operator < (const seg &r1,const seg &r2)
	{return r1.l<r2.l;};
}b[N];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) a[i] = read();
	for(int i=1;i<=n;i++)
		a1.col[i]=a[i],a2.col[i]=a[n-i+1];
	a1.cnt = read(), a2.cnt = read();
	
	a1.work();
	a2.work();
	
	for(int i=1,t,t1,t2;i<=n;i++)
		if(t=a1.pre[a2.col[i]])
		{
			t1=a1.mn[t];t2=a2.mn[i];
			if(t1&&t2&&n-t2+1>=t1) b[++num]=seg(t1,n-t2+1);
		}
		
	sort(b+1,b+1+num);
	int beg=b[1].l,en=b[1].r;top=0;
	
	for(int i=2;i<=num;i++)
	{
		if(b[i].l>en)
		{
			for(int j=beg;j<=en;j++)
				if(a[j]==v[a2.cnt])st[++top]=j;
			beg=b[i].l;en=b[i].r;
		}
		else en=max(en,b[i].r);
	}
	
	for(int i=beg;i<=en;i++)
		if(a[i]==v[a2.cnt])st[++top]=i;
		
	cout << top << endl;
	
	for(int i=1;i<=top;i++)
		printf("%d ",st[i]);
}
