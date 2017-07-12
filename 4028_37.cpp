
#include <stdio.h>
#include <math.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 100005;
const int B = 5005;
int g[N],x[N],a[N];
int pos[N],lb[N],rb[N];
int gcd(int a,int b)
{
	if(a==-1)return b;
	if(b==0)return a;
	return gcd(b,a%b);
}
map<ll,int>s[B];
void debug(int b)
{
	printf("Bolck No #%d\n",b);
	map<ll,int>::iterator it;
	for(it = s[b].begin();it!=s[b].end();it++)
		printf("%lld %d\n",it->first,it->second);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	int block = sqrt(n);
	for(int i = 1;i<= n;i++)
		pos[i] = (i-1)/block+1;
	int tot = pos[n];
	for(int i = 1;i<= tot;i++)
		lb[i] = (i-1)*block+1,rb[i] = i*block;
	rb[tot] = n;
	for(int i = 1;i<= tot;i++)
	{
		g[lb[i]] = a[lb[i]],x[lb[i]] = a[lb[i]];
		s[i][x[lb[i]]] = lb[i];
		for(int j = lb[i]+1;j<= rb[i];j++)
		{
			g[j] = gcd(g[j-1],a[j]),x[j] = x[j-1]^a[j];
			if(s[i].find(x[j])==s[i].end())s[i][x[j]] = j;
		}
		//debug(i);
	}
	int q,id,nv;
	ll p;
	scanf("%d",&q);
	while(q--)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[0]=='M')
		{
			scanf("%d%d",&id,&nv);
			id++;
			int Pos = pos[id];
			for(int i = id;i<= rb[Pos];i++)
				if(s[Pos][x[i]]==i)s[Pos].erase(x[i]);
			if(id==lb[Pos])g[id] = x[id] = nv;
			else g[id] = gcd(g[id-1],nv),x[id] = x[id-1]^nv;
			if(s[Pos].find(x[id])==s[Pos].end())s[Pos][x[id]] = id;
			for(int i = id+1;i<= rb[Pos];i++)
			{
				g[i] = gcd(g[i-1],a[i]),x[i] = x[i-1]^a[i];
				if(s[Pos].find(x[i])==s[Pos].end())s[Pos][x[i]] = i;
			}
			a[id] = nv;
			//debug(Pos);
		}
		else
		{
			scanf("%lld",&p);
			int lastgcd = -1;
			int lastxor = 0;
			bool flag = false;
			for(int i = 1;i<= tot&&!flag;i++)
			{
				int tmp_gcd = gcd(lastgcd,g[rb[i]]);
				if(tmp_gcd==lastgcd)
				{
					ll goal = (p/lastgcd)^lastxor;
					if(p%lastgcd)goal = -1;
					if(s[i].find(goal)!=s[i].end())
					{
						printf("%d\n",s[i][goal]-1);
						flag = true;
					}
				}else
				{
					for(int j = lb[i];j<= rb[i];j++)
					{
						ll tg = gcd(lastgcd,g[j]);
						ll tx = lastxor^x[j];
						if(tg*tx==p)
						{
							printf("%d\n",j-1);
							flag = true;break;
						}
					}
				}
				lastgcd = gcd(lastgcd,g[rb[i]]);
				lastxor = lastxor^x[rb[i]];
			}
			if(!flag)printf("no\n");
		}
	}
	return 0;
}
/*
10

1353600 5821200 10752000 1670400 3729600 6844320 12544000 117600 59400 640

10

MODIFY 7 20321280

QUERY 162343680

QUERY 1832232960000

MODIFY 0 92160

QUERY 1234567

QUERY 3989856000

QUERY 833018560

MODIFY 3 8600

MODIFY 5 5306112

QUERY 148900352

6

0

no

2

8

8
*/
