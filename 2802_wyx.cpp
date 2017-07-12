
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;

const int N = 500000+5;

using namespace std;

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}
 
LL a[N];

namespace Heap
{
	int h[N],pos[N],tot;
	
	void up(int x)
	{
		if(x==1)return;
		while(h[x] > h[x>>1])
		{
			if(x==1)break;
			swap(h[x],h[x>>1]);
			swap(pos[x],pos[x>>1]);
			x>>=1;
		}
	}
	
	void push(int x,int i)
	{
		h[++tot] = x;
		pos[tot] = i;
		up(tot);
	}
	
	int top(){
		return h[1];
	}
	
	int pop()
	{
		swap(h[1],h[tot]);
		swap(pos[1],pos[tot--]);
		int i = 1;
		
		while((h[i] < h[i<<1]&&(i<<1)<=tot)||((h[i] < h[i<<1|1])&&(i<<1|1)<=tot))
		{
			if((i<<1|1) <= tot)
			{
				int tmp = h[i<<1] > h[i<<1|1] ? i<<1 : i<<1|1;
				swap(h[i],h[tmp]);swap(pos[i],pos[tmp]);
				i = tmp;
			}
			else
			{
				swap(h[i],h[i<<1]);
				swap(pos[i],pos[i<<1]);
				i <<= 1;
			}
		}
		return pos[tot+1];
	}
	
	bool empty()
	{
		return tot == 0;
	}
}

using namespace Heap;

int ans[N];

int main()
{
	int n = read(),tmp;
	register int i= 0;
	for(i=1;i<=n;++i)a[i] = read();
	for(i=1;i<=n;++i){
		tmp = read();
		a[i] += a[i-1];
		if(a[i] >= tmp){
			a[i] -= tmp;
			push(tmp,++ans[0]);
			ans[ans[0]] = i;
		}	
		else if(!empty())
		{
			int tt = top();
			if(a[i]+tt-tmp>=0 && tt > tmp){
				int tt_pos = pop();
				a[i]=a[i]+tt-tmp;
				ans[tt_pos] = i; 
				push(tmp,tt_pos);
			}
		}
	}
	cout << ans[0] << endl;
	int tt = ans[0];
	sort(ans+1,ans+tt+1);
	for(int i=1;i<ans[0];++i)
		printf("%d ",ans[i]);
	cout << ans[ans[0]] << endl;
}
