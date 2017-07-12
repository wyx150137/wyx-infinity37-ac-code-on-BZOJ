
#include<iostream>  
#include<cstdio>  
#include<cstring>  
#define ll long long  
#define mod 1000000007  
#define N 10005  
using namespace std;  
  
int n,a[N],pw[N];  
struct bit_node
{  
	int c[N];  
	void clr()
	{ memset(c,0,sizeof(c)); }  
	void add(int x)
	{  
		int i; for (i=x; i<=n; i+=i&-i) c[i]=(c[i]+pw[i-x])%mod;  
	}  
	int getsum(int x)
	{  
		int i,t=0; for (i=x; i; i^=i&-i) t=((ll)c[i]*pw[x-i]+t)%mod;  
		return t;  
	}  
	int qry(int x,int y)
	{  
		int p=getsum(x-1),q=getsum(y);  
		return (q-(ll)p*pw[y-x+1]%mod+mod)%mod;  
	}  
}bit1,bit2;  
int main()
{  
	int cas,i;
	scanf("%d",&cas);  
	pw[0]=1;
	for(i=1; i<=10000; i++) 
		pw[i]=(ll)pw[i-1]*12347%mod;  
	while (cas--)
	{  
		scanf("%d",&n); 
		int x;  
		for (i=1; i<=n; i++) 
			scanf("%d",&a[i]);  
		bit1.clr(); bit2.clr();  
		for (i=1; i<=n; i++)
		{  
			x=min(a[i]-1,n-a[i]);  
			if (x && bit1.qry(a[i]-x,a[i]-1)!=bit2.qry(n-a[i]-x+1,n-a[i])) break;  
			bit1.add(a[i]); bit2.add(n-a[i]+1);  
		}  
		puts((i>n)?"N":"Y");  
	}  
	return 0;  
}  
