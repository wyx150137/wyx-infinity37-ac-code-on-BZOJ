
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1100005;
const int M = 35000005;
const int mod = 1048576;
double alpha = 0.81;
int stack[305],top,a[N],n,m,n0;
struct Trie
{
	int ch[M][2],num[M],cnt;
	queue<int>Q;
	int Addpoint()
	{
		if(!Q.empty())
		{
			int tmp = Q.front();Q.pop();
			ch[tmp][0] = ch[tmp][1] = 0;
			num[tmp] = 0;
			return tmp;
		}
		return ++cnt;
	}
	void Delete(int x)
	{
		if(!x)return ;
		Q.push(x);
		Delete(ch[x][0]);Delete(ch[x][1]);
	}
	void Insert(int &now,int v,int dep,int top)
	{
		if(!now)now = Addpoint();
		num[now]+=top;
		if(dep<0)return ;
		if(v>>dep&1)Insert(ch[now][1],v,dep-1,top);
		else Insert(ch[now][0],v,dep-1,top);
	}
	int merge(int x,int y)
	{
		if(!x&&!y)return 0;
		int ret = Addpoint();
		ch[ret][0] = merge(ch[x][0],ch[y][0]);
		ch[ret][1] = merge(ch[x][1],ch[y][1]);
		num[ret] = num[x]+num[y];
		return ret;
	}
	int getans(int x,int dep)
	{
		if(dep<0)return 0;
		int tmp = x>>dep&1,sum = 0;
		for(int i = 1;i<= top;i++)
			sum+=num[ch[stack[i]][tmp^1]];
		for(int i = 1;i<= top;i++)
			stack[i] = ch[stack[i]][sum ? tmp^1 : tmp];
		return getans(x,dep-1)+(sum?1<<dep:0);
	}
}trie;
struct Node
{
	int mx,sx;
	Node(){}
	Node(int mx,int sx):mx(mx),sx(sx){}
	void ins(int x)
	{
		if(x>mx)sx = mx,mx = x;
		else if(x>sx)sx = x;
	}
};
Node merge(Node r1,Node r2)
{
	Node ret = r1;
	ret.ins(r2.mx),ret.ins(r2.sx);
	return ret;
}
struct Balanced_Tree
{
	queue<int>Q;
	int ch[N][2],root[N],fa[N],size[N],val[N],sz[N],b[N];
	int cnt,Root,fre,pre,tar;
	Node n1,v[N];
	int Addpoint()
	{
		if(!Q.empty())
		{
			int t = Q.front();Q.pop();
			ch[t][0]=ch[t][1]=root[t]=fa[t]=size[t]=val[t]=b[t]=0;
			v[t] = Node(0,0);
			return t;
		}
		return ++cnt;
	}
	int NewNode(int x)
	{
		int ret = Addpoint();
		b[ret] = 1;
		val[ret] = x;
		size[ret] = sz[ret] = 1;
		v[ret] = Node(x,0);
		trie.Insert(root[ret],x,20,1);
		return ret;
	}
	void Push_up(int x)
	{
		size[x] = size[ch[x][0]]+size[ch[x][1]];
		sz[x] = size[x]+1;
		root[x] = trie.merge(root[ch[x][0]],root[ch[x][1]]);
		v[x] = merge(v[ch[x][0]],v[ch[x][1]]);
		fa[ch[x][0]] = fa[ch[x][1]] = x;
	}
	int Build(int l,int r)
	{
		if(l>r)return 0;
		if(l==r)return NewNode(a[l]);
		int mid = (l+r)>>1,ret = Addpoint();
		ch[ret][0] = Build(l,mid);
		ch[ret][1] = Build(mid+1,r);
		Push_up(ret);
		return ret;
	}
	void dfs(int x)
	{
		if(!x)return ;
		Q.push(x);
		trie.Delete(root[x]);
		if(b[x]){a[++n] = val[x];return ;}
		dfs(ch[x][0]),dfs(ch[x][1]);
	}
	void Rebuild(int x)
	{
		trie.Delete(root[x]);
		n = 0;
		dfs(ch[x][0]),dfs(ch[x][1]);
		int tmp = Build(1,n);
		if(x==Root)Root = tmp;
		fa[tmp] = fa[x];
		ch[fa[x]][ch[fa[x]][1]==x]=tmp;
	}
	void Insert(int &now,int x,int y)
	{
		if(size[now]==1||!now)
		{
			int t = NewNode(y),ret = Addpoint();
			fa[ret] = pre;
			ch[ret][0] = t,ch[ret][1] = now;
			Push_up(ret);
			now = ret;
			return ;
		}
		pre=now;
		if(size[ch[now][0]]>=x)Insert(ch[now][0],x,y);
		else Insert(ch[now][1],x-size[ch[now][0]],y);
		trie.Insert(root[now],y,20,1);
		v[now].ins(y);
		size[now]++;sz[now]+=2;
		fa[ch[now][0]] = fa[ch[now][1]] = now;
		if(max(sz[ch[now][0]],sz[ch[now][1]])>sz[now]*alpha)
			fre = now;
	}
	void Delete(int &now,int x)
	{
		if(b[now])
		{
			Q.push(now);
			tar = val[now];
			now = 0;
			return ;
		}
		if(size[ch[now][0]]>=x)Delete(ch[now][0],x);
		else Delete(ch[now][1],x-size[ch[now][0]]);
		trie.Insert(root[now],tar,20,-1);
		v[now] = merge(v[ch[now][0]],v[ch[now][1]]);
		size[now]--;sz[now]--;
		fa[ch[now][0]] = fa[ch[now][1]] = now;
		if(max(sz[ch[now][0]],sz[ch[now][1]])>sz[now]*alpha)
			fre = now;
	}
	void Insert(int x,int y)
	{
		fre = 0;
		Insert(Root,x,y);
		if(fre)
			Rebuild(fre);
	}
	void Delete(int x)
	{
		fre = 0;
		Delete(Root,x);
		if(fre)
			Rebuild(fre);
	}
	void Find(int now,int pre,int x,int y)
	{
		if(pre+1>=x&&pre+size[now]<=y)
		{
			stack[++top] = root[now];
			n1 = merge(n1,v[now]);
			return ;
		}
		if(pre+size[ch[now][0]]>=x)
			Find(ch[now][0],pre,x,y);
		if(pre+size[ch[now][0]]<y)
			Find(ch[now][1],pre+size[ch[now][0]],x,y);
	}
	Node Find(int x,int y)
	{
		top = 0;
		n1 = Node(0,0);
		Find(Root,0,x,y);
		return n1;
	}
}sheep;
int main()
{
	int lastans = 0;
	scanf("%d%d",&n,&m);n0=n;
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	sheep.Root=sheep.Build(1,n);
	int x,y;
	char opt[3];
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='I')
		{
			scanf("%d%d",&x,&y);
			x = (x+lastans)%n0+1,y = (y+lastans)%mod;
			n0++;
			sheep.Insert(x,y);
		}else if(opt[0]=='D')
		{
			scanf("%d",&x);
			x = (x+lastans)%n0+1;n0--;
			sheep.Delete(x);
		}else if(opt[0]=='C')
		{
			scanf("%d%d",&x,&y);
			x = (x+lastans)%n0+1,y = (y+lastans)%mod;
			sheep.Delete(x);
			sheep.Insert(x,y);
		}else
		{
			scanf("%d%d",&x,&y);
			x = (x+lastans)%n0+1,y = (y+lastans)%n0+1;
			Node tmp = sheep.Find(x,y);
			lastans = trie.getans(tmp.sx,20);
			printf("%d\n",lastans);
		}
		//printf("Ask:%c %d %d\nAns = %d\n",opt[0],x,y,lastans);
	}
	return 0;
}
