
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
long long n,m,p;
bool done[MAXN];
long long fib[6*MAXN],len[MAXN],vis[MAXN];
long long ine[MAXN];
struct Matrix
{
    int n;
    int m;
    long long a[3][3];
    Matrix (){}
    Matrix (int x,int y)
    {
        n=x;
        m=y;
        memset(a,0,sizeof(a));
    }
};
Matrix operator*(Matrix a,Matrix b)
{
    Matrix c(a.n,b.m);
    for(int i=0;i<a.n;i++)
    {
        for(int j=0;j<b.m;j++)
        {
            for(int k=0;k<a.m;k++)
            {
                (c.a[i][j]+=a.a[i][k]*b.a[k][j]%p)%=p ;
            }
        }
    }
    return c;
}
Matrix pow(Matrix a,long long x)
{
    Matrix  res (a.n,a.m);
    for(int i=0;i<a.n;i++)
        res.a[i][i]=1;
    for(; x; x>>=1 , a=a*a)
    {
        if(x&1)
        {
            res=res*a;
        }
    }
    return res;
}
Matrix res[MAXN];
Matrix ans,mul,de;
long long  exe_gcd(long long a,long long b,long long c)
{
    if(a==0)
        return -1;
    else if(c%a==0)
        return c/a;
    long long t=exe_gcd(b%a,a,(-c%a+a)%a);
    if (t == -1) 
        return -1;
    else
        return (t*b+c)/a;
}
void solve()
{
    mul.n=mul.m=de.m=de.n=3;
    bool flag=false;
    ans.n=1;
    ans.m=3;
    ans.a[0][0]=ans.a[0][2]=1;
    mul.a[0][1]=mul.a[1][0]=mul.a[1][1]=mul.a[2][2]=1;
    de.a[0][0]=de.a[1][1]=de.a[2][2]=1;
    de.a[2][1]=-1;
    for(long long t=1;n;)
    {
        if(!ine[t])
            ine[t]=exe_gcd(t,m,1);
        if(ine[t]==-1)
        {
            ans=ans*pow(mul,n);
            n=0;
        }
        else
        {
            if(!done[t]||flag)
            {
                done[t]=1;
                if(!vis[ine[t]])
                {
                    ans=ans*pow(mul,n);
                    n=0;
                }
                else
                {
                    len[t]=vis[ine[t]];
                    if(n>=len[t])
                    {
                        n-=len[t];
                        res[t]=pow(mul,len[t])*de;
                        ans=ans*res[t];
                        (t*=fib[len[t]-1])%=m;
                    }
                    else
                    {
                        ans = ans*pow(mul,n);
                        n = 0;
                    }
                }
            }
            else
            {
                long long cnt=0;
                Matrix ret(3,3);
                ret.a[0][0]=ret.a[1][1]=ret.a[2][2]=1;
                for (long long i = t * fib[len[t] - 1] % m;
                               i != t;
                               (i *= fib[len[i] - 1]) %= m
                    )
                {    
                    cnt += len[i];
                    ret = ret * res[i];
                }
                cnt += len[t];
                ret = res[t] * ret;
                ans = ans * pow(ret, n / cnt);
                n %= cnt;
                flag = true;
            }
        }
    }
}
int main()
{
    cin>>n>>m>>p;
    fib[1]=fib[2]=1;
    for(int i=3;i;i++)
    {
        fib[i]=(fib[i-1]+fib[i-2])%m;
        if (!vis[fib[i]])
            vis[fib[i]] = i;
        if (fib[i] == 1 && fib[i - 1] == 1)
            break;
    }
    solve();
    printf("%lld", (ans.a[0][1] + p) % p);
    return 0;
}
 
