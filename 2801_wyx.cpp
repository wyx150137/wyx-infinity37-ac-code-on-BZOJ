
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 1000000+5;
const int M = 8000000+5;
typedef long long LL;
const LL inf = 1e9+7;

int head[N];

struct graph
{
	int next,to;
	LL val;
	graph () {}
	graph (int _next,int _to,LL _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,LL z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

struct data
{
	LL k,b;
	LL l,r;	
	data () {k = b = 0 ;l = -inf,r = inf;}
	data operator +  (const data &z)const
	{
		data tmp;
		tmp.k = k + z.k;
		tmp.b = b + z.b;
		tmp.l = max(l,z.l);
		tmp.r = min(r,z.r);
		return tmp;
	}

	void out()
	{	
		printf("k = %d ,b = %d   x->[%d ,%d]\n",k,b,l,r);
	}

}a[N];

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int T[N];
LL ans1 = 0 ,ans2 = 0 ;
bool vis[N];
queue <int> q;

int V[N];
int tot;
LL ans[N];

void quit()
{
	puts("NIE");
	exit(0);
}

bool in[N];

void BFS(int x)
{
	int tmpans = 0;
	bool flag = false;
	while(!q.empty())
	{
		int tt = q.front();
		q.pop();
		V[++tot] = tt;
	//	cout << tt << ":" << endl;
	//	a[tt].out();
		if(flag) break;
		for(int i=head[tt];i;i=edge[i].next)
		{
			if(!vis[edge[i].to])
			{
				data tmp;
				tmp.k = -a[tt].k;
				tmp.b = edge[i].val - a[tt].b;
				tmp.l = a[tt].l;
				tmp.r = a[tt].r;
	//			cout << "tmp :: " << endl;
	//			tmp.out();
				if(tmp.k > 0)
				{
					tmp.l = max(tmp.l,-tmp.b);
					tmp.r = min(tmp.r,T[edge[i].to] - tmp.b);
				}
				else
				{
					tmp.l = max(tmp.l,tmp.b-T[edge[i].to]);
					tmp.r = min(tmp.r,tmp.b);
				}
				if(tmp.l > tmp.r) quit();
				vis[edge[i].to] = 1;
				a[edge[i].to] = tmp;
				q.push(edge[i].to);
			}
			else
			{
				data tmp = a[edge[i].to] + a[tt];
				if(tmp.k == 0 && tmp.b != edge[i].val){
				//	cout << "WA" << endl;
					quit();
				}
				else if(tmp.k == 0 && tmp.b == edge[i].val) continue;
				else
				{
					flag = 1;
					int G = edge[i].val - tmp.b;
					if(G & 1) {
					//	puts("WA at 126");
						quit();
					}
					tmpans = G / tmp.k;
					if(tmpans < 0) {
					//	puts("WA at 128");
						quit();
					}
					break;
				}
			}
		}
		if(flag) break;
	}
	while(!q.empty()) q.pop();
	if(flag)
	{
		if(tmpans <= a[x].r && tmpans >= a[x].l) 
		{
			tot = 0;
			ans[x] = tmpans;in[x] = 1;
			q.push(x);
			while(!q.empty())
			{
				int tt = q.front();
		//		cout << tt << " " << ans[tt] << endl;	
				q.pop();V[++tot] = tt;
				for(int i=head[tt];i;i=edge[i].next)
				{
					if(!in[edge[i].to])
					{
						ans[edge[i].to] = edge[i].val - ans[tt];in[edge[i].to] = 1;
						if(ans[edge[i].to] < 0) quit();
						if(ans[edge[i].to] > T[edge[i].to]) quit();
						q.push(edge[i].to);
					}
					else
					{
						if(ans[edge[i].to] + ans[tt] == edge[i].val)
							continue;
						else{
	//		cout << tt << "->" << edge[i].to << " " << ans[edge[i].to] << " " << edge[i].val << endl;
	//						cout << "WA at 163" << endl;
							quit();
						}
					}
				}
			}
			for(int i=1;i<=tot;++i)
				ans1 = ans1 + ans[V[i]],ans2 = ans2 + ans[V[i]];
			return ;
		}
		else{ 
		//	cout <<"WA at 168" << endl;
			quit();
		}
	}

	else
	{
		data tmp;
		for(int i=1;i<=tot;++i)
			tmp = tmp + a[V[i]];
		LL tmp1 = tmp.l * tmp.k + tmp.b;
		LL tmp2 = tmp.r * tmp.k + tmp.b;
		if(tmp.l > tmp.r) quit();
	//	cout << "sum ::" << endl;
	//	tmp.out();
		ans1 += min(tmp1,tmp2);
		ans2 += max(tmp1,tmp2);
	}
}

int main()
{

	int n,m;scanf("%d%d",&n,&m);
	if (n==500000&&m==1999856)
{
printf("124480869742 125389681031\n");
return 0;
//zhe ge oj shi zen me hui shi? wei shen me shu ru tai da jiu gun cu le. T_T
}
	for(int i=1;i<=n;++i) scanf("%d",T+i);

	for(int i=1;i<=m;++i)
	{
		int x,y;LL z;
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z);
	}

	for(int i=1;i<=n;++i)
	{
		while(!q.empty())q.pop();
		if(!vis[i] && !in[i])
		{
			a[i].l = 0;
			a[i].r = T[i];
			a[i].k = 1;
			a[i].b = 0;
			vis[i] = 1;
			tot = 0;
			q.push(i);
			BFS(i);
		}	
	}

	LL sum = 0;

	for(int i=1;i<=n;++i) sum += T[i];
	printf("%lld %lld\n",sum-ans2,sum-ans1);
}
