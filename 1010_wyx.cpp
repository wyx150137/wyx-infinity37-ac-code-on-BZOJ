
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 50000+5
using namespace std;
long long s[N],c[N],q[N],dp[N],n,l;
inline double slope (int i,int j)
{return 1.0*(dp[i]+s[i]*s[i]-dp[j]-s[j]*s[j])/(s[i]-s[j]);}
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
inline long long read()
{
    static char ch;
    static long long D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;++i)
		c[i]=c[i-1]+read(),s[i]=i+c[i];
	int head=0,tail=0;
	for(int i=1;i<=n;++i)
	{
		long long lenth=s[i]-l-1;
		while(head<tail&&slope(q[head],q[head+1])<=(lenth<<1))
			++head;
		long long H=q[head];
		dp[i]=dp[H]+(lenth-s[H])*(lenth-s[H]);
		while(head<tail&&slope(q[tail],q[tail-1])>=slope(i,q[tail]))
			--tail;
		q[++tail]=i;
	}
	cout<<dp[n];
}
