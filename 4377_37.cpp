
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int M = 1e6+5;
int n,a,b,p,m,cnt;
struct S
{int l,r;}seg[M<<2];
char s[M];
void add(int l,int r)
{
	if(l<=r){seg[++cnt].l = l;seg[cnt].r = r;}
	else 
	{
		seg[++cnt].l = l;seg[cnt].r = n-1;
		seg[++cnt].l = 0;seg[cnt].r = r;
	}
}
bool cmp(S a,S b)
{
	return a.l<b.l;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&a,&b,&p,&m);
	scanf("%s",s);
	int now = 0;
	for(int i = 0;i<m;i++,now = (now+a)%n)
	{
		if(s[i]=='0')add((p-now+n)%n,(n-1-now+n)%n);
		else add((n-now)%n,(p-1-now+n)%n);
	}
	for(int i=1,c=(b-a+n)%n;i<m;i++,c=(c-a+n)%n)
        add(c,c);
    sort(seg+1,seg+cnt+1,cmp);
    int end = -1,ans = 0;
    for(int i = 1;i<= cnt;i++)
    {
    	if(seg[i].l>end)
    	{
    		ans+=seg[i].l-end-1;
    		end = seg[i].r;
    	}
    	end = max(seg[i].r,end);
    }
    printf("%d\n",ans+n-1-end);
	return 0;
}
