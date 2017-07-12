
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int X=1000001,Y=1000000,N=2000005;
struct FEN{
    int xl,xr,y,i;
    bool flag;
    bool operator < (const FEN &o)const{
        return y!=o.y?y>o.y:xl<o.xl;
    }
} fen[N<<1];

struct FLO{
    int x,y;
    bool operator < (const FLO &o)const{
        return y>o.y;
    }
} flo[N];
struct CS{
    int x,y,i;
    bool operator < (const CS &o)const{
        return y>o.y;
    }
} cow[N];
struct SS{
    int nm;
    bool cov,cut;
} tr[X<<2];
int ans[N],fs[N];;
char * cp=(char *)malloc(20000000);
inline void in(int &x){
    for (;*cp<'0'||*cp>'9';cp++);
    for (x=0;*cp>='0'&&*cp<='9';cp++)
        x=x*10+*cp-'0';
}
inline void pushup(int x){
    tr[x].nm=tr[x<<1].nm+tr[x<<1|1].nm;
    tr[x].cut=tr[x<<1].cut|tr[x<<1|1].cut;
}
inline void paint(int x){
    tr[x].cov=1;
    tr[x].nm=0;
}
inline void pushdown(int x){
    if(tr[x].cov){
        paint(x<<1),paint(x<<1|1);
        tr[x].cov=0;
    }
}
void add(int x,int l,int r,int pur,int val){
    tr[x].nm+=val;
    if (l==r) return; 
    int mid=(l+r)>>1;
    pushdown(x);
    if(pur<=mid)
        add(x<<1,l,mid,pur,val);
    else 
        add(x<<1|1,mid+1,r,pur,val);
    pushup(x);
}
void cov(int x,int l,int r,int L,int R){
    if(L<=l&&r<=R){
        paint(x);
        return;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if(L<=mid)cov(x<<1,l,mid,L,R);
    if(R>mid)cov(x<<1|1,mid+1,r,L,R);
    pushup(x);
}
int query(int x,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
    {
        return tr[x].nm;
    }
    int mid=(l+r)>>1,ans=0;
    pushdown(x);
    if(L<=mid)ans+=query(x<<1,l,mid,L,R);
    if(R>mid)ans+=query(x<<1|1,mid+1,r,L,R);
    return ans;
}
void update(int x,int l,int r,int pur)
{
    if(l==r)
    {
        tr[x].cut^=1;
        return; 
    }
    int mid=l+r>>1;
    pushdown(x);
    if(pur<=mid)
        update(x<<1,l,mid,pur);
    else 
        update(x<<1|1,mid+1,r,pur);
    pushup(x);
}
int next(int x,int l,int r,int L)
{
    if(l>=L)
    {
        if(tr[x].cut)
        {
            while(l!=r)
                if(tr[x<<1].cut)
                    x<<=1,r=l+r>>1;
                else 
                    x=x<<1|1,l=(l+r>>1)+1;
            return l;
        }
        else return 0;
    }
    int tmp,mid=(l+r)>>1;
    pushdown(x);
    if(L<=mid&&(tmp=next(x<<1,l,mid,L)))
        return tmp;
    else 
        return next(x<<1|1,mid+1,r,L);
}
int main()
{
	//freopen("tt.in","r",stdin);
    fread(cp,1,20000000,stdin);
    int f,m,n,x1,y1,x2,y2;
    in(f);
    for(int i=f;i--;)
    {
        in(x1),in(y1),in(x2),in(y2);
        fen[i<<1]=(FEN){x1,x2,y1-1,i,0};
        fen[i<<1|1]=(FEN){x1,x2,y2,i,1};
    }
    sort(fen,fen+(f<<1));
    in(m);
    for(int i=m;i--;)
        in(flo[i].x),in(flo[i].y);
    sort(flo,flo+m);
    in(n);
    for(int i=0;i<n;++i)
    {
        in(cow[i].x),in(cow[i].y);
        cow[i].i=i;
    }
    sort(cow,cow+n);
    f=m=n=0;
    update(1,1,Y,Y);
    int sum,cut;
    for(int i=Y;i;--i)
    {
        for(;fen[f].y==i;++f)
            if(fen[f].flag==0)
            {
                cov(1,1,Y,fen[f].xl,fen[f].xr);
                if(fen[f].xl!=1)
                    add(1,1,Y,fen[f].xl-1,-fs[fen[f].i]);
                if(fen[f].xl!=1)
                    update(1,1,Y,fen[f].xl-1);
                if(fen[f].xr!=Y)
                    update(1,1,Y,fen[f].xr);
            }else
            {
                cut=next(1,1,Y,fen[f].xr);
                sum=query(1,1,Y,fen[f].xl,fen[f].xr);
                fs[fen[f].i]=query(1,1,Y,fen[f].xr+1,cut);
                cov(1,1,Y,fen[f].xl,fen[f].xr);
                if(fen[f].xl>1)
                    add(1,1,Y,fen[f].xl-1,sum+fs[fen[f].i]);
                if(fen[f].xl!=1)
                    update(1,1,Y,fen[f].xl-1);
                if(fen[f].xr!=Y)
                    update(1,1,Y,fen[f].xr);
            }
        for(;flo[m].y==i;++m)
            add(1,1,Y,flo[m].x,1);
        for(;cow[n].y==i;++n)
        {
            cut=next(1,1,Y,cow[n].x);
            ans[cow[n].i]=query(1,1,Y,cow[n].x,cut);
        }
    }
    for(int i=0;i<n;++i)
        printf("%d\n",ans[i]);
    return 0;
}
