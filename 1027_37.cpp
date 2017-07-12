
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const double eps = 1e-7;
const int N = 505;
const int INF = 0x3f3f3f3f;
struct Point
{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	Point operator+(const Point &a)const
	{
		return Point(x+a.x,y+a.y);
	}
	Point operator-(const Point &a)const
	{
		return Point(x-a.x,y-a.y);
	}
	double operator*(const Point &a)const
	{
		return x*a.y-y*a.x;
	}
	double operator^(const Point &a)const
	{
		return x*a.x+y*a.y;
	}
}mtr[N],req[N];
struct Line
{
	Point p,v;
	Line(){}
	Line(const Point &a,const Point &b):p(a),v(b){}
};
int map[N][N];
void display()
{
	for(int i = 1;i<= 10;i++)
	{
		for(int j = 1;j<= 10;j++)
			if(map[i][j]==INF)printf("0");
			else printf("1");
		printf("\n");
	}
}
int main()
{
	memset(map,0x3f,sizeof(map));
	int n,m;
	double c;
	scanf("%d%d",&m,&n);
	for(int i = 1;i<= m;i++)
		scanf("%lf%lf%lf",&mtr[i].x,&mtr[i].y,&c);
	for(int i = 1;i<= n;i++)
		scanf("%lf%lf%lf",&req[i].x,&req[i].y,&c);
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<=m;j++)
		{
			bool flag=true;
			for(int k = 1;k<= n;k++)
			{
				double cro = (mtr[i]-req[k])*(mtr[j]-req[k]);
				if(cro>eps){flag = false;break;}
				if(fabs(cro)<eps&&((mtr[i]-req[k])^(mtr[j]-req[k]))>eps)
					{flag = false;break;}
			}
			if(flag)map[i][j] = 1;
		}
	for(int k = 1;k<= m;k++)
		for(int i = 1;i<= m;i++)
			for(int j = 1;j<= m;j++)
				map[i][j] = min(map[i][j],map[i][k]+map[k][j]);
	int ans = INF;
	for(int i = 1;i<= m;i++)
		ans = min(ans,map[i][i]);
	if(ans!=INF)printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
