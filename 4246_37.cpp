
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define fir first
#define sec second
typedef long long ll;
const double eps = 1e-10;
const int N = 3005;
const double PI = 3.1415926535897323;
int dcmp(double x)
{
	if(fabs(x)<eps)return 0;
	if(x>0)return 1;else return -1;
}
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	friend Point operator -(const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend double arctan2(const Point &p)
	{
		double ang = atan2(p.y,p.x);
		if(ang<=0)return ang+PI;
		else return ang;
	}
}O;
pair<Point,int>point[N],stack[N];
int top;
ll ans;
void calc(int c)
{
	static pair<double,int>b[N];
	bool v[N];
	static pair<Point,int>_stack[N];
	int cnt[2][3]={};
	for(int i = 1;i<= top;i++)
		b[i] = make_pair(arctan2(stack[i].fir-O),i);
	sort(b+1,b+top+1);
	for(int i = 1;i<= top;i++)
		_stack[i]=stack[b[i].sec];
	memcpy(stack+1,_stack+1,sizeof(stack[0])*top);
	for(int i = 1;i<= top;i++)
	{
		if(stack[i].fir.y<O.y||stack[i].fir.y==O.y&&stack[i].fir.x>O.x)
			cnt[v[i]=false][stack[i].sec]++;
		else 
			cnt[v[i]=true][stack[i].sec]++;
	}
	int cnt0,cnt1;
	for(int i = 1;i<= top;i++)
	{
		cnt[v[i]][stack[i].sec]--;
		cnt0 = (c==0?1:cnt[0][0])*(c==1?1:cnt[0][1])*(c==2?1:cnt[0][2]);
		int C = stack[i].sec;
		cnt1 = (C==0?1:cnt[1][0])*(C==1?1:cnt[1][1])*(C==2?1:cnt[1][2]);
		//cnt0/=cnt[0][c],cnt1/=cnt[1][stack[i].sec];
		ans+=(ll)cnt0*cnt1;
		cnt0 = (c==0?1:cnt[1][0])*(c==1?1:cnt[1][1])*(c==2?1:cnt[1][2]);
		cnt1 = (C==0?1:cnt[0][0])*(C==1?1:cnt[0][1])*(C==2?1:cnt[0][2]);
		//cnt0/=cnt[1][c],cnt1/=cnt[0][stack[i].sec];
		ans+=(ll)cnt0*cnt1;
		cnt[v[i]^1][stack[i].sec]++;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d%d",&point[i].fir.x,&point[i].fir.y,&point[i].sec);
	for(int i = 1;i<= n;i++)
	{
		top = 0;
		for(int j = 1;j<= n;j++)
			if(i!=j)
				stack[++top]=point[j];
		O = point[i].fir;
		calc(point[i].sec);
	}
	printf("%lld\n",ans>>2);
	return 0;
}
