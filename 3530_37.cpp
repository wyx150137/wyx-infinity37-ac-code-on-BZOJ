
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define mod 1000000007
#define LL long long
#include <queue>
using namespace std;
struct trie
{
    int ch[12],mark,fail,last;
}t[2005];
char N[1500],s[1500];
int m,tot=0,n[2000],l;
LL f[1205][2005][3];
void Insert(char s[])
{
    int x=0;
    for (int i=0;i<strlen(s);i++)
    {
        int c=s[i]-'0';
        if (!t[x].ch[c])
            t[x].ch[c]=++tot;
        x=t[x].ch[c];
    }
    t[x].mark=1;
}
void Make_fail()
{
    queue<int> q;
    for (int i=0;i<=9;i++)
        if (t[0].ch[i]) 
            q.push(t[0].ch[i]);
    while (!q.empty())
    {
        int x=q.front();
        q.pop();
        for (int i=0;i<=9;i++)
            if (t[x].ch[i])
            {
                int y=t[x].ch[i];
                q.push(y);
                int v=t[x].fail;
                while (v&&!t[v].ch[i])
                    v=t[v].fail;
                t[y].fail=v=t[v].ch[i];
                t[y].last=t[v].mark?v:t[v].last;
            }
    }
}
void Add(LL &a,LL b)
{
    a=(a+b)%mod;
}
int C(int a,int b)
{
    if (a==b) return 1;
    if (a<b) return 0;
    return 2;
}
void DP()
{
    LL ans=0;
    for (int k=1;k<=9;k++)
    {
        int v=t[0].ch[k];
        if (!t[v].mark&&!t[v].last)
            f[1][t[0].ch[k]][C(k,n[1])]+=1;
    }
    for (int j=0;j<=tot;j++)
        ans=(ans+f[1][j][0]+f[1][j][1]+f[1][j][2])%mod;
    for (int i=1;i<l;i++)
    {
        for (int j=0;j<=tot;j++)
            if (f[i][j][0]||f[i][j][1]||f[i][j][2])
                for (int k=0;k<=9;k++)
                {
                    int v=j;
                    while (v&&!t[v].ch[k])
                        v=t[v].fail;
                    v=t[v].ch[k];
                    if (!t[v].mark&&!t[v].last)
                    {
                        int x=C(k,n[i+1]);
                        if (x==0)
                            Add(f[i+1][v][0],f[i][j][0]+f[i][j][1]),
                            Add(f[i+1][v][2],f[i][j][2]);
                        if (x==1)
                            Add(f[i+1][v][0],f[i][j][0]),
                            Add(f[i+1][v][1],f[i][j][1]),
                            Add(f[i+1][v][2],f[i][j][2]);
                        if (x==2)
                            Add(f[i+1][v][0],f[i][j][0]),
                            Add(f[i+1][v][2],f[i][j][1]+f[i][j][2]);
                    }
                }
        for (int j=0;j<=tot;j++)
        {
            Add(ans,f[i+1][j][0]+f[i+1][j][1]);
            if (i+1!=l)
                Add(ans,f[i+1][j][2]);
        }
    }
    printf("%d\n",(int)ans%mod);
}
int main()
{
    scanf("%s",N);
    l=strlen(N);
    for (int i=1;i<=l;i++)
        n[i]=N[i-1]-'0';
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
        scanf("%s",s),Insert(s);
    Make_fail();
    DP();
    return 0;
}
