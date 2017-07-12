
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
const int maxn=100000+10;
int tr[maxn*4],h[maxn*4],go[maxn*25],nxt[maxn*25];
int d[maxn],a[maxn];
int i,j,k,l,t,n,m,q,tot,ans;

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

void add(int x,int y) {
    d[y]++;
    go[++tot]=y;
    nxt[tot]=h[x];
    h[x]=tot;
}
void build(int p,int l,int r) {
    if (l==r) {
        tr[p]=1;
        return;
    }
    int mid=(l+r)/2;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    tr[p]=tr[p*2]+tr[p*2+1];
}
void cover(int p,int l,int r,int a,int b) {
    if (l==a&&r==b) {
        add(p,i);
        return;
    }
    int mid=(l+r)/2;
    if (b<=mid) cover(p*2,l,mid,a,b);
    else if (a>mid) cover(p*2+1,mid+1,r,a,b);
    else {
        cover(p*2,l,mid,a,mid);
        cover(p*2+1,mid+1,r,mid+1,b);
    }
}
void change(int p,int l,int r,int a) {
    tr[p]--;
    if (!tr[p]) {
        int t=h[p];
        while (t) {
            d[go[t]]--;
            if (!d[go[t]]) ans++;
            t=nxt[t];
        }
    }
    if (l==r) return;
    int mid=(l+r)/2;
    if (a<=mid) change(p*2,l,mid,a);
    else change(p*2+1,mid+1,r,a);
}
int main() {
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=n;++i) a[i] = read();
    fo(i,1,m) {
        j = read(), k = read();
        cover(1,1,n,j,k);
    }
    scanf("%d",&q);
    while (q--) {
        scanf("%d",&j);
        j=(j+ans-1)%n+1;
        a[j]--;
        if (!a[j]) change(1,1,n,j);
        printf("%d\n",ans);
    }
}
