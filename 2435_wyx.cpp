
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include <algorithm>
using namespace std;
#define stack_size (20001000) 
#define N 1000000+5
#define M 2000000+5
int head[N],size[N];
int stack[stack_size],bak;  
int n;
struct graph
{
    int next,to,val;
    graph ()  {}
    graph (int _next,int _to,int _val)
    :next(_next),to(_to),val(_val){}
}edge[M];
void add(int x,int y,int z)
{
    static int cnt = 0;
    edge[++cnt]=graph(head[x],y,z);
    head[x]=cnt;
    edge[++cnt]=graph(head[y],x,z);
    head[y]=cnt;
}
long long ans;
void DFS(int x,int fa)
{
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa)
        {
            DFS(edge[i].to,x);
            size[x]+=size[edge[i].to];
            ans+=(long long)edge[i].val*abs(n-2*size[edge[i].to]);
        }
    //printf("size [%d]= %d\n",x,size[x] );
    return;
}
void CallDFS()    
{    
    __asm__ __volatile__    
    (    
        "mov %%esp,%0\n"  
        "mov %1,%%esp\n"  
        :"=g"(bak)    
        :"g"(stack+stack_size-1)    
        :    
    );    
    DFS(1,0);    
    __asm__ __volatile__    
    (    
        "mov %0,%%esp\n"  
        :    
        :"g"(bak)    
        :    
    );    
}   
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
   
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
int main()
{
 
    cin>>n;
    int x,y,z;
    for(int i=1;i<n;++i)
    {
        x=read(),y=read(),z=read();
        add(x,y,z);
    }
    for(int i=1;i<=n;++i)
        size[i]=1;
    CallDFS();
    cout<<ans;
}
