
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
int n,m,ans;
struct stuff
{int l,r;}s[N];
inline bool cmp(const stuff &a,const stuff &b){return a.l<b.l;}
struct pro
{
	int x;
	bool operator <(const pro &a)const{return x>a.x;}
};
priority_queue<pro>heap;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&s[i].l,&s[i].r),s[i].r+=s[i].l;
	sort(s+1,s+n+1,cmp);
	heap.push((pro){s[1].r+m});
	for(int i = 2;i<= n;i++)
	{
		while(!heap.empty()&&heap.top().x<s[i].l)heap.pop();
		int t = heap.top().x;
		if(t-m<=s[i].l&&s[i].l<=t)ans++,heap.pop();
		heap.push((pro){s[i].r+m});
	}
	printf("%d\n",ans);
	return 0;
}
