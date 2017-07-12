
#include <bits/stdc++.h>
using namespace std;
inline long long read()
{
    long long x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
int T;
long long a,b,x,y,d;
bool jud(long long x,long long y)
{   return (!(x%d))&&(!(y%d)); }
int main()
{
    T=read();
    while(T--)
    {
        a=read(),b=read(),x=read(),y=read();
        d=__gcd(2*a,2*b);
        if(jud(x,y)||jud(x+a,y+b)||jud(x+b,y+a)||jud(x+a+b,y+a+b))puts("Y");
        else puts("N");
    }
}
