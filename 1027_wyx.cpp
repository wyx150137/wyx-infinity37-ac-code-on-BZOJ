
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 510
#define INF 0x3f3f3f3f
#define EPS 1e-7
using namespace std;

struct point{
	double x,y;
	point operator - (const point z) {
		point re;
		re.x=x-z.x;
		re.y=y-z.y;
		return re;
	}
	double operator * (const point z){return x*z.y-y*z.x;}
	double operator ^ (const point z){return x*z.x+y*z.y;}
}a[M],b[M];
int m,n, map[M][M],f[M][M], ans=INF;

void Floyd(){
	int i,j,k;
	memcpy(f,map,sizeof f);
	for(k=1;k<=m;k++)
		for(i=1;i<=m;i++)
			if(f[i][k]<INF)
				for(j=1;j<=m;j++)
					f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(i=1;i<=m;i++) ans=min(ans,f[i][i]);
}

int main(){
	int i,j,k;
	memset(map,0x3f,sizeof map);
	cin>>m>>n;
	for(i=1;i<=m;i++) scanf("%lf%lf%*lf",&a[i].x,&a[i].y);
	for(i=1;i<=n;i++) scanf("%lf%lf%*lf",&b[i].x,&b[i].y);
	for(i=1;i<=m;i++)
		for(j=1;j<=m;j++) {
			for(k=1;k<=n;k++) {
				double tmp=(a[i]-b[k])*(a[j]-b[k]);
				if(tmp>EPS||(fabs(tmp)<EPS && (a[i]-b[k]^a[j]-b[k])>EPS)) break;
			}
			if(k==n+1) map[i][j]=1;
		}
	Floyd();
	if(ans==INF) ans=-1;
	cout<<ans<<endl;
}
