
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct Data{int x,y,id;}a[N],b[N];
bool cmp1(const Data &m,const Data &n)
{
	return m.x<n.x;
}
bool cmp2(const Data &m,const Data &n)
{
	return m.y>n.y;
}
int main()
{
	int cnt1,cnt2;
	cnt1 = cnt2 = 0;
	int n,x,y;
	long long z;
	scanf("%d%lld",&n,&z);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		if(y>=x){a[++cnt1].x = x,a[cnt1].y = y,a[cnt1].id = i;}
		else{b[++cnt2].x = x,b[cnt2].y = y,b[cnt2].id = i;}
	}
	sort(a+1,a+cnt1+1,cmp1);
	sort(b+1,b+cnt2+1,cmp2);
	for(int i = 1;i<= cnt1;i++)
	{
		if(z-a[i].x<=0){printf("NIE\n");return 0;}
		z+=a[i].y-a[i].x;
	}
	for(int i = 1;i<= cnt2;i++)
	{
		if(z-b[i].x<=0){printf("NIE\n");return 0;}
		z+=b[i].y-b[i].x;
	}
	printf("TAK\n");
	for(int i = 1;i<= cnt1;i++)
		printf("%d ",a[i].id);
	for(int i = 1;i<= cnt2;i++)
		printf("%d ",b[i].id);
	return 0;
}
