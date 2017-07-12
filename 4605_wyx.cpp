
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500000+5 ;
const int M = N << 2;
const int Maxm = 6400010;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

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
  
struct poi {
	int x,y;
	poi () {}
	poi (int _,int __)
	:x(_),y(__){}
}a[Maxm],tmp[Maxm];

int flag;

bool cmp(const poi &a,const poi &b){
	if(!flag) return a.x ^ b.x ? a.x < b.x : a.y < b.y;
	else return a.y ^ b.y ? a.y < b.y : a.x < b.x;
}


struct kdtree{
	int root[Maxm],sz;

	struct data{
		int ch[2], x[2],y[2];
		int size;
	}tr[Maxm];

//	int ch[Maxm][2], x[Maxm][2], y[Maxm][2],sz,size[Maxm];

	inline void updata(int k){/*
		if(ch[k][0]) {
			x[k][0] = min(x[k][0],x[ch[k][0]][0]);
			x[k][1] = max(x[k][1],x[ch[k][0]][1]);
			y[k][0] = min(y[k][0],y[ch[k][0]][0]);
			y[k][1] = max(y[k][1],y[ch[k][0]][1]);
		}
		if(ch[k][1]){
			x[k][0] = min(x[k][0],x[ch[k][1]][0]);
			x[k][1] = max(x[k][1],x[ch[k][1]][1]);
			y[k][0] = min(y[k][0],y[ch[k][1]][0]);
			y[k][1] = max(y[k][1],y[ch[k][1]][1]);	
		} 
		size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;*/
		if(tr[k].ch[0]) {
			tr[k].x[0] = min(tr[k].x[0],tr[tr[k].ch[0]].x[0]),
			tr[k].x[1] = max(tr[k].x[1],tr[tr[k].ch[0]].x[1]),
			tr[k].y[0] = min(tr[k].y[0],tr[tr[k].ch[0]].y[0]),
			tr[k].y[1] = max(tr[k].y[1],tr[tr[k].ch[0]].y[1]);
		}
		if(tr[k].ch[1]) {
			tr[k].x[0] = min(tr[k].x[0],tr[tr[k].ch[1]].x[0]),
			tr[k].x[1] = max(tr[k].x[1],tr[tr[k].ch[1]].x[1]),
			tr[k].y[0] = min(tr[k].y[0],tr[tr[k].ch[1]].y[0]),
			tr[k].y[1] = max(tr[k].y[1],tr[tr[k].ch[1]].y[1]);
		}
		tr[k].size = tr[tr[k].ch[0]].size + tr[tr[k].ch[1]].size + 1;
	}

	int cnt;
	queue <int> q;

	void DFS(int k){/*
		if(ch[k][0]) DFS(ch[k][0]);
		q.push(k); tmp[++cnt] = a[k];
		if(ch[k][1]) DFS(ch[k][1]);*/
		if(tr[k].ch[0]) DFS(tr[k].ch[0]);
		q.push(k); tmp[++cnt] = a[k];
		if(tr[k].ch[1]) DFS(tr[k].ch[1]);
	}

	void build(int &k,int L,int R,int tt){
		if(L > R) return; k = q.front(); q.pop(); 
		tr[k].size = 1, tr[k].ch[0] = tr[k].ch[1] = 0; flag = tt;
	//	size[k] = 1, ch[k][0] = ch[k][1] = 0; flag = tt; 
		int mid = (L+R) >> 1; nth_element(tmp+L+1,tmp+mid+1,tmp+R+1,cmp);
		a[k] = tmp[mid]; 
	//	x[k][0] = x[k][1] = tmp[mid].x , y[k][0] = y[k][1] = tmp[mid].y;
		tr[k].x[0] = tr[k].x[1] = tmp[mid].x , tr[k].y[0] = tr[k].y[1] = tmp[mid].y;
	//	build(ch[k][0],L,mid-1,tt^1); build(ch[k][1],mid+1,R,tt^1);
		build(tr[k].ch[0],L,mid-1,tt^1); build(tr[k].ch[1],mid+1,R,tt^1);
		updata(k);
	}	

	void rebuild(int &k){
		cnt = 0;DFS(k);
		build(k,1,cnt,0);
	}

