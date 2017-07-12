
#include <cstdio>
#include <algorithm>
#define lowbit(x) ((x) & (-x))

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct seg{
    int l,r,t;
}ss[100005];

inline bool operator<(const seg&a,const seg&b){
    return a.r!=b.r?a.r<b.r:a.l<b.l;
}

int n,p=0;

int bit[100005];
inline void maxs(int&a,int b){if(a<b)a=b;}

inline void ins(int w,int x){
    ++w;
    while(w<=n+1)
    	maxs(bit[w],x),w+=lowbit(w);
}

inline int find(int w){
    ++w;
    int ans=0;
    while(w)
    	maxs(ans,bit[w]),w-=lowbit(w);
    return ans;
}

int main(){
    scanf("%d",&n);
    for(int i=0,l,r;i<n;i++){
       	l = read() + 1, r = n - read();
        if(l<=r) ss[p++]=(seg){l,r,1};
    }
    std::sort(ss,ss+p);
    int p2=0;

    for(int i=1;i<p;i++) {
        if(ss[i].l==ss[p2].l&&ss[i].r==ss[p2].r)++ss[p2].t;
        else ss[++p2]=ss[i];
    }

    p=p2+1;
    for(int i=0;i<p;i++) {
        int c=ss[i].r-ss[i].l+1;
        if(ss[i].t>c)ss[i].t=c;
    }

    int ans=0;
    for(int i=0;i<p;i++) {
        int c=ss[i].t+find(ss[i].l-1);
        maxs(ans,c);
        ins(ss[i].r,c);
    }
    printf("%d\n",n-ans);
    return 0;
}
