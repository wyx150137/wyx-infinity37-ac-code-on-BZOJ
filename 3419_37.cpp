
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 500005;
LL a[N];
bool cmp(LL a,LL b)
{
	return a>b;
}
int main()
{
	//freopen("tak.in","r",stdin);
	//freopen("tak.out","w",stdout);
	int n;
	LL m,d;
	scanf("%lld%lld%d",&m,&d,&n);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1,cmp);
	if(a[1]>=m+d){printf("1\n");return 0;}
	int sec = 0;
	for(int i = 1;i<= n;i++)
		if(a[i]>=m-d)sec = i;
	if(sec==0){printf("0\n");return 0;}
	int ans = 1;
	LL back = 0;
	for(int i=1;i<=n;i++)
	{
		if(i==sec) continue;
		if(back>=d||m-back+d-back<=a[sec]) break;
		if(a[i]<=d-back) {puts("0");return 0;}
		ans++;
		back+=a[i]-(d-back);
		if(back>=m) {ans--;break;}
	}
	if(m-back+d-back>a[sec]) puts("0");
	else printf("%d\n",ans);
	return 0;
}
