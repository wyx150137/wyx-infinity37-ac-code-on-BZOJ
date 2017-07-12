
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <algorithm>
using namespace std;
typedef double f2;
const int N = 1e6+5;
const f2 eps = 1e-8;
using namespace std;

struct poi {
	f2 x,y;
}q[N],s[N];

poi operator-(const poi &x,const poi &y) {return (poi){x.x-y.x,x.y-y.y};}
f2 operator*(const poi &x,const poi &y) {return x.x*y.y-x.y*y.x;}
f2 slope(const poi &x,const poi &y) {if (x.x==y.x) return -1e60; else return (y.y-x.y)/(y.x-x.x);}
f2 slope(const poi &x) {return -sqrt(x.y/x.x);}
f2 calc(const poi &x,f2 k) {if (k>=0) return 1e20; else return x.x+x.y-x.x*k-x.y/k;}

int n,top;
f2 ans;

bool cmp(const poi &x,const poi &y) {
	return x.x<y.x || (x.x==y.x && x.y>y.y);
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lf%lf",&q[i].x,&q[i].y);
	sort(q+1,q+n+1,cmp);
	int top=1;s[1]=q[1];
	for (int i=2;i<=n;i++) {
		while (top>1 && (q[i]-s[top])*(s[top]-s[top-1])<0) top--;
		s[++top]=q[i];	
	}
	if (top==1) ans=calc(s[1],slope(s[1]));
	else {
		f2 sp,sp1,sp2;
		ans=1e20;
		sp2=slope(s[1],s[2]);sp=slope(s[1]);
		if (sp>=sp2) ans=min(ans,calc(s[1],sp));
		for (int i=2;i<top;i++) {
			sp1=slope(s[i-1],s[i]);sp2=slope(s[i],s[i+1]);sp=slope(s[i]);
			ans=min(ans,calc(s[i],sp1));
			if (sp1>=sp && sp>=sp2) ans=min(ans,calc(s[i],sp));
		}
		sp1=slope(s[top-1],s[top]);sp=slope(s[top]);
		ans=min(ans,calc(s[top],sp1));
		if (sp<=sp1) ans=min(ans,calc(s[top],sp));
	}
	printf("%.4lf\n",ans);
	return 0;
}
