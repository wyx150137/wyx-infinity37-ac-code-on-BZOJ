
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
LL mod[5] = {0,2,3,4679,35617};
LL fac[5][40000];
LL env[5][40000];
LL c(int n,int m,int modn)
{
    LL tmp = fac[modn][m]*fac[modn][n-m]%mod[modn];
    return fac[modn][n]*env[modn][tmp]%mod[modn];
}
LL lucas(int n,int m,int m_n)
{
    LL ans = 1;
    while(n&&m&&ans) 
    {
        ans = (ans*c(n%mod[m_n],m%mod[m_n],m_n))%mod[m_n];
        n /= mod[m_n];
        m /= mod[m_n];
    }
    return ans;
}
LL xx,yy,d;
void ex_gcd(LL a,LL b)
{
    if(b==0)
    {
        xx = 1;
        yy = 0;
        d = a;
        return ;
    }
    ex_gcd(b,a%b);
    LL tmp = xx;
    xx = yy;
    yy = tmp-a/b*xx;
}
LL M[15],Mt = 999911658ll,ans;
LL a[15],envM[5];
LL remain()
{
    LL ans = 0;
    for(int i = 1;i<= 4;i++)
        ans =(ans+envM[i]*a[i]*M[i]%Mt)%Mt;
    return ans;
}
LL p = 0;
void div(LL x)
{
    LL i;
    for(i = 1;i*i<= x;i++)
    {
        //printf("%lld:\n",i);
        if(x%i==0)
        {
            for(int j = 1;j<= 4;j++)
            {
                a[j] = lucas(x,i,j);
                //printf("%lld ",a[j]);
            }
            p = (p+remain())%Mt;
            //printf("\nnow_ans = %lld\n",p);
            //printf("%lld:\n",x/i);
            if(i*i!=x)
            {
                for(int j = 1;j<= 4;j++)
                {
                    a[j] = lucas(x,x/i,j);
                    //printf("%lld ",a[j]);
                }
                p = (p+remain())%Mt;
                //printf("\nnow_ans = %lld\n",p);
            }
        }
    }
}
LL quick(LL x,LL y)
{
    if(y==0)return 1;
    LL tmp = quick(x,y/2);
    if(y%2==1)return tmp*tmp%(Mt+1)*x%(Mt+1);
    else return tmp*tmp%(Mt+1);
}
int main()
{
    long long n,g;
    scanf("%lld%lld",&n,&g);
    for(int i = 1;i<= 4;i++)
    {
        M[i] = Mt/mod[i];
        ex_gcd(M[i],mod[i]);
        xx = (xx%mod[i]+mod[i])%mod[i];
        envM[i] = xx;
    }
    for(int i = 1;i<= 4;i++)
    {
        fac[i][0] = env[i][1] = 1;
        for(LL j = 1;j<= mod[i]+1;j++)
        {
            //if(j==0){fac[i][j] = 1;env[i][j] = 1;continue;}
            fac[i][j] = fac[i][j-1]*j%mod[i];
            if(j!=1)env[i][j] = ((mod[i]-mod[i]/j)*env[i][mod[i]%j])%mod[i];
        }
    }
    /*for(int i = 1;i<= 4;i++)
    {
        for(LL j = 1;j<= 4;j++)
        {
            printf("%lld %lld:%lld\n",fac[i][j],env[i][j],j*env[i][j]%mod[i]);
        }
    }*/
    div(n);
    p = p+Mt;
    printf("%lld\n",quick(g,p));
    return 0;
}
