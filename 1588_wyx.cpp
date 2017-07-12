
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <time.h>
const int inf = 1000000000;
#define N 40000+5
using namespace std;
int fa[N],size[N],num[N],ch[N][2];
int cnt,rt;
int ans1,ans2;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y];
    int l = (ch[y][1]==x), r = l^1;
    if(y==k)k=x;
    else ch[z][ch[z][1]==y]=x;
    fa[ch[x][r]]=y;fa[y]=x;fa[x]=z;
    ch[y][l]=ch[x][r];ch[x][r]=y;
}
void splay(int x,int &k)
{
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {
            if((ch[y][0]==x) ^ (ch[z][0]==y))rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
void insert(int &k,int x,int last)
{
	if(!k){k=++cnt;num[k]=x,fa[k]=last;splay(k,rt);return;}
	if(x<num[k])insert(ch[k][0],x,k);
	else insert(ch[k][1],x,k);
}
void ask_before(int k,int x)
{
	if(!k)return;
	if(num[k]<=x){ans1=num[k];ask_before(ch[k][1],x);}
	else ask_before(ch[k][0],x);
}
void ask_last(int k,int x)
{
	if(!k)return;
	if(num[k]>=x){ans2=num[k];ask_last(ch[k][0],x);}
	else ask_last(ch[k][1],x);
}
int main()
{
	int n=read();
	int ans = 0;
	for(int i=1;i<=n;++i)
	{
		int x=read();
		if(rt)
			splay(rand()%rt+1,rt);
		ans1=-inf,ans2=inf;
		ask_before(rt,x);
		ask_last(rt,x);
		if(i!=1)
			ans += min(x-ans1,ans2-x);
		else ans +=x;
		insert(rt,x,0);
	}
	cout<<ans<<endl;
}
