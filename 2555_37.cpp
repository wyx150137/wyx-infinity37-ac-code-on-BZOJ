
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1200005;
char s[N];
int mask;
struct Splay
{
	Splay *ls,*rs,*fa;
	int val,add_mark;
	Splay();
	void push_down();
	void Add(int x);
}*null = new Splay;
Splay :: Splay ()
{
	ls = rs = fa = null;
	val = add_mark = 0;
}
void Splay :: push_down()
{
	if(fa->ls==this||fa->rs==this)
		fa->push_down();
	if(add_mark)
	{
		ls->Add(add_mark);
		rs->Add(add_mark);
		add_mark = 0;
	}
}
void Splay :: Add(int x)
{
	val+=x;
	add_mark+=x;
}
void go_left(Splay *x)
{
	Splay *y = x->fa;
	y->rs = x->ls;
	x->ls->fa = y;
	x->ls = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa = x;
}
void go_right(Splay *x)
{
	Splay *y = x->fa;
	y->ls = x->rs;
	x->rs->fa = y;
	x->rs = y;
	x->fa = y->fa;
	if(y==y->fa->ls)
		y->fa->ls = x;
	else if(y==y->fa->rs)
		y->fa->rs = x;
	y->fa= x;
}
void splay(Splay *x)
{
	x->push_down();
	Splay *y,*z;
	while(x==x->fa->ls||x==x->fa->rs)
	{
		y = x->fa,z = y->fa;
		if(x==y->ls)
		{
			if(y==z->ls)go_right(y);
			go_right(x);
		}else
		{
			if(y==z->rs)go_left(y);
			go_left(x);
		}
	}
}
void Access(Splay *x)
{
	Splay *y = null;
	while(x!=null)
	{
		splay(x);
		x->rs = y;
		y = x,x = x->fa;
	}
}
void Cut(Splay *x)
{
	Access(x);
	splay(x);
	x->ls->fa = null;
	x->ls = null;
}
void Link(Splay *x,Splay *y)
{
	Cut(x);
	x->fa = y;
}
struct SAM
{
	int trs[N][26],fa[N],len[N];
	int cnt,last;
	Splay *tree[N];
	void init(){cnt=last=1;tree[1] = new Splay;}
	void insert(int x)
	{
		int p,newp,q,newq;
		p = last,newp = ++cnt,last = cnt;
		tree[cnt] = new Splay;
		len[newp] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x] = newp;
		if(!p)
		{
			fa[newp] = 1;
			Link(tree[newp],tree[1]);
		}
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)
			{
				fa[newp] = q;
				Link(tree[newp],tree[q]);
			}
			else
			{
				newq = ++cnt;
				tree[newq] = new Splay;
				fa[newq] = fa[q];
				Link(tree[newq],tree[fa[q]]);
				memcpy(trs[newq],trs[q],sizeof(trs[q]));
				len[newq] = len[p]+1;
				fa[newp] = fa[q] = newq;
				Link(tree[q],tree[newq]);
                Link(tree[newp],tree[newq]);
                tree[q]->push_down();
                tree[newq]->val = tree[q]->val;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x] = newq;
			}
		}
		Access(tree[newp]);
        splay(tree[newp]);
        tree[newp]->Add(1);
	}
	void Insert()
	{
		for(int i = 1;s[i];i++)
			insert(s[i]-'A');
	}
	int Query(char *s)
    {
        int p = 1;
        for(;p;p=trs[p][(*s++)-'A'])
            if(!*s) return tree[p]->push_down(),tree[p]->val;
        return 0;
    }
}sam;
void Decode(char s[],int mask)
{
    int i,n=strlen(s);
    for(i=0;i<n;i++)
    {
        mask=(mask*131+i)%n;
        swap(s[i],s[mask]);
    }
}
int main()
{
	int q;
	char opt[10];
	sam.init();
	scanf("%d",&q);
	scanf("%s",s+1);
	sam.Insert();
	for(int i = 1;i<= q;i++)
	{
		scanf("%s%s",opt,s+1);
		Decode(s+1,mask);
		if(opt[0]=='A')sam.Insert();
		else
		{
			int tmp = sam.Query(s+1);
			mask^=tmp;
			printf("%d\n",tmp);
		}
	}
	return 0;
}
