
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;  
#define MAXN 1000010  
#define MAXM 1010  
#define INF 1000000000  
#define MOD 1000000007  
#define eps 1e-8  
#define ll long long  
int n;  
char S[MAXN];  
int s[MAXN];  
int st[MAXN],tp;  
int low[MAXN],far[MAXN];  
int ans;  
int v[MAXN<<2];  
void build(int x,int y,int z){  
    if(y==z){  
        v[x]=far[y];  
        return ;  
    }  
    int mid=y+z>>1;  
    build(x<<1,y,mid);  
    build(x<<1|1,mid+1,z);  
    v[x]=max(v[x<<1],v[x<<1|1]);  
}  
int find(int x,int y,int z,int av){  
    if(v[x]<av){  
        return INF;  
    }  
    if(y==z){  
        return y;  
    }  
    int mid=y+z>>1;  
    if(v[x<<1]>=av){  
        return find(x<<1,y,mid,av);  
    }else{  
        return find(x<<1|1,mid+1,z,av);  
    }  
}  
int ask(int k,int L,int R,int l,int r,int av){  
    if(L==l&&R==r){  
        return find(k,L,R,av);  
    }  
    int mid=L+R>>1;  
    if(r<=mid){  
        return ask(k<<1,L,mid,l,r,av);  
    }else if(l>mid){  
        return ask(k<<1|1,mid+1,R,l,r,av);  
    }else{  
        int t=ask(k<<1,L,mid,l,mid,av);  
        if(t!=INF){  
            return t;  
        }  
        return ask(k<<1|1,mid+1,R,mid+1,r,av);  
    }  
}  
int main(){  
       
    int i;  
    scanf("%d%s",&n,S+1);  
    for(i=1;i<=n;i++){  
        s[i]=s[i-1]+(S[i]=='p'?1:-1);  
    }  
/*
    for(int i=1;i<=n;++i)
        cout << s[i] << " ";
    puts("");*/
    st[0]=-1;  
    st[++tp]=0;  
    for(i=1;i<=n;i++){  
        while(tp&&s[st[tp]]<=s[i]){  
            tp--;  
        }  
        low[i]=st[tp]+1;  
        st[++tp]=i;  
    }  
    tp=0;  
    st[++tp]=n+1;  
    s[n+1]=-INF;  
    for(i=n;~i;i--){  
        while(tp&&s[st[tp]]>=s[i]){  
            tp--;  
        }  
        far[i]=st[tp]-1;  
        st[++tp]=i;  
    }  
//    for(int i=1;i<=n;++i)
  //      cout << far[i] << " " << low[i] << " "<< endl; 
    build(1,0,n);  
    for(i=1;i<=n;i++){  
        if(low[i]!=i&&i-low[i]>ans){  
            ans=max(ans,i-ask(1,0,n,low[i],i-1,i));  
        }  
    }  
    printf("%d\n",ans);  
    return 0;  
}  
