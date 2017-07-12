
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
const f2 eps = 1e-6;
const int N = 100000+5;

struct poi {
	f2 x,y;
	poi () {}
	poi (f2 _a,f2 _b) :x(_a),y(_b){}
	poi operator + (const poi &z) const {return poi(x+z.x,y+z.y);} 
	poi operator - (const poi &z) const {return poi(x-z.x,y-z.y);}
	poi operator * (const f2  &z) const {return poi(x*z,y*z);}
	f2  operator * (const poi &z) const {return x*z.x+y*z.y;}
	f2  operator ^ (const poi &z) const {return x*z.y-y*z.x;}
} a[N];

struct line {
	poi tmp1,tmp2;
	line () {}
	line (poi a,poi b) :tmp1(a),tmp2(b){}
};

struct data{
	poi tmp1; f2 r;
	data () {}
	data (poi a,f2 b) : tmp1(a),r(b){} 
}ans;

inline f2 dis(const poi &a,const poi &b) {return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
inline bool in(const poi &a,const data &b) { return dis(a,b.tmp1)<=b.r;}
poi rotate(poi a) {return poi(-a.y,a.x);} 

poi get(const line &a,const line &b){
	poi tt = a.tmp1 - b.tmp1;
	f2 tmp = (b.tmp2^tt)/(a.tmp2 ^ b.tmp2);
	return a.tmp1 + a.tmp2*tmp;
}

int main() {
	int n; cin >> n; srand(150137);
	for(int i=1;i<=n;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
    random_shuffle(a+1,a+n+1);
	for(int i=1;i<=n;++i) {
		if(!in(a[i],ans)) {
			ans.tmp1 = a[i];
			for(int j=1;j<i;++j) {
				if(!in(a[j],ans)) {
					ans.tmp1 = (a[i]+a[j])*0.5;
					ans.r = dis(a[i],a[j])*0.5;
					for(int k=1;k<j;++k) {
						if(!in(a[k],ans)) {
							line tmp1 = line((a[i]+a[j])*0.5,rotate(a[i]-a[j]));
							line tmp2 = line((a[i]+a[k])*0.5,rotate(a[i]-a[k]));
							ans.tmp1 = get(tmp1,tmp2); ans.r = dis(ans.tmp1,a[i]);
						}
					}
				}

			}
		}
	}
	printf("%.6lf\n%.6lf %.6lf\n",ans.r,ans.tmp1.x,ans.tmp1.y);
}
