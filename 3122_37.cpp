
#include <stdio.h>
#include <map>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
ll x,y;
ll ex_gcd(ll a,ll b)
{
	if(b==0)
	{
		x = 1,y = 0;
		return a;
	}
	ll ans = ex_gcd(b,a%b);
	ll c = x;
	x = y;
	y = c-a/b*y;
	return ans;
}
ll getenv(ll X,ll c)
{
	ex_gcd(X,c);
	ll tmp = x;
	tmp = (tmp%c+c)%c;
	return tmp;
}
map<int,int>Pow;
int powA[100005];
ll A,B,C;
ll work()
{
	Pow.clear();
	//scanf("%lld%lld%lld",&A,&C,&B);
	if(A%C==0&&B!=0)return -1;
	ll D = 1;
	ll tmp = 1;
	for(int i = 0;i<=50;i++)
	{
		if((tmp%=C)==B)return i;
		tmp = tmp*A%C;
	}
	ll k = 0,gcd = ex_gcd(A,C);
	while(gcd!=1)
	{
		k++;
		if(B%gcd!=0)return -1;
		B/=gcd,C/=gcd,D*=A/gcd;
		D%=C;
		gcd = ex_gcd(A,C);
	}
	B*=getenv(D,C),B%=C;
	int m = ceil(sqrt(C)+1e-5);
	powA[0] = 1;Pow[1] = 0;
	for(int i = 1;i<= m;i++)
	{
		powA[i] = powA[i-1]*A%C;
		if(powA[i]==B)return i+k;
		Pow[powA[i]] = i;
	}
	D = 1;
	for(int i = 0;i<= m;i++)
	{
		ex_gcd(D,C);
		x = (x*B%C+C)%C;
		if(Pow.find(x)!=Pow.end())
			return (ll)i*m+k+Pow[x];
		D=D*powA[m]%C;
	}
	return -1;
}
ll solve()
{
	ll p,a,b,x1,t,tmp;
	scanf("%lld%lld%lld%lld%lld",&p,&a,&b,&x1,&t);
	if(x1==t)return 1;
	if(!a)return b==t?2:-1;
	if(a==1)
	{
		t+=p-x1,t%=p;
		tmp = ex_gcd(b,p);
		if(t%tmp)return -1;
		b/=tmp,p/=tmp,t/=tmp;
		ex_gcd(b,p);
		tmp = (x*t%p+p)%p;
		return tmp+1;
	}
	ll Y = (a*x1-x1+b)%p;
	ll Z = (a*t-t+b)%p;
	tmp = ex_gcd(Y,p);
	if(Z%tmp)return -1;
	Z/=tmp,Y/=tmp,p/=tmp;
	C = p;
	B = Z*getenv(Y,C)%p;
	A = a;
	tmp = work();
	if(tmp==-1)return -1;
	else return tmp+1;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
		printf("%lld\n",solve());
	return 0;
}
