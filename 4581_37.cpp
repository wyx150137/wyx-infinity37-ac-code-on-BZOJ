
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
int maxx[5],maxy[5],minx[5],miny[5];
int x[N],y[N];
int main()
{
	int n;
	scanf("%d",&n);
	memset(minx,0x3f,sizeof(minx));
	memset(miny,0x3f,sizeof(miny));
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		maxx[4] = max(maxx[4],x[i]);
		for(int j = 4;j>1;j--)
			if(maxx[j]>maxx[j-1])swap(maxx[j],maxx[j-1]);
		minx[4] = min(minx[4],x[i]);
		for(int j = 4;j>1;j--)
			if(minx[j]<minx[j-1])swap(minx[j],minx[j-1]);
		maxy[4] = max(maxy[4],y[i]);
		for(int j = 4;j>1;j--)
			if(maxy[j]>maxy[j-1])swap(maxy[j],maxy[j-1]);
		miny[4] = min(miny[4],y[i]);
		for(int j = 4;j>1;j--)
			if(miny[j]<miny[j-1])swap(miny[j],miny[j-1]);
	}
	int ans = (1<<30)-1+(1<<30);
	for(int x1 = 1;x1<=4;x1++)
	for(int x2 = 1;x2<=4;x2++)
		if(minx[x1]<maxx[x2])
		for(int y1 = 1;y1<=4;y1++)
		for(int y2 = 1;y2<=4;y2++)
		if(miny[y1]<maxy[y2])
		{
			int cnt = 0;
			for(int i = 1;i<= n;i++)
				if(x[i]>=minx[x1]&&x[i]<=maxx[x2]&&y[i]>=miny[y1]&&y[i]<=maxy[y2])
					cnt++;
			if(cnt>=n-3)
				ans = min(ans,(maxx[x2]-minx[x1])*(maxy[y2]-miny[y1]));
		}
	printf("%d\n",ans);
	return 0;
}
