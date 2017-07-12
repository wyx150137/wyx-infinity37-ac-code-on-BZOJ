
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
#define lowbit(x) ((x)&(-x))
using namespace std;

struct data
{
	int x,y,z,cnt;
	int ans;
	friend bool operator == (const data &a,const data &b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
	bool operator < (const data &tmp)const
	{
		if(x != tmp.x) return x < tmp.x;
		else if(y != tmp.y) return y < tmp.y;
		else return z < tmp.z;
	}
	friend bool operator != (const data &a,const data &b)
	{
		return !(a==b);
	}
}a[N];

inline char getc()
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
 
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
 

bool cmp1(const data &a,const data &b)
{
	return a.y ^ b.y ? a.y < b.y : a.z < b.z;
}

int tr[N];

void change(int x,int tt)
{
	while(x < N)
	{
		tr[x] += tt;
		x += lowbit(x); 
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += tr[x] ;
		x -= lowbit(x);
	}
	return ans;
}

void Tchange(int x)
{
	while(x < N)
	{
		tr[x] = 0;
		x += lowbit(x);
	}
}

void solve(int L,int R)
{
	if(L==R){
		a[L].ans += a[L].cnt - 1;
		return; 
	}
	int mid = (L+R) >> 1;
	solve(L,mid);
	solve(mid+1,R);
	sort(a+L,a+mid+1,cmp1);
	sort(a+mid+1,a+R+1,cmp1);
	for(int i=L,j=mid+1;j<=R;++j)
	{
		while(a[i].y <= a[j].y && i <= mid){
			change(a[i].z,a[i].cnt);
			i ++;
		}
		a[j].ans += ask(a[j].z);
	}
	for(int i=L;i<=mid;++i) Tchange(a[i].z);
}

int T[N];

int main()
{
	int n = read(), k = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].y = read(), a[i].z = read() ,a[i].cnt = 1;
	sort(a+1,a+n+1);
	int tt = 0;
	for(int i=1;i<=n;++i) 
		if(a[i] != a[i-1]) a[++tt] = a[i]; 
		else a[tt].cnt ++;
	solve(1,tt);
	for(int i=1;i<=tt;++i) T[a[i].ans] += a[i].cnt;
	for(int i=0;i<n;++i)
		printf("%d\n",T[i]);
}
