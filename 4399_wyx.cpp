
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 4e5+5;
const int Max = 1000000000;

int m, c, sz, cnt;
int size[N],fa[N],val[N];
inline int find(int x) {
    return fa[x] ^ x ? fa[x] = find(fa[x]) : fa[x];
}

int root[N];
double tr[N*20]; 
int ls[N*20], rs[N*20], sum[N*20];

void insert(int &k,int l,int r,int pos,double e)
{
    k=++sz; sum[sz]=1; tr[k]=e;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(pos<=mid) insert(ls[k],l,mid,pos,e);
    else insert(rs[k],mid+1,r,pos,e); 
}

void merge(int &x,int y,int l,int r)
{
    if(!x||!y) {
        x += y; return ;
    }
    if(l==r){
        sum[x]+=sum[y];
        tr[x]+=tr[y];
        return;
    }
    int mid=(l+r)>>1;
    merge(ls[x],ls[y],l,mid);
    merge(rs[x],rs[y],mid+1,r);
    sum[x]=sum[ls[x]]+sum[rs[x]];
    tr[x]=tr[ls[x]]+tr[rs[x]];
}

void change1(int &k,int l,int r,int a,int v)
{
    if(!k) k=++sz;
    if(l==r) {
        sum[k]+=v;
        tr[k]+=v*log((double)l);
        return;
    }
    int mid=(l+r)>>1;
    if(mid<a) {
        v+=sum[ls[k]],ls[k]=0;
        change1(rs[k],mid+1,r,a,v);
    }
    else change1(ls[k],l,mid,a,v);
    sum[k] = sum[ls[k]] + sum[rs[k]];
    tr[k] = tr[ls[k]] + tr[rs[k]];
}


void change2(int &x,int l,int r,int a,int v)
{
    if(!x) x=++sz;
    if(l==r){
        sum[x]+=v;
        tr[x]+=v*log((double)l);
        return;
    }
    int mid=(l+r)>>1;
    if(mid+1>a) {
        v+=sum[rs[x]],rs[x]=0;
        change2(ls[x],l,mid,a,v);
    }
    else change2(rs[x],mid+1,r,a,v);
    sum[x] = sum[ls[x]] + sum[rs[x]];
    tr[x] = tr[ls[x]] + tr[rs[x]];
}

int get_kth(int x,int l,int r,int k)
{
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(sum[ls[x]]>=k) return get_kth(ls[x],l,mid,k);
    else return get_kth(rs[x],mid+1,r,k-sum[ls[x]]);
}

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int main()
{
    int a,b,c;
    for(cin>>m;m--;){
        c = read();
        if(c==1) {
            val[++cnt] = read(); fa[cnt] = cnt , size[cnt] = 1;
            insert(root[cnt],1,Max,val[cnt],log((double)val[cnt]));
        }
        else if(c==2) {
            a = read(), b = read();
            int p=find(a),q=find(b);
            if(p==q) continue;
            if(size[p] < size[q]) swap(p,q);
            merge(root[p],root[q],1,Max);
            fa[q]=p;size[p]+=size[q];
        }
        else if(c==3) {
            a = read(), b = read();
            change1(root[find(a)],1,Max,b,0);
        }
        else if(c==4) {
            a = read(), b = read();
            change2(root[find(a)],1,Max,b,0);
        }
        else if(c==5) {
            a = read(), b = read();
            printf("%d\n",get_kth(root[find(a)],1,Max,b));
        }
        else if(c==6)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",tr[root[find(a)]]>tr[root[find(b)]]?1:0);
        }
        else if(c==7)
        {
            a = read();
            printf("%d\n",size[find(a)]);
        }
        else if(c==8) a = read(), b = read();
        else a = read();
    }
}
