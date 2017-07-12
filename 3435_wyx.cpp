
#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 100100
#define ALPHA 0.88
using namespace std;

int n;
long long last_ans;
int r[M];

namespace Graph{

	struct abcd{
		int to,f,next;
		int ban;
	}table[M<<1];
	int head[M],tot=1;

	int ancestor[M][17],dpt[M],dis[M];

	void Add(int x,int y,int z)
	{
		table[++tot].to=y;
		table[tot].f=z;
		table[tot].next=head[x];
		head[x]=tot;
	}

	void Build_LCA(int x)
	{
		int j;
		for(j=1;j<=16;j++)
			ancestor[x][j]=ancestor[ancestor[x][j-1]][j-1];
	}

	int LCA(int x,int y)
	{
		int j;
		if(dpt[x]<dpt[y])
			swap(x,y);
		for(j=16;~j;j--)
			if(dpt[ancestor[x][j]]>=dpt[y])
				x=ancestor[x][j];
		if(x==y) return x;
		for(j=16;~j;j--)
			if(ancestor[x][j]!=ancestor[y][j])
				x=ancestor[x][j],y=ancestor[y][j];
		return ancestor[x][0];
	}

	int Distance(int x,int y)
	{
		int lca=LCA(x,y);
		return dis[x]+dis[y]-2*dis[lca];
	}

}

struct Treap{

	static queue<Treap*> bin;
	
	Treap *ls,*rs;
	int val,key;
	int cnt,size;

	void* operator new (size_t,int _)
	{
		Treap *re;
		if(bin.size())
			re=bin.front(),bin.pop();
		else
		{
			static Treap *mempool,*C;
			if(C==mempool)
				mempool=(C=new Treap[1<<16])+(1<<16);
			re=C++;
		}
		re->ls=re->rs=0x0;
		re->val=_;re->key=rand();//信仰！
		re->cnt=re->size=1;
		return re;
	}

	void operator delete (void *p)
	{
		bin.push((Treap*)p);
	}

	void Push_Up()
	{
		size=cnt;
		if(ls) size+=ls->size;
		if(rs) size+=rs->size;
	}

	friend void Zig(Treap *&x)
	{
		Treap *y=x->ls;
		x->ls=y->rs;
		y->rs=x;x=y;
		x->rs->Push_Up();
		x->Push_Up();
	}

	friend void Zag(Treap *&x)
	{
		Treap *y=x->rs;
		x->rs=y->ls;
		y->ls=x;x=y;
		x->ls->Push_Up();
		x->Push_Up();
	}

	friend void Insert(Treap *&x,int y)
	{
		if(!x)
		{
			x=new (y)Treap;
			return ;
		}
		if(y==x->val)
			x->cnt++;
		else if(y<x->val)
		{
			Insert(x->ls,y);
			if(x->ls->key>x->key)
				Zig(x);
		}
		else
		{
			Insert(x->rs,y);
			if(x->rs->key>x->key)
				Zag(x);
		}
		x->Push_Up();
	}

	friend void Decomposition(Treap *&x)
	{
		if(!x) return ;
		Decomposition(x->ls);
		Decomposition(x->rs);
		delete x;x=0x0;
	}

	friend int Query(Treap *x,int y)
	{
		if(!x) return 0;
		if(y<x->val)
			return Query(x->ls,y);
		else
			return (x->ls?x->ls->size:0) + x->cnt + Query(x->rs,y);
	}

};

queue<Treap*> Treap :: bin;

namespace Dynamic_TDC{

	using namespace Graph;

	int fa[M],v[M],T;

	Treap *tree1[M],*tree2[M];

	set<int> to[M];
	
	void DFS(int x)
	{
		set<int>::iterator it;
		v[x]=T;
		for(it=to[x].begin();it!=to[x].end();it++)
		{
			DFS(*it);
			Decomposition(tree2[*it]);
		}
		to[x].clear();
		Decomposition(tree1[x]);
	}

	int Get_Size(int x,int from)
	{
		int i,re=1;
		for(i=head[x];i;i=table[i].next)
		{
			if(v[table[i].to]!=T)
				continue;
			if(table[i].ban==T)
				continue;
			if(table[i].to==from)
				continue;
			re+=Get_Size(table[i].to,x);
		}
		return re;
	}

	int Get_Centre_Of_Gravity(int x,int from,int size,int &cg)
	{
		int i,re=1,flag=true;
		for(i=head[x];i;i=table[i].next)
		{
			if(v[table[i].to]!=T)
				continue;
			if(table[i].ban==T)
				continue;
			if(table[i].to==from)
				continue;
			int temp=Get_Centre_Of_Gravity(table[i].to,x,size,cg);
			if(temp<<1>size) flag=false;
			re+=temp; 
		}
		if(size-re<<1>size) flag=false;
		if(flag) cg=x;
		return re;
	}

	void DFS(int x,int from,int dpt,Treap *&p)
	{
		int i;
		Insert(p,dpt-r[x]);
		for(i=head[x];i;i=table[i].next)
		{
			if(v[table[i].to]!=T)
				continue;
			if(table[i].ban==T)
				continue;
			if(table[i].to==from)
				continue;
			DFS(table[i].to,x,dpt+table[i].f,p);
		}
	}
	
	int Tree_Divide_And_Conquer(int x)
	{
		int i,size=Get_Size(x,0);
		Get_Centre_Of_Gravity(x,0,size,x);
		DFS(x,0,0,tree1[x]);
		for(i=head[x];i;i=table[i].next)
		{
			if(v[table[i].to]!=T)
				continue;
			if(table[i].ban==T)
				continue;
			
			Treap *p=0x0;
			DFS(table[i].to,x,table[i].f,p);
			
			table[i].ban=table[i^1].ban=T;
			
			int temp=Tree_Divide_And_Conquer(table[i].to);
			tree2[temp]=p;fa[temp]=x;to[x].insert(temp);
		}
		return x;
	}

	void Rebuild(int x)
	{
		++T;DFS(x);
		int y=fa[x];
		Treap *p=tree2[x];
		tree2[x]=0x0;
		int temp=Tree_Divide_And_Conquer(x); 
		fa[temp]=y;if(y) to[y].insert(temp);
		tree2[temp]=p;
	}

	void Insert(int x)
	{
		int i;
		
		for(i=x;i;i=fa[i])
		{

			if(fa[i])
			{
				int d1=Distance(x,fa[i]);
				last_ans+=Query(tree1[fa[i]],r[x]-d1);
				last_ans-=Query(tree2[i],r[x]-d1);
				Insert(tree2[i],d1-r[x]);
			}

			int d=Distance(x,i);
			Insert(tree1[i],d-r[x]);
			
		}
		int to_rebuild=0;

		for(i=x;fa[i];i=fa[i])
			if( tree1[i]->size*5>tree1[fa[i]]->size*4)
				to_rebuild=fa[i];

		if(to_rebuild)
			Rebuild(to_rebuild);
	}

}
int main()
{

	srand(150137);
	int i,x,y,z;
	scanf("%*d%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);

		x=x^(last_ans%1000000000);


		Graph::Add(i,x,y);
		Graph::Add(x,i,y);
		Graph::ancestor[i][0]=x;
		Graph::dpt[i]=Graph::dpt[x]+1;
		Graph::dis[i]=Graph::dis[x]+y;
		Graph::Build_LCA(i);
		r[i]=z;

		Dynamic_TDC::to[x].insert(i);
		Dynamic_TDC::fa[i]=x;
		Dynamic_TDC::Insert(i);

		
		printf("%lld\n",last_ans);
	}
}
