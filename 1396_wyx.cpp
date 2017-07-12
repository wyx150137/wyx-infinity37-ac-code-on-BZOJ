
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
const int N = 1e5+5;
const int M = N << 2;
#define inf 1000000000
using namespace std;
struct node
{
	node *ch[26],*fa;
	int len;
	bool v;
}sam[N*2],*rot,*now;
char s[N];
int n,m,num;
struct segtree
{
	int tr[M],lazy[M];

	void build(int k,int l,int r){
		tr[k] = lazy[k] = inf;
		if(l==r)return;
		int mid = (l+r) >> 1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
	}

	inline void cover(int k,int val){
		lazy[k] = min(lazy[k],val);
		tr[k] = min(tr[k],val);
	}

	inline void down(int k,int l,int r){
		if(lazy[k] == inf || l == r)return;
		cover(k<<1,lazy[k]);
		cover(k<<1|1,lazy[k]);
		lazy[k] = inf;
	}

	void change(int k,int l,int r,int x,int y,int val){
		down(k,l,r);
		if(x <= l && r <= y) cover(k,val);
		else{
			int mid = (l+r) >> 1;
			if(x <= mid) change(k<<1,l,mid,x,y,val);
			if (y > mid) change(k<<1|1,mid+1,r,x,y,val);
			tr[k] = min(tr[k<<1],tr[k<<1|1]);
		}
	}

	inline int ask(int k,int l,int r,int pos){
		down(k,l,r);
		if(l==r)return tr[k];
		int mid = (l+r) >> 1;
		if(pos <= mid) return ask(k<<1,l,mid,pos);
		else return ask(k<<1|1,mid+1,r,pos);
	}

}S,T;

void insert(int w)
{
	node *p=now,*np=&sam[++num];
	np->len=p->len+1; np->v=1;
	while (p&&p->ch[w]==0) p->ch[w]=np,p=p->fa;
	if (!p) np->fa=rot;
	else
	{
		node *q=p->ch[w];
		if (p->len+1==q->len) np->fa=q;
		else
		{
			node *nq=&sam[++num];
			*nq=*q;
			nq->len=p->len+1; nq->v=0;
			np->fa=q->fa=nq;
			while (p&&p->ch[w]==q) p->ch[w]=nq,p=p->fa;
		}
	}
	now=np;
}

int main()
{
	scanf("%s",s);
	n=strlen(s);
	rot=now=&sam[num=0];
	for (int i=0;i<n;i++) insert(s[i]-'a');
	S.build(1,1,n);
	T.build(1,1,n);
	for (int i=1;i<=num;i++) sam[i].fa->v=0;
	for (int i=1;i<=num;i++) 
		if (sam[i].v==1)
		{
			node *p=&sam[i];
			int l=(p->len)-(p->fa->len),r=p->len;
			S.change(1,1,n,l,r,r-l+1);
			if (l>1) T.change(1,1,n,1,l-1,r);
		}
	for (int i=1;i<=n;i++)
		printf("%d\n",min(S.ask(1,1,n,i),T.ask(1,1,n,i)-i+1));
	return 0;
}
