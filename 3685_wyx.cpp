
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int M = 3000000+5;
int tr[M],n,m;

int MIN(int k,int l,int r)
{
	if(!tr[k])return -1;
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(tr[k<<1])return MIN(k<<1,l,mid);
	else return MIN(k<<1|1,mid+1,r);
}

int MAX(int k,int l,int r)
{
	if(!tr[k])return -1;
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(tr[k<<1|1])return MAX(k<<1|1,mid+1,r);
	else return MAX(k<<1,l,mid);
}

inline void updata(int k)
{
	tr[k] = tr[k<<1] + tr[k<<1|1];
}

void Insert(int k,int l,int r,int val)
{
	if(l==r){tr[k] = 1;return;}
	int mid = (l+r)>>1;
	if(val <= mid)Insert(k<<1,l,mid,val);
	else Insert(k<<1|1,mid+1,r,val);
	updata(k);
}

void Del(int k,int l,int r,int val)
{
	if(l==r){tr[k] = 0;return;}
	int mid = (l+r)>>1;
	if(val <= mid)Del(k<<1,l,mid,val);
	else Del(k<<1|1,mid+1,r,val);
	updata(k);
}

int find(int k,int l,int r,int val)
{
	if(!tr[k])return -1;
	if(l==r)
	{
		if(tr[k])return 1;
		else return -1;
	}
	int mid = (l+r)>>1;
	if(val <= mid)return find(k<<1,l,mid,val);
	else return find(k<<1|1,mid+1,r,val);
}

int find_pre(int k,int l,int r,int val)
{
	if(val < 0)return -1;
	if(!tr[k]) return -1;
	if(l==r)return l;
	int mid = (l+r)>>1;
	if(val <= mid)return find_pre(k<<1,l,mid,val);
	else{
		int tt = find_pre(k<<1|1,mid+1,r,val);
		if(tt == -1)return MAX(k<<1,l,mid);
		else return tt;
	}
}

int find_las(int k,int l,int r,int val)
{
	if(!tr[k]) return -1;
	if(l == r) return l;
	int mid = (l+r)>>1;
	if(val > mid)return find_las(k<<1|1,mid+1,r,val);
	else{
		int tt = find_las(k<<1,l,mid,val);
		if(tt == -1) return MIN(k<<1|1,mid+1,r);
		else return tt;
	}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(), m = read(),opt,x;
	for(int i=1;i<=m;++i)
	{
		opt = read();
		if(opt == 1){ x = read();
			if(find(1,0,n,x) == -1)
				Insert(1,0,n,x);
		}else if(opt == 2){	x = read();
			if(find(1,0,n,x) == 1)
				Del(1,0,n,x);
		}else if(opt == 3){
				printf("%d\n",MIN(1,0,n));
		}else if(opt == 4){
				printf("%d\n",MAX(1,0,n));
		}else if(opt == 5){ x = read();
				printf("%d\n",find_pre(1,0,n,x-1));
		}else if(opt == 6){ x = read();
				printf("%d\n",find_las(1,0,n,x+1));
		}else{ x = read();
				printf("%d\n",find(1,0,n,x));
		}
		
	}	
}
