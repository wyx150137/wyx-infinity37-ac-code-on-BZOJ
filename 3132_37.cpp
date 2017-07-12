
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2049;
struct T
{
	int a[N][N];
	T()
	{memset(a,0,sizeof(a));}
	void update(int x,int y,int c)
	{
		for(int i = x;i<N;i+=i&(-i))
			for(int j = y;j<N;j+=j&(-j))
				a[i][j]+=c;
	}
	int getans(int x,int y)
	{
		int ans = 0;
		for(int i = x;i>0;i-=i&(-i))
			for(int j = y;j>0;j-=j&(-j))
				ans+=a[i][j];
		return ans;
	}
}A,B,C,D;
void update(int x1,int x2,int y1,int y2,int d)
{
	A.update(x1,y1,d),A.update(x2+1,y1,-d);
	A.update(x1,y2+1,-d),A.update(x2+1,y2+1,d);

	B.update(x1,y1,d*x1),B.update(x2+1,y1,-d*(x2+1));
	B.update(x1,y2+1,-d*x1),B.update(x2+1,y2+1,d*(x2+1));

	C.update(x1,y1,d*y1),C.update(x2+1,y1,-d*y1);
	C.update(x1,y2+1,-d*(y2+1)),C.update(x2+1,y2+1,d*(y2+1));

	D.update(x1,y1,d*x1*y1),D.update(x2+1,y1,-d*(x2+1)*y1);
	D.update(x1,y2+1,-d*x1*(y2+1)),D.update(x2+1,y2+1,d*(x2+1)*(y2+1));
}
int getb(int x,int y)
{
	return (x+1)*(y+1)*A.getans(x,y)-(x+1)*C.getans(x,y)-(y+1)*B.getans(x,y)+D.getans(x,y);
}
int main()
{
	int n,m,a,b,c,d,z;
	char ju[3];
	scanf("%s",ju);
	scanf("%d%d",&n,&m);
	while(scanf("%s",ju)!=EOF)
	{
		if(ju[0]=='k')
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			int ans = 0;
			ans += getb(c,d)-getb(a-1,d)-getb(c,b-1)+getb(a-1,b-1);
			printf("%d\n",ans);
		}
		else
		{
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&z);
			update(a,c,b,d,z);
		}
	}
	return 0;
}
