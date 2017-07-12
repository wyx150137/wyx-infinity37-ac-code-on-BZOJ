
#include <bits/stdc++.h>
using namespace std;
#define MAXN 10000+500
int n,m,num[2222][4];
int p(int x,int y)
{
    int c=y-x;
    if(c<0)
        c+=3;
    return c;
}
int times(int i,int j, int t1,int t2,int t3)
{
    int ans=0;
    if(j<=0||i<=0) return 0;
    if(i==j)
        ans+=t3;
    else if(i>j)
        ans+=times(j,i-j,t2,t3,t1)+p(t1,t3);
    else
        ans+=times(i,j-i,t1,t3,t2)+p(t2,t3);
    return ans;
}
int main()
{
    while(scanf("%d%d",&n,&m)&&n+m!=-2)
    {
    	if(n==-1&&m==-1)
    		return 0;
        int t=n%3,a,b;
        if(t==0)
            a=1,b=2,t=3;
        else if(t==2)
            a=1,b=3;
        else a=2,b=3;
        int tot=0;
        for(int i=1; i<m; i++)
        {
            if(times(i,m-i,a,b,t)==n)
            {
                num[tot][a]=i;
                num[tot][b]=m-i;
                num[tot++][t]=m;
            }
        }
        printf("%d\n",tot);
        for(int i=0;i<tot;i++)
                printf("%d %d %d\n",num[i][1],num[i][2],num[i][3]);
    }
    return 0;
}
