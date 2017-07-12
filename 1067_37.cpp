
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define mod 10007
int n,m;
struct Y
{
    int year,rr;
}num[50005];
struct E
{
    int next,val,no;
}edge[50005];
int logx[50005];
int f[50005][20];
void init()
{
    for(int j = 1;j<= 19;j++)
    {
        for(int i = 1;i<=n;i++)
        {   
            if((i+(1<<(j-1)))<=n)
            {
                if(num[f[i][j-1]].rr>=num[f[i+(1<<(j-1))][j-1]].rr)
                    f[i][j] = f[i][j-1];
                else 
                    f[i][j] = f[i+(1<<(j-1))][j-1];
            }
            else f[i][j]= f[i][j-1];
        }
    }
    logx[1] = 0;
    for(int i = 2;i<= 50000;i++)
        logx[i] = logx[i>>1]+1;
    return ;
}
int check(int l,int r)
{
    if(l>r)return -1;
    int len = r-l+1;
    if(num[f[l][logx[len]]].rr>num[f[r-(1<<logx[len])+1][logx[len]]].rr)
        return f[l][logx[len]];
    else return f[r-(1<<logx[len])+1][logx[len]];
}
void ch(int st,int en)
{
    int l = 0,r = n+1,mid,poss,pose;
    while(l<r)
    {
        mid = (l+r)>>1;
        if(num[mid].year>=st)r = mid;
        else l = mid+1;
    }
    poss = l;
    l = 0;r = n+1;
    while(l<r)
    {
        mid = (l+r)>>1;
        if(num[mid].year>=en)r = mid;
        else l = mid+1;
    }
    pose = l;
    if(num[pose].year>en)
        pose--;
    //printf("%d %d\n",poss,pose);
    //printf("%d %d\n",num[poss].year,num[pose].year);
    if(num[pose].year!=en&&num[poss].year!=st)
    {
        printf("maybe\n");
        return ;
    }
    else if(num[pose].year==en&&num[poss].year!=st)
    {
        if(num[check(poss,pose)].year!=num[pose].year)
            printf("false\n");
        else printf("maybe\n");
    }
    else if(num[pose].year!=en&&num[poss].year==st)
    {
        if(num[check(poss+1,pose)].rr>=num[poss].rr)
            printf("false\n");
        else printf("maybe\n");
    }
    else
    {
        if(num[pose].rr>num[poss].rr)printf("false\n");
        else if(num[check(poss+1,pose)].year!=en)printf("false\n");
        else if(pose-poss!=en-st)printf("maybe\n");
        else printf("true\n");
    }
    return ;
}
int main()
{
    num[0].year = -0x3f3f3f3f;
    //freopen("rains.in","r",stdin);
    //freopen("rains.out","w",stdout);
    scanf("%d",&n);
    for(int i = 1;i<= n;i++)
    {
        scanf("%d%d",&num[i].year,&num[i].rr);
        f[i][0] = i;
    }
    /*for(int j = 1;j<= n;j++)
    {
        for(int i = head[hash(num[j].year)];i;i = edge[i].next)
            printf("%d ",edge[i].val);
        printf("\n");
    }*/
    init();
    scanf("%d",&m);
    for(int i = 1;i<= m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>y){printf("false\n");continue;}
        //int fx = find(x),fy = find(y);
        //printf("fx = %d fy = %d\n",fx,fy);
        //if(num[fy].rr>num[fx].rr){printf("false\n");continue;}
        //if(fx==-1||fy==-1||fy-fx!=y-x){printf("maybe\n");continue;}
        ch(x,y);
    }
    return 0;
}