	void insert(int &k,poi &z,int t=0){
		if(!k) {
			k = ++sz;
		//	x[k][0] = x[k][1] = z.x;
		//	y[k][0] = y[k][1] = z.y;
		//	size[k] = 1;
			tr[k].x[0] = tr[k].x[1] = z.x;
			tr[k].y[0] = tr[k].y[1] = z.y;
			tr[k].size = 1,	a[k] = z; return;
		}
		flag = t;
		if(cmp(z,a[k])){
		//	if(ch[k][0]) insert(ch[k][0],z,t^1);
		//	else insert(ch[k][1],z,t^1);
			if(tr[k].ch[0]) insert(tr[k].ch[0],z,t^1);
			else insert(tr[k].ch[1],z,t^1);
		}
		else {
		//	if(ch[k][1]) insert(ch[k][0],z,t^1);
		//	else insert(ch[k][1],z,t^1);
			if(tr[k].ch[1]) insert(tr[k].ch[1],z,t^1);
			else insert(tr[k].ch[0],z,t^1);
		}
		updata(k);
	//	int tt = max(size[ch[k][0]],size[ch[k][1]]);
		int tt = max(tr[tr[k].ch[0]].size,tr[tr[k].ch[1]].size);
		if(tt * 5 > tr[k].size * 4) rebuild(k);
	}

	int ask(int k,int x1,int y1,int x2,int y2){
		if(!k) return 0;
	//	if(x[k][0] >= x1 && y[k][0] >= y1 && x[k][1] <= x2 && y[k][1] <= y2) return size[k];
	//	if(x[k][1] < x1 || x[k][0] > x2 || y[k][1] < y1 || y[k][0] > y2) return 0;
	//	int ans = 0; ans += ask(ch[k][0],x1,y1,x2,y2); ans += ask(ch[k][1],x1,y1,x2,y2);
		if(tr[k].x[0] >= x1 && tr[k].y[0] >= y1 && tr[k].x[1] <= x2 && tr[k].y[1] <= y2) return tr[k].size;
		if(tr[k].x[1] < x1 || tr[k].x[0] > x2 || tr[k].y[1] < y1 || tr[k].y[0] > y2) return 0;
		int ans = 0; ans += ask(tr[k].ch[0],x1,y1,x2,y2); ans += ask(tr[k].ch[1],x1,y1,x2,y2);
		if(a[k].x >= x1 && a[k].x <= x2 && a[k].y >= y1 && a[k].y <= y2) ans ++;
		return ans;
	}
}T;

namespace seg{
	int sz,ch[Maxm][2];
	int root;

	void change(int &k,int l,int r,int pos,poi z){
		if(!k) k = ++sz;
		T.insert(T.root[k],z);
		if(l==r) return; int mid = (l+r) >> 1;
		if(pos <= mid) change(ch[k][0],l,mid,pos,z);
		else change(ch[k][1],mid+1,r,pos,z);
	}

	int ask(int k,int l,int r,int x1,int y1,int x2,int y2,int V){
		if(l==r) return l;
		int mid = (l+r) >> 1;
		int tmp = T.ask(T.root[ch[k][1]],x1,y1,x2,y2);
		if(V <= tmp) return ask(ch[k][1],mid+1,r,x1,y1,x2,y2,V);
		else return ask(ch[k][0],l,mid,x1,y1,x2,y2,V-tmp);
	}
}

using namespace seg;

const int inf = 1e9+1;

int main(){ //freopen("4605.in","r",stdin); freopen("4605.out","w",stdout);
	int n = read(), Q = read(),ans = 0,x,y,val,x1,y1,x2,y2;
	while(Q--){
		int opt = read();
		if(opt == 1){
			x = read()^ans, y = read()^ans,val = read()^ans;
			change(root,1,inf,val,poi(x,y));
		}
		else{
			x1 = read()^ans, y1  = read()^ans, x2 = read()^ans, y2 = read()^ans,val = read()^ans;
			if(T.ask(T.root[root],x1,y1,x2,y2) < val){
				puts("NAIVE!ORZzyz.");
				ans = 0;
			}
			else printf("%d\n",ans= ask(root,1,inf,x1,y1,x2,y2,val));
		}
	}
}	
