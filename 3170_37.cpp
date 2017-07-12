
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
struct P
{
	ll x,y;
	P(){}
	P(ll x,ll y):x(x+y),y(x-y){}

}p[N];
int n;
ll X[N],Y[N],ans = 1e18;
ll sumx[N],sumy[N];
int main()
{
	int x,y;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		p[i]=P(x,y);
		X[i] = p[i].x,Y[i] = p[i].y;
	}
	sort(X+1,X+n+1);
	sort(Y+1,Y+n+1);
	for(int i = 1;i<= n;i++)
	{
		sumx[i] = sumx[i-1]+X[i];
		sumy[i] = sumy[i-1]+Y[i];
	}
	ll tmp=0;
	int pos;
	for(int i = 1;i<= n;i++)
	{
		tmp = 0;
		pos = lower_bound(X+1,X+n+1,p[i].x)-X;
		tmp+=(p[i].x*pos-sumx[pos])+((sumx[n]-sumx[pos])-p[i].x*(n-pos));
		pos = lower_bound(Y+1,Y+n+1,p[i].y)-Y;
		tmp+=(p[i].y*pos-sumy[pos])+((sumy[n]-sumy[pos])-p[i].y*(n-pos));
		ans = min(ans,tmp);
	}
	printf("%lld\n",ans>>1);
	return 0;
}
