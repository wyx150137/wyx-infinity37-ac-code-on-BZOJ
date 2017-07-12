
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<set>
#include<queue>
#include<ctime>
#include<vector>
#define N 100010
#define mod 998244353
using namespace std;
inline int rd(){
  register char ch=getchar();
  register bool flag=false;
  register int res=0;
  while(ch<'0'||ch>'9'){flag=(ch=='-');ch=getchar();}
  while(ch>='0'&&ch<='9'){
    res=(res<<3)+(res<<1)+ch-'0';ch=getchar();}
  if(flag)res=-res;
  return res;
}
int cnt;
int vis[N<<2];
int w1[N<<2];
int inv[N],fac[N];
int W1,n;
inline int qp(int x,int o){
  int y=1;
  while(o){
    if(o&1)y=1LL*x*y%mod;
    x=1LL*x*x%mod;
    o>>=1;
  }
  return y;
}
struct events{int type,l,r,W1,W2;
  inline void read(){
    type=rd();l=rd();r=rd();
    if(type==2)l--,W1=0;
    else W1=inv[r-l+1],W2=(W1+W1>=mod?W1+W1-mod:W1+W1);
    //printf("action %d %d %d %d\n",type,l,r,W1);
   } 
}evt[N];
int xu[N];
inline void clear(){++cnt;}
inline void find(int o,int l,int r,int L,int R){
  if(L>R)return;//printf("find %d %d %d %d\n",l,r,L,R);
    if(vis[o]!=cnt){w1[o]=0;vis[o]=cnt;}//no change
  if(l==L&&r==R){
    W1=((1LL*W1*(mod+1-w1[o]))+(1LL*(mod+1-W1)*w1[o]))%mod;
    return;
  }
  int mid=(l+r)>>1;
  if(R<=mid)find(o<<1,l,mid,L,R);else if(L>mid)find(o<<1|1,mid+1,r,L,R);else find(o<<1,l,mid,L,mid),find(o<<1|1,mid+1,r,mid+1,R);
}
inline void settag(int o,int l,int r,int x,int W1){
  int mid=(l+r)>>1;
  while(l!=r){//printf("settag %d %d %d\n",l,r,x);
    if(vis[o]!=cnt){w1[o]=0;vis[o]=cnt;}
    //w1[o]=(vis[o]!=cnt)?0:w1[o];
  w1[o]=((1LL*W1*(mod+1-w1[o]))+(1LL*(mod+1-W1)*w1[o]))%mod;
  if(x<=mid)r=mid,o=o<<1;
  else l=mid+1,o=o<<1|1;
  mid=(l+r)>>1;
  }
    if(vis[o]!=cnt){w1[o]=0;vis[o]=cnt;}
  //w1[o]=(vis[o]!=cnt)?0:w1[o];
  w1[o]=((1LL*W1*(mod+1-w1[o]))+(1LL*(mod+1-W1)*w1[o]))%mod;
}
bool cmpl(const int &u,const int &v){return evt[u].l<evt[v].l||(evt[u].l==evt[v].l&&u<v);}
bool cmpr(const int &u,const int &v){return evt[u].r>evt[v].r||(evt[u].r==evt[v].r&&u<v);}
int pre1[N],pre2[N];
inline void cdq(int l,int r){//printf("cdq %d %d\n",l,r);
  if(l==r)return;
  int i,j,len=0,mid=(l+r)>>1;
  if(pre1[r]-pre1[l-1]==0||pre2[r]-pre2[l-1]==0)return;
  cdq(l,mid);cdq(mid+1,r);
  
  if(pre1[mid]-pre1[l-1]==0||pre2[r]-pre2[mid]==0)return;
  //printf("realdo %d %d\n",l,r);
  for(i=l;i<=mid;i++)evt[i].type==1?(xu[++len]=i):0;
  for(i=mid+1;i<=r;i++)evt[i].type==2?(xu[++len]=i):0;
  sort(xu+1,xu+len+1,cmpr);//printf("len=%d\n",len);
  clear();
  for(i=1;i<=len;i++)
  if(evt[xu[i]].type==1)settag(1,0,n,evt[xu[i]].l,evt[xu[i]].W2);
  else {W1=evt[xu[i]].W1;find(1,0,n,1,evt[xu[i]].l);evt[xu[i]].W1=W1;}
  clear();
  for(i=1;i<=len;i++)
 if(evt[xu[i]].type==1)settag(1,0,n,evt[xu[i]].l,evt[xu[i]].W1);
else {W1=evt[xu[i]].W1;find(1,0,n,evt[xu[i]].l+1,evt[xu[i]].r);evt[xu[i]].W1=W1;}
  sort(xu+1,xu+len+1,cmpl);
  clear();
  for(i=1;i<=len;i++)
    if(evt[xu[i]].type==1)settag(1,0,n,evt[xu[i]].r,evt[xu[i]].W1);
else {W1=evt[xu[i]].W1;find(1,0,n,evt[xu[i]].l,evt[xu[i]].r-1);evt[xu[i]].W1=W1;}
  
}
void work(){
  int i,j,p;n=rd();
  fac[0]=fac[1]=1;for(i=2;i<=n;i++)fac[i]=1LL*fac[i-1]*i%mod;
  inv[n]=qp(fac[n],mod-2);for(i=n-1;i>=1;i--)inv[i]=1LL*inv[i+1]*(i+1)%mod;
  for(i=1;i<=n;i++)inv[i]=1LL*fac[i-1]*inv[i]%mod;
  int m=rd();for(i=1;i<=m;i++)evt[i].read(),pre1[i]=pre1[i-1],pre2[i]=pre2[i-1],(evt[i].type==1?pre1[i]++:pre2[i]++);
  
  //for(i=1;i<=n;i++)printf("%d %d %lld\n",fac[i],inv[i],1LL*inv[i]*i%mod);
  cdq(1,m);j=0;
  for(i=1;i<=m;i++)if(evt[i].type==1)j^=1;
    else if(evt[i].l==0&&j)printf("%d\n",evt[i].W1);else {p=mod+1-evt[i].W1;p>=mod?(p=p-mod):0;printf("%d\n",p);}
}
int main(){
  work();
  return 0;
}
