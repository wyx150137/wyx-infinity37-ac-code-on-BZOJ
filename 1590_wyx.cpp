
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define M 500000+5
using namespace std;
struct Trie
{
	Trie *son[2];
	int end; //截至
	int flag;//路过
	Trie () {son[0]=son[1]=NULL;end=flag=0;}
}tr[M],*p,*rt=tr,*C=tr;
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch <'0'||ch >'9'){if(ch=='-')f=-1;ch = getchar();}
	while(ch >='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}
int T[500000+45];
void insert()
{
	p = rt;
	for(int i=1;i<=T[0];++i)
	{
		p->flag++;
		if(!p->son[T[i]])
			p->son[T[i]] = ++C;
		p = p-> son[T[i]];
	}
	p->flag++;
	p->end++;
}
int find()
{
	p = rt;
	int ans = 0;
	for(int i=1;i<=T[0];++i)
	{
		ans += p->end;
		if(i==T[0]&&p->son[T[i]])ans += p->son[T[i]]->flag;
		if(!p->son[T[i]])break;
		p = p->son[T[i]];
	}
	return ans;
}
int main()
{
	//freopen("06.in","r",stdin);
	rt = ++C;
	int m=read(),n=read();
	for(int i=1;i<=m;++i)
	{
		int k=read();
		T[0]=k;
		for(int i=1;i<=k;++i)
			T[i]=read();
		insert();
	}
	for(int i=1;i<=n;++i)
	{
		int k=read();
		T[0]=k;
		for(int i=1;i<=k;++i)
			T[i]=read();
		printf("%d\n",find());
	}
}
