
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#define mod 100003
using namespace std;
long long m,n;
long long pow(long long a,long long b)
{
    long long res=1;
    for(;b;b>>=1,(a*=a)%=mod)
        if(b&1)
            (res*=a)%=mod;
    return res;
}
int main()
{
    cin>>m>>n;
    long long ans = pow(m,n);
    (ans-=m*pow(m-1,n-1))%=mod;
    if(ans<0)ans+=mod;
    cout<<ans<<endl;
}
 
