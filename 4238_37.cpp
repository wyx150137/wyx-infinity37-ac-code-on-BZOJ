
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 110000
#define M 210000
using namespace std;
int next[M<<1],to[M<<1],head[N],tot=1;
int deep[N],fa[N],good[N],bad[N],gc,bc;
bool vis[N];
void add(int x,int y)
{
  to[++tot]=y;
  next[tot]=head[x];
  head[x]=tot;
}
void dfs(int x,int pre)
{
  deep[x]=deep[fa[x]]+1,vis[x]=1;
  int i;
  for(i=head[x];i;i=next[i])
  {
    if((i^1)==pre)  continue;
    if(!vis[to[i]])
    {
      fa[to[i]]=x;
      dfs(to[i],i);
      good[x]+=good[to[i]];
      bad[x]+=bad[to[i]];
    }
    else
    {
      if(deep[to[i]]>deep[x]) continue;
      if(deep[x]-deep[to[i]]&1)
        good[x]++,good[to[i]]--,gc++;
      else
        bad[x]++,bad[to[i]]--,bc++;
    }
  }
}
int main()
{
  int n,m,i,j,k,x,y,ans;
  scanf("%d%d",&n,&m);
  for(i=1;i<=m;i++)
  {
    scanf("%d%d",&x,&y);
    add(x,y),add(y,x);
  }
  for(i=1;i<=n;i++)
  {
    if(!vis[i])
      dfs(i,0);
  }
  for(i=1,ans=0;i<=n;i++)
  {
    if(fa[i]&&bad[i]==bc&&!good[i])
      ans++;
  }
  if(bc==1)
    ans++;
  printf("%d\n",ans);
  return 0;
}
