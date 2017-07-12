
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
const int LIM = (N<<1)+5;
struct C
{int k,s;}cow[N];
bool cmp(C a,C b)
{return a.s<b.s;}
int pos[(N<<1)+5];
int main()
{	
	int n,x;
	char tmp[3];
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%s",&x,tmp);
		if(tmp[0]=='W')cow[i].k = -1;
		else cow[i].k = 1;
		cow[i].s =x;
	}
	sort(cow+1,cow+n+1,cmp);
	memset(pos,0x3f,sizeof(pos));
	int sum = n,ans = 0;
	pos[sum] = cow[1].s;
	for(int i = 1;i< n;i++)
	{
		sum+=cow[i].k;
		pos[sum] = min(pos[sum],cow[i+1].s);
	}
	for(int i = 2*n;i>=0;i--)
		pos[i] = min(pos[i],pos[i+2]);
	sum = n;
	for(int i = 1;i<= n;i++)
	{
		sum+=cow[i].k;
		ans = max(cow[i].s-pos[sum],ans);
	}
	printf("%d\n",ans);
	return 0;
}
