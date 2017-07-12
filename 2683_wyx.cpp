
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
const int N = 500000+5;
const int M = 200000*4+5;
using namespace std;

int tr[N];
int T[M];

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
		ans += tr[x];
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

struct data
{
	int x,y,times,ans,opt,tmp;
	bool operator < (const data &z)const
	{
		if(times != z.times) return times < z.times;
		if(y != z.y) return y < z.y;
		return x < z.x;
	}
}a[M];

bool cmp1(const data &a,const data &b)
{
	if(a.y != b.y) return a.y < b.y;
	else if(a.x != b.x) return a.x < b.x;
	else return a.times < b.times;
}

void solve(int L,int R)
{
	if(L==R) return;
	int mid = (L+R) >> 1;
	solve(L,mid);
	sort(a+L,a+mid+1,cmp1);
	sort(a+mid+1,a+R+1,cmp1);
	for(int i=L,j=mid+1;j<=R;++j)
	{
		while((a[i].y < a[j].y || ((a[i].y == a[j].y) && (a[i].x <= a[j].x))) && (i <= mid))
		{
			change(a[i].x,a[i].tmp);
			i ++;
		}
		if(a[j].opt != 1)
			a[j].ans += ask(a[j].x);
	}
	for(int i=L;i<=mid;++i) Tchange(a[i].x);
	sort(a+L,a+R+1);
	solve(mid+1,R);
}


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
 

bool F[N];

int main()
{
	read();
	int cnt = 0,tt=0;
	while(1)
	{
		cnt ++;
		int opt = read();
		if(opt == 3) break;
		else if(opt == 1)
		{
			int x = read()+1, y = read()+1, A = read();
			++tt; a[tt].x = x , a[tt].y = y, a[tt].times = cnt;
			a[tt].opt = 1, a[tt].tmp = A;
		}
		else
		{
			F[cnt] = 1;
			int x1 = read()+1, y1 = read()+1, x2 = read()+1, y2 = read()+1;
			++tt ; a[tt].x = x1-1 , a[tt].y = y1-1 , a[tt].times = cnt,a[tt].opt =2;
			++tt ; a[tt].x = x2 , a[tt].y = y2 , a[tt].times = cnt,a[tt].opt =2;
			++tt ; a[tt].x = x1-1 , a[tt].y = y2 , a[tt].times = cnt,a[tt].opt =3;
			++tt ; a[tt].x = x2 , a[tt].y = y1-1 , a[tt].times = cnt,a[tt].opt =3;
		}
	}
	sort(a+1,a+tt+1);
	solve(1,tt);

	for(int i=1;i<=tt;++i)
	{
		if(a[i].opt == 2) T[a[i].times] += a[i].ans;
		else T[a[i].times] -= a[i].ans;
	}
	for(int i=1;i<=cnt;++i)
		if(F[i])
			printf("%d\n",T[i]);
}
