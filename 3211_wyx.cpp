
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
const int M = N << 2;
using namespace std;
typedef long long LL;

LL tr[M],lazy[M];
LL a[N],n;

inline void updata(int k){
    tr[k] = tr[k<<1] + tr[k<<1|1];
    lazy[k] = lazy[k<<1] & lazy[k<<1|1];
}

inline void build(int k,int l,int r){
    if(l==r){
        tr[k] = a[l];
        if(tr[k] == 0 || tr[k] == 1)lazy[k] = 1;
        return ;
    }
    int mid = (l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    updata(k);
}

void change(int k,int l,int r,int x,int y){
    if(lazy[k]) return;
    if(l==r){
        tr[k] = (LL)sqrt(tr[k]);
        if(tr[k] == 0 || tr[k] == 1) lazy[k] = 1; return;
    }
    int mid = (l+r)>>1;
    if(y <= mid) change(k<<1,l,mid,x,y);
    else if(x>mid)change(k<<1|1,mid+1,r,x,y);
    else change(k<<1,l,mid,x,mid),change(k<<1|1,mid+1,r,mid+1,y);
    updata(k);
}

LL ask(int k,int l,int r,int x,int y){
    if(l==x && r==y)return tr[k];
    int mid = (l+r)>>1;
    if(y<=mid)return ask(k<<1,l,mid,x,y);
    else if(x>mid)return ask(k<<1|1,mid+1,r,x,y);
    else return ask(k<<1,l,mid,x,mid)+ask(k<<1|1,mid+1,r,mid+1,y);
}

inline LL read(){
    LL x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int main(){
    n = read();
    for(int i=1;i<=n;++i)a[i] = read();
    build(1,1,n);int m = read();
    while(m--){
        int opt = read(),x = read(),y = read(); if(x>y)swap(x,y);
        if(opt == 2) change(1,1,n,x,y);
        else printf("%lld\n",ask(1,1,n,x,y));
    }
}
