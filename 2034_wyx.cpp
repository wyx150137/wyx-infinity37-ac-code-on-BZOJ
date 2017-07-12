
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;

inline char nc()
{
	static char buf[100000],*p1=buf,*p2=buf;
	if (p1==p2) { p2=(p1=buf)+fread(buf,1,100000,stdin); if (p1==p2) return EOF; }
	return *p1++;
}

inline void read(int &x)
{
	char c=nc(),b=1;
	for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
	for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

const int N=5005;

struct abcd{
	int l,r,val;
	bool operator < (const abcd &B) const{
		return r>B.r;
	}
}A[N],S[N],T[N],tem;
bool cmpv(abcd A,abcd B){ return A.val>B.val; }
bool cmpl(abcd A,abcd B){ return A.l<B.l; }

int n,pnt; ll ans;

int icnt,sx[N];

int boy[N];
bool match(int x,int now,int ed){
	if (now>ed || now>=icnt) return 0;
	int t=boy[now];
	if (!t)
		return boy[now]=x,1;
	if (A[x].r<A[t].r){
		if (match(t,now+1,A[t].r))
			return boy[now]=x,1;
		else
			return 0;
	}
	else
		return match(x,now+1,ed);
}

int main()
{
	read(n);
	for (int i=1;i<=n;i++) read(A[i].l),read(A[i].r),read(A[i].val);
	for(int i=1;i<=n;i++) sx[++icnt]=A[i].l;
	sort(sx+1,sx+icnt+1);
	for(int i=2;i<=icnt;i++) sx[i]=max(sx[i-1]+1,sx[i]);
	icnt=unique(sx+1,sx+icnt+1)-sx-1;
	sx[++icnt]=1<<30;
	for(int i=1;i<=n;i++){
		A[i].l=lower_bound(sx+1,sx+icnt+1,A[i].l)-sx;
		A[i].r=upper_bound(sx+1,sx+icnt+1,A[i].r)-sx-1;
	}
	sort(A+1,A+n+1,cmpv);
	for(int i=1;i<=n;i++)
		if (match(i,A[i].l,A[i].r))
			ans+=A[i].val;
	printf("%lld\n",ans);
	return 0;
}
