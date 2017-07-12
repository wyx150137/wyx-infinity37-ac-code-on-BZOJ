
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		x1--;
		x2--;
		int last = 0,ans = -1;
		for(int i = 1;i<= y1&&i<=y2;i = last+1)
		{
			last = min(y1/(y1/i),y2/(y2/i));
			if(y1/last>x1/last&&y2/last>x2/last)
				ans = max(ans,last);
		}
		printf("%d\n",ans);
	}
	return 0;
}
