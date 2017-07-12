
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;  
#define MAXN 1000005  
#define MAXM 1000005  
#define INF 1000000000  
#define MOD 1000000007  
#define eps 1e-8  
#define ll long long  
int n,m;  
int M=1;  
int a[MAXN];  
ll c[MAXN];  
ll len[MAXN];  
int tot;  
int L[MAXN],R[MAXN];  
int ta[MAXN];  
void cal(int l,int r,int d){  
    int i,j;  
    if(!d)
        return ;  
    int t=0;  
    int lst=l;  
    for(i=l;i<=r;i++)
    {  
        t++;  
        if(t==len[d-1]||i==r)
        {  
            cal(lst,i,d-1);  
            lst=i+1;  
            t=0;  
        }  
    }  
    t=0;  
    lst=l;  
    tot=0;  
    for(i=l;i<=r;i++)
    {  
        t++;  
        if(t==len[d-1]||i==r)
        {  
            tot++;  
            L[tot]=lst;  
            R[tot]=i;  
            lst=i+1;  
            t=0;  
        }  
    }  
    for(i=tot;i>1;i--)
    {  
        for(j=L[i];j<=R[i];j++)
        {  
            c[j]-=c[j-len[d-1]];  
        }  
    }  
}  
int main()
{  
    int i;  
    scanf("%d",&n);  
    for(i=1;i<=n;i++)
    {  
        scanf("%d",&a[i]);  
    }  
    int tn=0;  
    for(i=1;i<=n;i++)
    {  
        if(a[i]!=1)
        {  
            ta[++tn]=a[i];  
        }  
    }  
    scanf("%d",&m);  
    ta[tn+1]=m;  
    for(i=1;i<=m;i++)
    {  
        scanf("%lld",&c[i]);  
    }  
    len[0]=1;  
    for(i=1;i<=tn+1;i++)
    {  
        len[i]=len[i-1]*ta[i];  
        if(len[i]>=m)
        {  
            cal(1,m,i);  
            break;  
        }  
    }  
    printf("%d\n",n);  
    for(i=1;i<=n;i++)
    {  
        printf(i==n?"%d\n":"%d ",a[i]);  
    }  
    printf("%d\n",m);  
    for(i=1;i<=m;i++)
    {  
        printf(i==m?"%lld\n":"%lld ",c[i]);  
    }  
    return 0;  
}  
