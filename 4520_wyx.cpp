
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL inf = 1ll<<62;
const int N = 1e5+5;
priority_queue <LL,vector<LL>,greater<LL> >mxs;

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int n,k, X[2], dx;

inline LL calc(LL x,LL y) {
    return x*x+y*y;
}

inline void updata(LL x) {
    if(x < mxs.top()) return;
    mxs.pop(); mxs.push(x);
}

struct data {
    int x[2], mn[2], mx[2];
    data * son[2], *f;
    inline void set (int x1,int x2) {
        x[0] = mn[0] = mx[0] = x1;
        x[1] = mn[1] = mx[1] = x2;
    }
    inline void updata() {
        for(int i=0;i<2;++i) if(son[i] != NULL) {
            for(int j=0;j<2;++j) {
                mn[j] = min(mn[j],son[i]->mn[j]);
                mx[j] = max(mx[j],son[i]->mx[j]);
            }
        }
    }

    inline LL maxv () {
        if(!this) return -1;
        int tmp1 = X[0] - mn[0],
            tmp2 = mx[0] - X[0],
            tmp3 = X[1] - mn[1],
            tmp4 = mx[1] - X[1];
        tmp1 = max(tmp1,0); tmp2 = max(tmp2,0); 
        tmp3 = max(tmp3,0); tmp4 = max(tmp4,0);
        return calc(tmp1|tmp2,tmp3|tmp4);
    }

    void get() {
        LL tmp1 = -1, tmp2 = -1;
        ::updata(calc(x[0]-X[0],x[1]-X[1]));
        tmp1 = max(tmp1,son[0]->maxv());
        tmp2 = max(tmp2,son[1]->maxv());
        if(tmp1 > tmp2) {
            if(tmp1 > mxs.top()) son[0] -> get();
            if(tmp2 > mxs.top()) son[1] -> get();
        }
        else {
            if(tmp2 > mxs.top()) son[1] -> get();
            if(tmp1 > mxs.top()) son[0] -> get();
        }
    }
    bool operator < (const data &z) const {
        return x[dx] ^ z.x[dx] ? x[dx] < z.x[dx] : x[dx^1] < z.x[dx^1];
    }
}ns[N],*root;

data* build(data *l, data *r) {
    if(l==r) return NULL;
    data *mid = l + ((r-l)>>1);
    nth_element(l,mid,r);
    dx ^= 1;
    mid -> son[0] = build(l,mid);
    mid -> son[1] = build(mid+1,r);
    mid -> updata();
    dx ^= 1;
    return mid;
}

int main() {
    n = read(), k = read();k *= 2;
    for(int i=0;i<k;++i) mxs.push(0);
    for(int i=0;i<n;++i) ns[i].set(read(),read());
    root = build(ns,ns+n);
    for(int i=0;i<n;++i) {
        X[0] = ns[i].x[0];
        X[1] = ns[i].x[1];
        root -> get();
    }
    cout << mxs.top() << endl;
}
