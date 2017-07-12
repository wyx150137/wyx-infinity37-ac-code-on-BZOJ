
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e5+20;
struct data
{
	ll f[4][4];
	data(){memset(f,0,sizeof(f));}
	data(ll a,ll b,ll c)
	{
		f[0][0]=f[3][3]=a;f[1][1]=b;f[2][2]=c;
		f[0][1]=max(a,b),f[1][2]=max(b,c),f[2][3]=max(c,a);
		f[0][2]=f[1][3]=f[0][3]=max(max(b,c),a);
	}
	friend data operator +(const data &a,const data &b)
	{
		data c;
		for(int l = 1;l<= 4;l++)
			for(int i = 0;i+l-1<4;i++)
			{
				int j = i+l-1;
				for(int k = i;k<= j;k++)
					c.f[i][j]=max(c.f[i][j],a.f[i][k]+b.f[k][j]);
			}
		return c;
	}
}s[N];
int fa[N],size[N],ch[N][2];
int rt,mark,A[N],B[N],C[N],L[N],n,cnt,q[N],top,tms;
ll Size[N],tot;
void Push_up(int x)
{
	s[x] = data(1ll*A[x]*L[x],1ll*B[x]*L[x],1ll*C[x]*L[x]);
	if(ch[x][0])s[x] = s[ch[x][0]]+s[x];
	if(ch[x][1])s[x] = s[x]+s[ch[x][1]];
	Size[x] = Size[ch[x][0]]+Size[ch[x][1]]+L[x];
	size[x] = size[ch[x][0]]+size[ch[x][1]]+1;
}
int Find(int x,ll pos)
{
	ll Sz1 = Size[ch[x][0]],Sz2 = Sz1+L[x];
	if((Sz1<pos||(!ch[x][0]&&!pos))&&Sz2>=pos)return x;
	else if(Sz1>=pos)return Find(ch[x][0],pos);
	else {tot+=Sz2;return Find(ch[x][1],pos-Sz2);}
}
void Insert(int &x,int ai,int bi,int ci,ll pos,int len,int last=0)
{
	if(!x)
	{
		x = ++cnt;
		s[x] = data(1ll*ai*len,1ll*bi*len,1ll*ci*len);
		L[x]=Size[x]=len;
		A[x]=ai,B[x]=bi,C[x]=ci;fa[x]=last;size[x]=1;
		return ;
	}
	ll Sz = Size[ch[x][0]]+L[x];
	if(pos<Sz)Insert(ch[x][0],ai,bi,ci,pos,len,x);
	else Insert(ch[x][1],ai,bi,ci,pos-Sz,len,x);
	Push_up(x);
	if(max(size[ch[x][0]],size[ch[x][1]])>0.7*size[x])mark=x;
}
void Update(int x,int k,ll pos,int Len)
{
	if(x==k)
	{
		L[x] = Len;
		Push_up(x);
		return ;
	}
	if(Size[ch[x][0]]>=pos)Update(ch[x][0],k,pos,Len);
	else Update(ch[x][1],k,pos-L[x]-Size[ch[x][0]],Len);
	Push_up(x);
}
void Dfs(int x)
{
	if(ch[x][0])Dfs(ch[x][0]);
	q[++top]=x;
	if(ch[x][1])Dfs(ch[x][1]);
}
void Build(int &x,int l,int r,int last)
{
	if(l>r)
	{
		x=0;
		return ;
	}
	int mid = (l+r)>>1;
	x = q[mid];fa[x] = last;
	Build(ch[x][0],l,mid-1,x);
	Build(ch[x][1],mid+1,r,x);
	Push_up(x);
}
void rebuild(int x)
{
    mark=top=0;
    Dfs(x);
    int y=fa[x];
    if(!y) Build(rt,1,top,0);
    else Build(ch[y][ch[y][1]==x],1,top,y);
}

int main()
{
	scanf("%d",&n);
	Insert(rt,0,0,0,0,0);
	ll pre = 0;
	for(int i = 1;i<= n;i++)
	{
		ll pi;int ai,bi,ci,x;
		scanf("%lld%d%d%d%d",&pi,&ai,&bi,&ci,&x);
		tot = tms = 0;
		int k = Find(rt,pi);
		if(tot+Size[ch[k][0]]+L[k]!=pi)
		{
			ll Left=tot+Size[ch[k][0]]+L[k]-pi;
            tms=0;
            Update(rt,k,pi,L[k]-Left);    
            Insert(rt,ai,bi,ci,pi,x);
            if(mark) rebuild(mark);
            Insert(rt,A[k],B[k],C[k],pi+x,Left);
		}else Insert(rt,ai,bi,ci,pi,x);
		printf("%lld\n",s[rt].f[0][3]-pre);
		pre = s[rt].f[0][3];
		if(mark)rebuild(mark);
	}
	return 0;
}
