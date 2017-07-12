
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 20005;
const int M = 100005;
int fa[N];
struct E{int x,y;}e1[M],e2[M];
int cnt1,cnt2;
int ansx[M],ansy[M],ansc[M];
int ans_cnt,n,m,k;
int getfa(int x)
{
	if(fa[x]==x||!fa[x])return fa[x] = x;
	else return fa[x] = getfa(fa[x]);
}
void uni(int x,int y)
{
	int fx = getfa(x),fy = getfa(y);
	if(fx!=fy)
		fa[fx] = fy;
}
bool Find_Must()
{
	int block = n;
	for(int i = 1;i<= cnt2;i++)
	{
		int fx = getfa(e2[i].x),fy = getfa(e2[i].y);
		if(fx==fy)continue;
		block--;
		uni(e2[i].x,e2[i].y);
		if(block==1)break;
	}
	for(int i = 1;i<= cnt1;i++)
	{
		int fx = getfa(e1[i].x),fy = getfa(e1[i].y);
		if(fx==fy)continue;
		block--;
		ans_cnt++;
		ansx[ans_cnt] = e1[i].x;ansy[ans_cnt] = e1[i].y;
		ansc[ans_cnt] = 0;
		uni(e1[i].x,e1[i].y);
		if(block==1)break;
	}
	if(ans_cnt>k)return false;
	else return true;
}
bool build()
{
	int block = n,tmp = 0;
	for(int i = 1;i<= ans_cnt;i++)
	{
		uni(ansx[i],ansy[i]);
		block--;
		tmp++;
	}
	for(int i = 1;i<= cnt1;i++)
	{
		int fx = getfa(e1[i].x),fy = getfa(e1[i].y);
		if(fx==fy)continue;
		block--;
		tmp++;
		ans_cnt++;
		ansx[ans_cnt] = e1[i].x;ansy[ans_cnt] = e1[i].y;
		ansc[ans_cnt] = 0;
		uni(e1[i].x,e1[i].y);
		if(block==1||tmp==k)break;
	}
	for(int i = 1;i<= cnt2;i++)
	{
		int fx = getfa(e2[i].x),fy = getfa(e2[i].y);
		if(fx==fy)continue;
		block--;
		ans_cnt++;
		ansx[ans_cnt] = e2[i].x;ansy[ans_cnt] = e2[i].y;
		ansc[ans_cnt] = 1;
		uni(e2[i].x,e2[i].y);
		if(block==1)break;
	}
	if(tmp!=k)return false;
	else return true;
}
int main()
{
	int x,y,c;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&x,&y,&c);
		if(c==0){e1[++cnt1].x = x;e1[cnt1].y = y;}
		else {e2[++cnt2].x = x;e2[cnt2].y = y;}
	}
	if(!Find_Must())printf("no solution\n");
	memset(fa,0,sizeof(fa));
	if(!build())printf("no solution\n");
	else
	{
		for(int i = 1;i<= ans_cnt;i++)
			printf("%d %d %d\n",ansx[i],ansy[i],ansc[i]);
	}
	return 0;
}
