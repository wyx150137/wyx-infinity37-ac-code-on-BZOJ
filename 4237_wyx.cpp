
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int inf = 0x7fffffff;
inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct Poi{
	int x,y;
}a[N],stack1[N],stack2[N];

bool cmp1(const Poi &a,const Poi &b){
	return a.x < b.x;
}

bool cmp2(const Poi &a,const Poi &b){
	return a.y > b.y;
}

long long ans = 0;

void solve(int l,int r){
	if(l==r)return;
	register int i,j;
	int top1=0,top2=0;
	int mid = (l+r) >> 1;
	solve(l,mid); 
	solve(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);
	for(i=l,j=mid+1;i<=mid;++i){
		while(a[i].y <= a[j].y && j <= r){
			while(a[j].x < stack2[top2].x) top2--;
			stack2[++top2] = a[j]; j ++;
		}
		while(a[i].x > stack1[top1].x) top1--;
		stack1[++top1] = a[i];
		int L,R,tmp1 = stack1[top1-1].y;
		{
			int l = 1, r = top2;
			while(l<=r){
				int mid = (l+r) >> 1;
				if(stack2[mid].y <= tmp1) r = mid - 1;
				else l = mid + 1;
			}
			L = r+1;
		}
		tmp1 = stack1[top1].y;
		{
			int l = 1, r = top2;
			while(l<=r){
				int mid = (l+r) >> 1;
				if(stack2[mid].y <= tmp1) r = mid - 1;
				else l = mid + 1;
			}
			R = r;
		}
		ans += (long long)(R - L + 1);
	}
}

int main(){ //freopen("09.in","r",stdin);
	int n = read();
	stack1[0].x = inf ,stack1[0].y = inf; stack2[0].x = -1,stack2[0].y = inf;
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].y = read();
	sort(a+1,a+n+1,cmp1);
	solve(1,n);
	cout << ans << endl;
}
