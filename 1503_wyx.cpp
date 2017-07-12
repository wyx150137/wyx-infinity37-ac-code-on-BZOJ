
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#define M 100000+5
using namespace std;
struct treap
{
	int l,r,num;
	int rnd;
	int size;
}tr[M];
int root,size,delta,ans,cnt;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch <'0' || ch > '9'){if(ch =='-')f=-1;ch = getchar();}
	while(ch >='0' && ch<= '9'){x=(x<<1)+(x<<3)+ch -'0'; ch = getchar();}
	return x*f;
}
void updata(int k)
{
	tr[k].size = tr[tr[k].l].size + tr[tr[k].r].size + 1;
}

void rturn(int &k)
{
	int t = tr[k].l;
	tr[k].l=tr[t].r;
	tr[t].r=k;
	tr[t].size = tr[k].size;
	updata(k);
	k = t;
}

void lturn(int &k)
{
	int t = tr[k].r;
	tr[k].r=tr[t].l;
	tr[t].l=k;
	tr[t].size = tr[k].size;
	updata(k);
	k = t;
}

void insert(int &k,int x)
{
	if(!k)
	{
		k = ++cnt;
		tr[k].rnd = rand();
		tr[k].num = x;
		tr[k].size = 1;
		return;
	}
	tr[k].size ++;
	if(x<tr[k].num)
	{
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd < tr[k].rnd)
			rturn(k);
	}
	else
	{
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd < tr[k].rnd)
			lturn(k);
	}
}

int del(int &k,int x)
{
	int t ;
	if(!k)return 0;
	if(x > tr[k].num)
	{
		t = tr[tr[k].l].size + 1;
		k = tr[k].r;
		return t + del(k,x);
	}
	else
	{
		t = del(tr[k].l,x);
		tr[k].size -= t;
		return t;
	}
}

int find(int k,int x)
{
	if(tr[tr[k].l].size + 1 == x)return tr[k].num + delta;
	else if(tr[tr[k].l].size +1 < x)return find(tr[k].r,x-tr[tr[k].l].size -1 );
	else return find(tr[k].l,x);
}

int main()
{
	int n=read(),m=read();
	char ch[10];
	srand(2000);
	while(n--)
	{
		scanf("%s",ch);
		int x=read();
		//cout<<x<<endl;
		if(ch[0]=='I')
			if(x>=m)insert(root,x-delta);
	    if(ch[0]=='A')
	    	delta+=x;
	    if(ch[0]=='S')
	    	{delta-=x;ans+=del(root,m-delta);}
	    if(ch[0]=='F')
        {
			if(x>tr[root].size)printf("-1\n");
			else printf("%d\n",find(root,tr[root].size-x+1));
        }
	}
	cout<<ans;
}
