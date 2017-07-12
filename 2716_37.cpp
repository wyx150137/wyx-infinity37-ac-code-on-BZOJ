
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define ll long long
#define inf 1000000000 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,root,D;
struct P{
	int d[2],mn[2],mx[2],l,r;
	int& operator[](int x){return d[x];}
	P(int x=0,int y=0)
		{l=0,r=0;d[0]=x,d[1]=y;}  
}p[500005];
bool operator<(P a,P b)
{
	return a[D]<b[D];
}
inline int dis(P a,P b)
{
	return abs(a[0]-b[0])+abs(a[1]-b[1]);
}
struct kdtree{
	int ans;
	P t[1000005],T;
	void update(int k){
		P l=t[t[k].l],r=t[t[k].r];
		for(int i=0;i<2;i++)
		{
			if(t[k].l)t[k].mn[i]=min(t[k].mn[i],l.mn[i]),t[k].mx[i]=max(t[k].mx[i],l.mx[i]);
			if(t[k].r)t[k].mn[i]=min(t[k].mn[i],r.mn[i]),t[k].mx[i]=max(t[k].mx[i],r.mx[i]);
		}
	}
	int build(int l,int r,int now){
		D=now;
		int mid=(l+r)>>1;
		nth_element(p+l,p+mid,p+r+1);
		t[mid]=p[mid];
		for(int i=0;i<2;i++)
			t[mid].mn[i]=t[mid].mx[i]=t[mid][i];
		if(l<mid)t[mid].l=build(l,mid-1,now^1);
		if(r>mid)t[mid].r=build(mid+1,r,now^1);
		update(mid);
		return mid;
	}
	int get(int k,P p){
		int tmp=0;
		for(int i=0;i<2;i++)
			tmp+=max(0,t[k].mn[i]-p[i]);
		for(int i=0;i<2;i++)
			tmp+=max(0,p[i]-t[k].mx[i]);
		return tmp;
	}
	void insert(int k,int now){
		if(T[now]>=t[k][now])
		{
			if(t[k].r)insert(t[k].r,now^1);
			else 
			{
				t[k].r=++n;t[n]=T;
				for(int i=0;i<2;i++)
					t[n].mn[i]=t[n].mx[i]=t[n][i];
			}
		}
		else 
		{
			if(t[k].l)insert(t[k].l,now^1);
			else 
			{
				t[k].l=++n;t[n]=T;
				for(int i=0;i<2;i++)
					t[n].mn[i]=t[n].mx[i]=t[n][i];
			}
		}
		update(k);
	}
	void query(int k,int now){
		int d,dl=inf,dr=inf;
		d=dis(t[k],T);
		ans=min(ans,d);
		if(t[k].l)dl=get(t[k].l,T);
		if(t[k].r)dr=get(t[k].r,T);
		if(dl<dr)
		{
			if(dl<ans)query(t[k].l,now^1);
			if(dr<ans)query(t[k].r,now^1);
		}
		else
		{
			if(dr<ans)query(t[k].r,now^1);
			if(dl<ans)query(t[k].l,now^1);
		}
	}
	int query(P p){
		ans=inf;T=p;query(root,0);
		return ans;
	}
	void insert(P p){
		T=p;insert(root,0);
	}
}kd;
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)p[i][0]=read(),p[i][1]=read();
	root=kd.build(1,n,0);
	while(m--)
	{
		int opt=read(),x=read(),y=read();
		if(opt==1)kd.insert(P(x,y));
		else printf("%d\n",kd.query(P(x,y)));
	}
	return 0;
}
