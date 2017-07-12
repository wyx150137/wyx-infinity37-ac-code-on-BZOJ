
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define N 1000000+5
int T[N];
int a[N];
struct Person
{
    int num;
    int val;
     
}p[N];
bool cmp1(Person A,Person B)
{
    return  A.val< B.val;
}
bool cmp2(Person A,Person B)
{
    return  A.num< B.num;
}
 
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
int ans[N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        p[i].num=i;
        p[i].val=read();
        T[p[i].val]++;
    }
    sort(p+1,p+n+1,cmp1);
    int Max=p[n].val;
    int tmp=0;
    for(int i=1;i<=n;++i)
    {
        if(tmp ^ p[i].val)
        {       
            int s=p[i].val;
            for(int k=2;k*s<=Max;++k)
                ans[s*k]+=T[s];
            tmp=p[i].val;
        }
    }
    tmp=0;
    for(int i=1;i<=n;++i)
        if(tmp^p[i].val)
        {
            tmp=p[i].val;
            ans[tmp]+=T[tmp]-1;
        }
    sort(p+1,p+n+1,cmp2);
    for(int i=1;i<=n;++i)
        printf("%d\n",ans[p[i].val] );
}
 
