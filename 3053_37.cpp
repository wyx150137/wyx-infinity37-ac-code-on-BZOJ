
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 50005;
const int INF = 1e9+1;
int n,k,D,root;
struct Point
{
	int mx[6],mn[6],d[6],l,r;
	int& operator[](int x){return d[x];}
	void clear()
	{
		for(int i = 0;i<6;i++)
			mx[i]=mn[i]=d[i]=0;
	}
}p[N];
bool operator <(Point a,Point b)
{
	return a[D]<b[D];
}
int getdis(Point a,Point b)
{
	int ans = 0;
	for(int i = 0;i<k;i++)
		ans = ans+(a[i]-b[i])*(a[i]-b[i]);
	return ans;
}
int top;
struct Heap
{
	int o,dis;
	Heap(int _o=0,int _dis=INF):o(_o),dis(_dis){}
	bool operator <(const Heap &s)const
	{
		return dis<s.dis;
	}
}ans[15];
struct KD_tree
{
	Point t[N],target;
	int cnt;
	void clear()
	{
		for(int i = 0;i<N;i++)
			t[i].clear();
		target.clear();
		cnt = 0;
	}
	void Push_up(int p)
	{
		Point l = t[t[p].l],r = t[t[p].r];
		for(int i = 0;i<k;i++)
		{
			if(t[p].l)t[p].mx[i]=max(t[p].mx[i],l.mx[i]),t[p].mn[i]=min(t[p].mn[i],l.mn[i]);
			if(t[p].r)t[p].mx[i]=max(t[p].mx[i],r.mx[i]),t[p].mn[i]=min(t[p].mn[i],r.mn[i]);
		}
	}
	int getmindis(int x,Point p)
	{
		int ans = 0;
		for(int i = 0;i<k;i++)
		{
			if(p[i]>t[x].mx[i])
				ans = ans+(p[i]-t[x].mx[i])*(p[i]-t[x].mx[i]);
			if(p[i]<t[x].mn[i])
				ans = ans+(t[x].mn[i]-p[i])*(t[x].mn[i]-p[i]);
		}
		return ans;
	}
	int build(int l,int r,int now)
	{
		D = now;
		int mid = (l+r)>>1;
		nth_element(p+l,p+mid,p+r+1);
		t[mid] = p[mid];
		for(int i = 0;i<k;i++)
			t[mid].mx[i]=t[mid].mn[i]=t[mid][i];
		if(l<mid)t[mid].l = build(l,mid-1,(now+1)%k);
		if(r>mid)t[mid].r = build(mid+1,r,(now+1)%k);
		Push_up(mid);
		return mid;
	}
	void getans(int o)
	{
		int d,dl = INF,dr = INF;
		d = getdis(target,t[o]);
		if(d<ans[1].dis)
		{
			pop_heap(ans+1,ans+top+1);
			ans[top] = Heap(o,d);
			push_heap(ans+1,ans+top+1);
		}
		if(t[o].l)dl = getmindis(t[o].l,target);
		if(t[o].r)dr = getmindis(t[o].r,target);
		if(dl<dr)
		{
			if(dl<ans[1].dis)getans(t[o].l);
			if(dr<ans[1].dis)getans(t[o].r);
		}else
		{
			if(dr<ans[1].dis)getans(t[o].r);
			if(dl<ans[1].dis)getans(t[o].l);
		}
	}
	void Getans(const Point &o,int num)
	{
		for(int i = 1;i<=num;i++)
			ans[i] = Heap(0,INF);
		top = num;
		target = o;
		getans(root);
	}
}kd;
void init()
{
	kd.clear();
	top = 0;
	for(int i = 0;i<15;i++)
		ans[i]=Heap(0,INF);
}
void work()
{
	init();
	for(int i = 1;i<= n;i++)
		for(int j = 0;j<k;j++)
			scanf("%d",&p[i].d[j]);
	root = kd.build(1,n,0);
	int m,num;Point t;
	scanf("%d",&m);
	while(m--)
	{
		for(int i = 0;i<k;i++)
			scanf("%d",&t.d[i]);
		scanf("%d",&num);
		kd.Getans(t,num);
		printf("the closest %d points are:\n",num);
		sort(ans+1,ans+num+1);
		for(int j = 1;j<=num;j++)
		{
			for(int tt = 0;tt<k-1;tt++)
				printf("%d ",p[ans[j].o][tt]);
			printf("%d\n",p[ans[j].o][k-1]);
		}
	}
}
int main()
{
	while(scanf("%d%d",&n,&k)!=EOF)
		work();
	return 0;
}
