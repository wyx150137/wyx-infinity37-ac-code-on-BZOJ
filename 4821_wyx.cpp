
#include<cmath>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iomanip>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#define ll long long
#define inf 1000000000
#define mod 1000000007
#define ls x<<1
#define rs x<<1|1
#define N 100005
#define fo(i,a,b) for(i=a;i<=b;i++)
#define fd(i,a,b) for(i=a;i>=b;i--)
using namespace std;
struct TREE{double sumx,sumy,sumxy,sumxx,tag_x,tag_y; int l,r,len,tag_c;} tree[N*4];
double xx[N],yy[N];
int n,m,i,opt,l,r,dx,dy;
void updata(int x)
{
    tree[x].sumx = tree[ls].sumx + tree[rs].sumx;
    tree[x].sumy = tree[ls].sumy + tree[rs].sumy;
    tree[x].sumxy = tree[ls].sumxy + tree[rs].sumxy;
    tree[x].sumxx = tree[ls].sumxx + tree[rs].sumxx;
}
void build(int x,int l,int r)
{
    tree[x].len = r - l + 1; tree[x].l = l; tree[x].r = r;
    if (l == r) 
        {
            tree[x].sumx = xx[l]; tree[x].sumy = yy[l];
            tree[x].sumxy = xx[l] * yy[l]; 
            tree[x].sumxx = xx[l] * xx[l];
            return;
        }
    int mid = (l + r) >> 1;
    build(ls,l,mid); 
    build(rs,mid+1,r); 
    updata(x);
}
double calc(int x) {return (double)x*(x+1)*(2*x+1)/6;}
void update_a(int x,double dx,double dy)
{
    tree[x].sumxy += tree[x].sumx * dy + tree[x].sumy * dx + tree[x].len * dx * dy;
    tree[x].sumxx += tree[x].sumx * dx * 2 + tree[x].len * dx * dx;
    tree[x].sumx += dx * tree[x].len;
    tree[x].sumy += dy * tree[x].len;
    tree[x].tag_x += dx; tree[x].tag_y += dy;
}
void update_c(int x)
{
    tree[x].sumx = tree[x].sumy = (double)(tree[x].l+tree[x].r)*tree[x].len/2;
    tree[x].sumxy = tree[x].sumxx = calc(tree[x].r) - calc(tree[x].l-1);
    tree[x].tag_c = 1;
    tree[x].tag_x = tree[x].tag_y = 0;
}
void down(int x)
{
    if (tree[x].tag_c) {update_c(ls); update_c(rs); tree[x].tag_c = 0;}
    if (tree[x].tag_x || tree[x].tag_y)
        {
            update_a(ls,tree[x].tag_x,tree[x].tag_y);
            update_a(rs,tree[x].tag_x,tree[x].tag_y);
            tree[x].tag_x = tree[x].tag_y = 0;
        }
}
void add(int x,int l,int r,int L,int R,int dx,int dy)
{
    if (L <= l && r <= R) {
        update_a(x,dx,dy); 
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if (L <= mid) add(ls,l,mid,L,R,dx,dy);
    if (mid < R) add(rs,mid+1,r,L,R,dx,dy);
    updata(x);
}
void change(int x,int l,int r,int L,int R)
{
    if (L <= l && r <= R) {
        update_c(x); 
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if (L <= mid) change(ls,l,mid,L,R);
    if (mid < R) change(rs,mid+1,r,L,R);
    updata(x);
}
double query(int x,int l,int r,int L,int R,int opt)
{
    if (L <= l && r <= R) {
        if (opt == 1) return tree[x].sumx;
        if (opt == 2) return tree[x].sumy;
        if (opt == 3) return tree[x].sumxy;
        if (opt == 4) return tree[x].sumxx;
    }
    down(x);
    int mid = (l + r) >> 1; double res = 0;
    if (L <= mid) res += query(ls,l,mid,L,R,opt);
    if (mid < R) res += query(rs,mid+1,r,L,R,opt);
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    fo(i,1,n) scanf("%lf",&xx[i]);
    fo(i,1,n) scanf("%lf",&yy[i]);
    build(1,1,n);
    while (m--)
    {
        scanf("%d",&opt);
        scanf("%d%d",&l,&r);
        if (opt == 1) {
            double res1 = query(1,1,n,l,r,1); double res2 = query(1,1,n,l,r,2);
            double res3 = query(1,1,n,l,r,3); double res4 = query(1,1,n,l,r,4);
            double p = res3 - res1 * res2 / (r-l+1);
            double q = res4 - res1 * res1 / (r-l+1);
            printf("%.10lf\n",p/q);
        }   
        else {
            scanf("%d%d",&dx,&dy);
            if (opt == 3) change(1,1,n,l,r);
            add(1,1,n,l,r,dx,dy);
        }       
    }
    return 0;   
}
