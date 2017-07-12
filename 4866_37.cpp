
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int S = 1<<26;
const int N = 60005;
unsigned short cnt[S+5];
char s[N];
int ans[N],num[N];
int pos[N],pre[N],lb[N],rb[N];
inline char nc(){
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x){
	char c=nc(),b=1;
	for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
	for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}
inline void read(char *s){
	char c=nc(); int len=0;
	for (;!(c>='a' && c<='z');c=nc());
	for (;c>='a' && c<='z';s[++len]=c,c=nc());
}
inline void write(ll x){
	if (x>=10) write(x/10); putchar(x%10+'0');
}

inline void add(int x)
{
	cnt[x]++;
	for(register int i = 0;i<26;i++)cnt[x^(1<<i)]++;
}
inline void del(int x)
{
	cnt[x]--;
	for(register int i = 0;i<26;i++)cnt[x^(1<<i)]--;
}
inline int getans(int x){return cnt[x];}
struct Q
{
	int l,r,id;
	Q(int _l=0,int _r=0,int _id=0):l(_l),r(_r),id(_id){}
	bool operator <(const Q &s)const
	{
		return pos[l]==pos[s.l]?r<s.r:pos[l]<pos[s.l];
	}
}ask[N];
int block;
int main()
{
	//freopen("4866.in","r",stdin);
	//freopen("4866.out","w",stdout);
	int n,m,i,j,k;
	read(n),read(m);
	block = min((int)sqrt(n*28),n);
	read(s);
	for(i = 1;i<= n;i++)pre[i] = pre[i-1]^(1<<(s[i]-'a'));
	int tot = 0;
	for(i = 1;i<= n;i++)
		pos[i] = (i-1)/block+1;
	tot = pos[n];
	for(i = 1;i<= tot;i++)
		lb[i] = (i-1)*block+1,rb[i] = i*block;
	rb[tot] = n;
	for(i =1;i<= tot;i++)
	{
		add(pre[rb[i]]);
		for(j = rb[i]-1;j>=lb[i]-1;j--)
		{
			num[j+1] = num[j+2]+getans(pre[j]);
			add(pre[j]);
		}
		for(j = rb[i];j>=lb[i]-1;j--)
			del(pre[j]);
	}
	int L,R,Cnt = 0;
	for(i = 1;i<= m;i++)
	{
		read(L),read(R);
		if(pos[L]==pos[R])
		{
			add(pre[L-1]);
			for(j = L;j<= R;j++)
				ans[i]+=getans(pre[j]),add(pre[j]);
			for(j = L-1;j<= R;j++)
				del(pre[j]);
		}else
			ask[++Cnt] = Q(L,R,i);
	}
	sort(ask+1,ask+Cnt+1);
	int last = 0,pnt = 0;
	for(i = 1;i<tot;i++)
	{
		last = pnt;
		while(pnt+1<=Cnt&&pos[ask[pnt+1].l]==i)pnt++;
		int r = lb[i+1]-1;
		ll now = 0;
		add(pre[r]);
		for(j = last+1;j<= pnt;j++)
		{
			while(r<ask[j].r)now+=getans(pre[++r]),add(pre[r]);
			ans[ask[j].id] = now+num[ask[j].l];
			del(pre[lb[i+1]-1]);
			for(k = ask[j].l-1;k< rb[i];k++)
				ans[ask[j].id]+=getans(pre[k]);
			add(pre[lb[i+1]-1]);
		}
		for(j = lb[i+1]-1;j<= r;j++)del(pre[j]);
	}	
	for(i = 1;i<= m;i++)write(ans[i]),putchar('\n');
	return 0;
}
