
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1000000+10
int pos[N];
int n,m;
long long p;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool check(int len)
{
	int l = 1,r = len;
	long long ans = 0;
	int mid = (l+r)>>1;
	for(int i=l;i<=r;++i)
		ans += abs(pos[mid]-pos[i]);
	//cout<<ans<<endl;
	if(ans <= p)return true;
	while(r<n)
	{
		ans -= pos[mid] - pos[l++];
		ans += pos[++r] - pos[mid];
		mid = (l+r)>>1;
		ans += (pos[mid]-pos[mid-1])*(mid-l);
		ans -= (pos[mid]-pos[mid-1])*(r-mid+1);
		if(ans <= p)
			return true;
	}
	return false;
}


int main()
{
	cin>>n>>m>>p;
	for(int i=1;i<=n;++i)pos[i] = read();
	int l = 1, r = n;
	int ans = 0;
	while(l<r)
	{
		if(r-l<=3)
		{
			for(int i=l;i<=r;++i)
				if(check(i))
					ans = i;
			break;
		}
		int mid = (l+r)>>1;
		if(check(mid))
			l = mid;
		else r = mid - 1;
	}
	printf("%d\n",ans);
}
