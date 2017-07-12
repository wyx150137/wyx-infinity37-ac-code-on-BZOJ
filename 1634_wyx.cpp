
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
using namespace std;
inline char getc()
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
    
inline int  read()
{
    static char ch;
    static int   D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
struct data
{
    int T,D;
    inline void Read()
    {
        T=read(),D=read();
    }
    bool operator < (const data &z)const
    {
        return D*z.T>T*z.D;
    }
}E[N];
int main()
{
    int n;
    n=read();
    long long sum=0;
    for(int i=1;i<=n;++i)E[i].Read(),sum+=E[i].D;
    sort(E+1,E+n+1);
    long long ans = 0;
    for(int i=1;i<=n;++i)
    {
        sum-=E[i].D;
        ans+=E[i].T*sum*2;
    }
    cout<<ans;
}
