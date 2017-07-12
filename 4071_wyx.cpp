
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 200010 +5 ;
const int M = N << 2;
using namespace std;

LL tr[M];
int cnt[M],T[N],tt;

LL F[N];

#define find(x) ( lower_bound(T+1,T+tt+1,x) - T )

void change(int k,int l,int r,int pos,int y)
{
	if(l == r) {tr[k] += y;cnt[k] ++; return;}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k<<1,l,mid,pos,y);
	else change(k<<1|1,mid+1,r,pos,y);
	tr[k] = tr[k<<1] + tr[k<<1|1], cnt[k] = cnt[k<<1] + cnt[k<<1|1];
}

LL ask(int rank)
{
	int k = 1, l = 1, r = tt, mid;
	LL tmp = 0;
	while(l<r)
	{
		mid = (l+r) >> 1;
		if(cnt[k<<1] < rank)
		{
			tmp += tr[k<<1];
			rank -= cnt[k<<1];
			l = mid + 1; k = k << 1|1;
		}
		else
			r = mid , k <<= 1;
	}
	
	return tr[1] - 2ll * tmp - 2ll * T[l] * rank;
}

struct data
{
	int L, R;
	bool operator < (const data &z)const
	{
		return L + R < z.L + z.R;
	}
}a[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
//	freopen("tt.in","r",stdin);
	int k = read(), n = read(),tmp1,tmp2;
	LL dis = 0;
	int tmpcnt = 0;
	char str1[5],str2[5];
	for(int i=1;i<=n;++i)
	{
		scanf("%s",str1);
		tmp1 = read();
		scanf("%s",str2);
		tmp2 = read();
		if(str1[0] == str2[0]) dis += abs(tmp2 - tmp1);
		else
		{
			T[++tt] = tmp1; T[++tt] = tmp2;
			if(tmp1 > tmp2) swap(tmp1,tmp2);dis++;
			a[++tmpcnt].L = tmp1; a[tmpcnt].R = tmp2;
		}
	}
	n = tmpcnt;
	sort(T+1,T+tt+1);
	int num = 0;
	T[0] = -1;
	for(int i=1;i<=tt;++i) if(T[i] != T[i-1]) T[++num] = T[i];
	tt = num;
	sort(a+1,a+n+1);

	for(int i=1;i<=n;++i)
	{
		change(1,1,tt,find(a[i].L),a[i].L);
		change(1,1,tt,find(a[i].R),a[i].R);
		F[i] = ask(i);
	}
	if(k == 1)  
	{
		cout << F[n] + dis << endl;
		return 0;
	}
	memset(tr,0,sizeof tr);
	memset(cnt,0,sizeof cnt);
	LL ans = F[n] , tmp;
	for(int i=n;i;--i)
	{
		change(1,1,tt,find(a[i].L),a[i].L);
		change(1,1,tt,find(a[i].R),a[i].R);
		tmp = ask(n-i+1);
		ans = min(ans,tmp+F[i-1]);
	}
	cout << ans + dis << endl;
}
