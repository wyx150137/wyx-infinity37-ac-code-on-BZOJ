
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std; 
#define maxn 200005 
  
struct Seg  
{  
    int l,r;  
    int lmx,rmx,ans,size,tag;  
}t[maxn<<2];  
  
int n,T;  
  
inline void add(int i,int x)  
{  
    t[i].tag=x;  
    if (x==1) t[i].lmx=t[i].rmx=t[i].ans=t[i].size=0;  
    else t[i].lmx=t[i].rmx=t[i].ans=t[i].size=t[i].r-t[i].l+1;  
}  
  
inline void release(int i) 
{
    if (t[i].tag==-1) return;  
    add(i*2,t[i].tag);add(i*2+1,t[i].tag);  
    t[i].tag=-1;  
}  
  
Seg merge(Seg x,Seg y)  
{  
    Seg ans;  
    ans.l=x.l;ans.r=y.r;  
    ans.size=x.size+y.size;  
    if (x.size==x.r-x.l+1) ans.lmx=x.size+y.lmx; else ans.lmx=x.lmx;  
    if (y.size==y.r-y.l+1) ans.rmx=y.size+x.rmx; else ans.rmx=y.rmx;  
    ans.ans=max(x.rmx+y.lmx,max(x.ans,y.ans));  
    ans.tag=-1;  
    return ans;  
}  
  
void build(int i,int l,int r)  
{  
    t[i].l=l;t[i].r=r;t[i].lmx=t[i].rmx=t[i].ans=t[i].size=0;t[i].tag=-1;  
    if (l==r) return;  
    int mid=(t[i].l+t[i].r)/2;  
    build(i*2,l,mid);build(i*2+1,mid+1,r);  
}  
  
void modify(int i,int l,int r,int d)  
{  
    if (l<=t[i].l && t[i].r<=r) {add(i,d);return;}  
    release(i);  
    int mid=(t[i].l+t[i].r)/2;  
    if (l<=mid) modify(i*2,l,r,d);  
    if (mid<r) modify(i*2+1,l,r,d);  
    t[i]=merge(t[i*2],t[i*2+1]);  
}  
  
int Query(int i,int l,int r)  
{  
    if (l<=t[i].l && t[i].r<=r) return t[i].size;  
    release(i);  
    int mid=(t[i].l+t[i].r)/2,ans=0;  
    if (l<=mid) ans+=Query(i*2,l,r);  
    if (mid<r) ans+=Query(i*2+1,l,r);  
    return ans;  
}  
  
void change(int i,int l,int r,int x)  
{  
    if (!x) return;  
    if (l<=t[i].l && t[i].r<=r && t[i].size<=x) {add(i,1);return;}  
    release(i);  
    int mid=(t[i].l+t[i].r)/2;  
    if (l<=mid)  
    {  
        int num=Query(i*2,l,r);  
        if (x>num) {modify(i*2,l,r,1);if (mid<r) change(i*2+1,l,r,x-num);}  
        else change(i*2,l,r,x);  
    }  
    else change(i*2+1,l,r,x);   
    t[i]=merge(t[i*2],t[i*2+1]);  
}  
  
Seg query(int i,int l,int r)  
{  
    if (l<=t[i].l && t[i].r<=r) return t[i];  
    release(i);  
    int mid=(t[i].l+t[i].r)/2;  
    if (r<=mid) return query(i*2,l,r);  
    else if (l>mid) return query(i*2+1,l,r);  
    else return merge(query(i*2,l,r),query(i*2+1,l,r));  
}  
  
int main()  
{  
    scanf("%d%d",&n,&T);  
    build(1,1,n);  
    while (T--)  
    {  
        int op,l1,l2,r1,r2;  
        scanf("%d%d%d",&op,&l1,&r1);  
        if (op==0) modify(1,l1,r1,0);  
        else if (op==1)  
        {  
            scanf("%d%d",&l2,&r2);  
            int num=r1-l1+1-Query(1,l1,r1);  
            modify(1,l1,r1,0);  
            change(1,l2,r2,num);  
        }  
        else   
        {  
            Seg ans=query(1,l1,r1);  
            printf("%d\n",ans.ans);  
        }  
    }  
    return 0;  
}  
