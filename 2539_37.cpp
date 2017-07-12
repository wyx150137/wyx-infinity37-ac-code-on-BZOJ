
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
const int maxm=100000,inf=1061109567;
const ll mod=1000000007;
map<ll,int>id;  char str[30];   ll hash[100];
int h[100],p[maxm],c[maxm],cost[maxm],n1[maxm],q[maxm],sp[100],inq[100];
int D,n,S,T,TT,An=0,path[maxm],w[100][100],pre[100],tot=0,px[100],py[100];
inline void ae(int a,int b,int cc,int co)
{
	p[tot]=b; c[tot]=cc; cost[tot]=co;  n1[tot]=h[a]; h[a]=tot++;
	p[tot]=a; c[tot]=0;  cost[tot]=-co; n1[tot]=h[b]; h[b]=tot++;
}
inline int spfa()
{
	memset(sp,63,sizeof(sp));   
	memset(inq,0,sizeof(inq));
	int head=0,tail=1; 
	sp[S]=0; q[0]=S; 
	inq[S]=1; pre[S]=-1;
	while(head!=tail)
	{
		int u=q[head++]; 
		if(head>=maxm) 
			head-=maxm; 
		inq[u]=0;
		for(int i=h[u];~i;i=n1[i])
			if(c[i]>0&&sp[p[i]]>sp[u]+cost[i])
			{
				path[p[i]]=i, pre[p[i]]=u, sp[p[i]]=sp[u]+cost[i];
				if(!inq[p[i]])
				{ 
					inq[p[i]]=1, q[tail++]=p[i]; 
					if(tail>=maxm) 
						tail-=maxm;
				}
			}
	}
	return sp[T]!=inf;
}
inline int aug()
{
	int delta=inf,  flow=0;
	for(int i=T;pre[i]!=-1;i=pre[i]) delta=min(delta,c[path[i]]);
	for(int i=T;pre[i]!=-1;i=pre[i])
	{
		c[path[i]]-=delta, c[path[i]^1]+=delta;
		flow+=cost[path[i]]*delta;
	}
	return flow;
}
inline int cf()
{
	int ret=0; 
	while(spfa()) 
		ret+=aug(); 
	return ret;
}
inline ll gethash(char *str)
{
	ll tmp=0; int len=strlen(str);
	for(int j=0;j<len;j++) 
		if(str[j]>='A' && str[j]<='Z') 
			str[j]=str[j]+32; 
	for(int j=0;j<len;j++)
	{
		tmp=tmp*29+str[j];
		if(tmp>=mod) tmp%=mod;
	}
	return tmp;
}
inline int ok(int u,int v)
{
	if((px[u]-px[v])*(px[u]-px[v])+(py[u]-py[v])*(py[u]-py[v])>D*D) return 0;
	for(int i=1;i<=n<<1;i++)
	{
		if(i==u||i==v) continue;
		if((px[i]-px[u])*(px[i]-px[v])>0) continue;
		if((py[i]-py[u])*(py[i]-py[v])>0) continue;
		if((px[i]-px[u])*(py[v]-py[i])==(py[i]-py[u])*(px[v]-px[i])) return 0;
	}
	return 1;
}
int main()
{
	scanf("%d%d",&D,&n);
	S=0;TT=n<<1|1;T=TT+1;
	memset(h,0xff,sizeof(h));
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%s",&px[i],&py[i],str);
		px[i]+=50;py[i]+=50;
		id[hash[i]=gethash(str)]=i;
		ae(S,i,1,0);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%s",&px[n+i],&py[n+i],str);
		px[n+i]+=50;py[n+i]+=50;
		id[hash[n+i]=gethash(str)]=n+i;
		ae(n+i,T,1,0);
	}
	int u,v;
	for(int i=1;i<=n<<1;i++) 
		for(int j=1;j<=n<<1;j++) 
			w[i][j]=1;
	while(1)
	{
		scanf("%s",str);    
		if(!strcmp("End",str)) break;   
		u=id[gethash(str)];
		scanf("%s",str);    v=id[gethash(str)];
		scanf("%d",&w[u][v]);   w[v][u]=w[u][v];
	}
	for(int i=1;i<=n;i++) 
		for(int j=n+1;j<=n<<1;j++) 
			if(ok(i,j)) 
				ae(i,j,1,-w[i][j]);
	printf("%d\n",-cf()); 
	return 0;
}
