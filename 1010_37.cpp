
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define MaxN 50000+5
int n,l,L,R = 1;
long long sum[MaxN],F[MaxN],Y[MaxN];
int q[MaxN];
long long Z(int x){return F[x]+Y[x]*Y[x];}
long long G(int x){return Y[x]-l-1;}
double calc(int j1,int j2){return 1.0*(Z(j1)-Z(j2))/(Y[j1]-Y[j2]);}
int main()
{
    int x;
    scanf("%d%d",&n,&l);
    for(int i = 1;i<= n;i++)
    {
        scanf("%d",&x);
        sum[i] = sum[i-1]+x;
        Y[i] = sum[i]+i;
    }
    for(int i = 1;i<= n;i++)
    {
        long long Gi = G(i);
        while(L+1<R&&calc(q[L],q[L+1])<=Gi*2)
            L++;
        F[i] = F[q[L]]+(Gi-Y[q[L]])*(Gi-Y[q[L]]);
        while(L+1<R&&calc(q[R-1],i)<=calc(q[R-2],q[R-1]))
            R--;
        q[R++] = i;
    }
    printf("%lld",F[n]);
    return 0;
}
