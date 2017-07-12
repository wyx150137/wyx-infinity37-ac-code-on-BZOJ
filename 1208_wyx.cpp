
#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#define FOR(a,b,c) for(int a=(b);a<=(c);a++)
using namespace std;

const int MOD = 1000000;
struct Node{
    Node* ch[2];
    int v,r;
    Node(int w) :v(w) { ch[0]=ch[1]=NULL; r=rand(); }
    int cmp(int x) const {
        if(x==v) return -1;  return x<v? 0:1;
    }
};
Node* root;

void rotate(Node* &o,int d) {
    Node*k=o->ch[d^1]; o->ch[d^1]=k->ch[d]; k->ch[d]=o; o=k;
}
void insert(Node* &o,int x) {
    if(o==NULL) o=new Node(x);
    else {
        int d=o->cmp(x); if(d==-1) return ;
        insert(o->ch[d],x);
        if(o->ch[d]->r > o->r) rotate(o,d^1);
    }
}
void remove(Node* &o,int x) {
    if(o==NULL) return ;
    int d=o->cmp(x);
    if(d==-1) {
        Node* u=o;
        if(o->ch[0]!=NULL && o->ch[1]!=NULL) {
            int d2=o->ch[0]->r > o->ch[1]->r? 1:0;
            rotate(o,d2); remove(o->ch[d2],x);
        }
        else {
            if(o->ch[0]!=NULL) o=o->ch[0];  else o=o->ch[1];
            delete u;
        }
    }
    else remove(o->ch[d],x);
}
void query1(Node* o,int x,int& ans) 
{
    if(o==NULL) return ;
    if(o->v <= x) { 
		ans=o->v; 
		query1(o->ch[1],x,ans); 
	}
    else query1(o->ch[0],x,ans);
}
void query2(Node* o,int x,int& ans) 
{
    if(o==NULL) return ;
    if(o->v >= x) { 
		ans=o->v; 
		query2(o->ch[0],x,ans); 
	}
    else query2(o->ch[1],x,ans);
}
int n;
int abs(int x) { return x<0? -x:x; }

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0'; ch = getchar(); }
	return x*f;
}

int main() {
    int a,b,c,ans=0,ta,tb;
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
	{
		int a = read(), b = read();
        if(root==NULL) root=new Node(b),c=a;
        else if(c==a) insert(root,b);
        else 
		{
            ta=tb=-1;
            query1(root,b,ta),query2(root,b,tb);
            if(ta==-1) 
			{ 
				ans+=abs(tb-b);  
				remove(root,tb);  
			}
            else if(tb==-1) 
			{ 
				ans+=abs(ta-b);  
				remove(root,ta);
			}
            else 
			{
                if(abs(ta-b)>abs(tb-b)) { ans+=abs(tb-b);  remove(root,tb);  }
                else { ans+=abs(ta-b);  remove(root,ta); }
            }
            ans%=MOD;
        }
    }
    printf("%d\n",ans);
    return 0;
}
