
#include <cstdio>
const int LIM=14;
int T,n,ans;
int a[LIM<<2];
int quick_work(int x[])
{
    int c1=0,c2=0,c3=0,c4=0,cnt=0;
    for(int i=0;i<LIM;i++)
    {
        if(x[i]==1) c1++;
        else if(x[i]==2) c2++;
        else if(x[i]==3) c3++;
        else if(x[i]==4) c4++;
    }
    while(c2>1&&c4)
     {c2-=2;c4--;cnt++;}
    while(c2&&c3)
     {c2--;c3--;cnt++;}
    while(c1>1&&c4)
     {c1-=2;c4--;cnt++;}
    while(c2&&c4) 
    {c2--;c4--;cnt++;}
    while(c1&&c3) 
    {c1--;c3--;cnt++;}
    return cnt+c1+c2+c3+c4;
}
void DFS(int x[],int step)
{
    int qans=quick_work(x);
    if((!ans)||(ans&&step+qans<ans)) ans=step+qans;
    if(ans&&step>ans) return ;
    bool flag=0;
    int  y[LIM<<2]={0};
    for(int i=0;i<LIM;i++)
    	y[i]=x[i];
    for(int i=2;i<LIM;i++)
    {
        int j=i;
        while(x[j]>=3) 
        	j++;
        if(j-i>=2)
        {
            flag=1;
            for(int j1=j;j1-i>=2;j1--)
            {
                for(int k=i;k<j1;k++) y[k]-=3;
                DFS(y,step+1);
                for(int k=i;k<j1;k++) y[k]+=3;
            }
        }
    }
    for(int i=2;i<LIM;i++)
    {
        int j=i;
        while(x[j]>=2) j++;
        if(j-i>=3)
        {
            flag=1;
            for(int j1=j;j1-i>=3;j1--)
            {
                for(int k=i;k<j1;k++) y[k]-=2;
                DFS(y,step+1);
                for(int k=i;k<j1;k++) y[k]+=2;
            }
        }
    }
    for(int i=2;i<LIM;i++)
    {
        int j=i;
        while(x[j]>=1) j++;
        if(j-i>=5)
        {
            flag=1;
            
            for(int j1=j;j1-i>=5;j1--)
            {
                for(int k=i;k<j1;k++) y[k]--;
                DFS(y,step+1);
                for(int k=i;k<j1;k++) y[k]++;
            }
        }
    }
    qans=quick_work(x);
    if((!ans)||(ans&&step+qans<ans)) ans=step+qans;
}

int main()
{
    scanf("%d%d",&T,&n);
    for(int i=1;i<=T;i++)
    {
        ans=0;
        for(int j=0;j<LIM;j++) 
        	a[j]=0;
        for(int j=1;j<=n;j++)
        {
            int ta,tb;
            scanf("%d%d",&ta,&tb);
            if(ta==1) ta=13;
            else if(ta) ta--;
            a[ta]++;
        }
        DFS(a,0);
        printf("%d\n",ans);
    }

    return 0;
}
