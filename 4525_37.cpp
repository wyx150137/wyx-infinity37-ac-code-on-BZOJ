
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
int pos[N],n,k;
bool check(int x)
{
	int last = 1,ans = 0;
	for(int i= 1;i<= n;i++)
		if(pos[i]-pos[last]>x)
			ans++,last = i;
	ans++;
	return ans<=k;
}
int main()
{		
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&pos[i]);
	sort(pos+1,pos+n+1);
	int l = 0,r = pos[n]+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(2*mid))r = mid;
		else l = mid+1;
	}
	printf("%d\n",l);
	return 0;
}
