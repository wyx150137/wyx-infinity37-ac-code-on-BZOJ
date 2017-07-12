
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1001001
using namespace std;
int k,n,top;
pair<int,int> stack[M],a[3];


inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int main()
{
    int i,j;
    cin>>k;
    for(i=1;i<=k;i++)
    {
        n = read();
        for(j=1;j<=n;j++)
        {
            stack[++top]=pair<int,int>(read(),i);
        }
    }
    sort(stack+1,stack+top+1);
    for(i=1;i<=top;i++)
    {
        for(j=0;j<3;j++)
            if(stack[i].second==a[j].second)
            {
                a[j]=stack[i];
                break;
            }
        if(j==3) a[0]=stack[i];
        sort(a,a+3);
        if(a[0].second)
        {
            if(a[0].first+a[1].first>a[2].first)
            {
                printf("%d %d %d %d %d %d\n",a[0].second,a[0].first,a[1].second,a[1].first,a[2].second,a[2].first);
                return 0;
            }
        }
    }
    puts("NIE");
    return 0;
}
