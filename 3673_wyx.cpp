
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 5;
using namespace std;

  
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

int root[N],ls[M],rs[M];
int tr[M],tmp[M];
int lts[M],rts[M];
int sz,stz,n,m;
int troot[N];

void build_1(int &k,int l,int r)
{
	k = ++sz;
	if(l==r)
	{
		tr[k] = l;
		return ;
	}
	int mid = (l+r)>>1;
	build_1(ls[k],l,mid);
	build_1(rs[k],mid+1,r);
}

void build_2(int &k,int l,int r)
{
	k = ++stz;
	if(l==r)
	{
		tmp[k] = 1;
		return;
	}
	int mid = (l+r)>>1;
	build_2(lts[k],l,mid);
	build_2(rts[k],mid+1,r);
}

void change_1(int l,int r,int x,int &y,int pos,int T)
{
	y = ++sz;
	if(l==r)
	{
		tr[y] = T;
		return;
	}
	int mid = (l+r)>>1;
	ls[y] = ls[x];
	rs[y] = rs[x];
	if(pos <= mid) change_1(l,mid,ls[x],ls[y],pos,T);
	else change_1(mid+1,r,rs[x],rs[y],pos,T);
}	

void change_2(int l,int r,int x,int &y,int pos,int T)
{
	y = ++stz;
	if(l==r)
	{
		tmp[y] = tmp[x] + T;
		return;
	}
	int mid = (l+r)>>1;
	lts[y] = lts[x];
	rts[y] = rts[x];
	if(pos <= mid) change_2(l,mid,lts[x],lts[y],pos,T);
	else change_2(mid+1,r,rts[x],rts[y],pos,T);
}

int ask(int k,int l,int r,int pos)
{
	if(l==r) return k;
	int mid = (l+r)>>1;
	if(pos <= mid)return ask(ls[k],l,mid,pos);
	else return ask(rs[k],mid+1,r,pos);
}

int asksize(int k,int l,int r,int pos)
{
	if(l==r)return tmp[k];
	int mid = (l+r)>>1;
	if(pos <= mid)return asksize(lts[k],l,mid,pos);
	else return asksize(rts[k],mid+1,r,pos);
}

int find(int k,int x)
{
	int p = ask(k,1,n,x);
	if(x == tr[p]) return p;
	int t = find(k,tr[p]);
	change_1(1,n,k,k,tr[p],t);
	return t;
}

bool check(int times,int x,int y,int lmt)
{
	int tt1 = find(root[times],x);
	int tt2 = find(root[times],y);
//	printf("time = %d x = %d y = %d fx = %d fy = %d\n",times,x,y,tr[x],tr[y]);
	if(tt1 == tt2) 
		return asksize(troot[times],1,n,tr[tt1]) >= lmt;
	else return asksize(troot[times],1,n,tr[tt1]) + asksize(troot[times],1,n,tr[tt2]) >= lmt;
}

int main()
{
//	freopen("01.in","r",stdin);
	n = read(),m = read();
	build_1(root[0],1,n);
	build_2(troot[0],1,n);
	int las = 0;
	for(int i=1;i<=m;++i)
	{
		int opt = read();
		if(opt==1)
		{
			int x = read(),y = read();
			int tt1 = find(root[i-1],x);
			int tt2 = find(root[i-1],y);
	//		printf("fx = %d fy = %d\n",tr[tt1],tr[tt2]);
			if(tt1 == tt2)
			{
				root[i] = root[i-1];
				troot[i] = troot[i-1];
				continue;
			}
			else
			{
				int tx1 = asksize(troot[i-1],1,n,tr[tt1]);
				int tx2 = asksize(troot[i-1],1,n,tr[tt2]);
	//			cout << tx1 << " " << tx2 << endl;
				if(tx1 < tx2)
				{
					change_1(1,n,root[i-1],root[i],tr[tt2],tr[tt1]);
					change_2(1,n,troot[i-1],troot[i],tr[tt1],tx2);
				}
				else
				{
					change_1(1,n,root[i-1],root[i],tr[tt1],tr[tt2]);
					change_2(1,n,troot[i-1],troot[i],tr[tt2],tx1);
				}
			}
		}
		else if(opt == 2)
		{
			int k = read();
			root[i] = root[k];
			troot[i] = troot[i-1];
		}
		else
		{
			root[i] = root[i-1];
			troot[i] = troot[i-1];
			int x = read(),y = read();
			if(find(root[i],x) == find(root[i],y))
				las  = 1;
			else las = 0;
			printf("%d\n",las);
		}
	}
}

