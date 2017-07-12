
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 10000000+5;
const int M = 7e4;
const int inf = M;
using namespace std;

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,m,sz,ans,root;
int rt[M+5],dfn[M+5],val[M+5],ls[M+5],rs[M+5];
queue <int> rec;
vector <int> p,t;

struct seg{
	int l,r,sum;
}a[N];

int newnode(){
	if(!rec.empty()) {
		int tt = rec.front();
		rec.pop(); return tt;
	}
	else return ++sz;
}

void recy(int &x){
	if(!x) return;
	rec.push(x);
	recy(a[x].l);
	recy(a[x].r);
	a[x].sum = a[x].l = a[x].r = 0 ; x = 0;
}

void insert(int &k,int l,int r,int val,int f){
	if(!k) k = newnode();
	if(l==r){
		a[k].sum += f;
		return;
	}
	int mid = (l+r) >> 1;
	if(val <= mid) insert(a[k].l,l,mid,val,f);
	else insert(a[k].r,mid+1,r,val,f);
	a[k].sum = a[a[k].l].sum + a[a[k].r].sum;
	if(!a[k].sum) recy(k);
}

void build(int &k,int l,int r){
	if(l>r) return;
	int mid = (l+r) >> 1;
	k = dfn[mid];
	for(int i=l;i<=r;++i) insert(rt[k],0,inf,val[dfn[i]],1);
	if(l==r) return; 
	build(ls[k],l,mid-1);
	build(rs[k],mid+1,r);
}

void del(int &x){
	if(!x) return; 
	recy(rt[x]);
	del(ls[x]);  
	p.push_back(x);  
	del(rs[x]);
	x = 0;
}

void rebuild(int &x){
	del(x); int tmp1 = p.size();
	for(int i=1;i<=tmp1;++i) dfn[i] =p[i-1];
	build(x,1,tmp1); p.clear();
}

int modify(int k,int x,int _val){
	insert(rt[k],0,inf,_val,1);
	int tt; int L = a[rt[ls[k]]].sum;
	if(L+1 == x){
		tt = val[k];
		val[k] = _val;
	}
	else if(L >= x) tt = modify(ls[k],x,_val);
	else tt = modify(rs[k],x-L-1,_val);
	insert(rt[k],0,inf,tt,-1);
	return tt;
}

void ask(int k,int l,int r){
	int L = a[rt[ls[k]]].sum, R = a[rt[k]].sum;
	if(l==1 && r == R) {
		t.push_back(rt[k]); return;
	}
	if(l <= L + 1 && r >= L+1) p.push_back(val[k]);
	if(r <= L) ask(ls[k],l,r);
	else if(l > L+1) ask(rs[k],l-L-1,r-L-1);
	else {
		if(l <= L) ask(ls[k],l,L);
		if(R > L + 1) ask(rs[k],1,r-L-1);
	}
}

int Ask(int L,int R,int K){
	ask(root,L,R); K --;
	int l = 0, r = inf;
	int tmp1 = t.size(),tmp2 = p.size();
	while(l < r){
		int mid = (l+r) >> 1, sum = 0;
		for(int i=0;i<tmp1;++i) sum += a[a[t[i]].l].sum;
		for(int i=0;i<tmp2;++i) if(p[i] >= l && p[i] <= mid) sum ++;
		if(K < sum){
			for(int i=0;i<tmp1;++i) t[i] = a[t[i]].l;
			r = mid;
		}
		else{
			for(int i=0;i<tmp1;++i) t[i] = a[t[i]].r;
			l = mid + 1, K -= sum;
		}
	} 
	t.clear(); p.clear();
	return l;
}

int tmp;

void insert(int &k,int x,int _val){
	if(!k) {
		k = ++n;
		insert(rt[k],0,inf,_val,1);
		val[k] = _val; return;
	}
	insert(rt[k],0,inf,_val,1);
	int L = a[rt[ls[k]]].sum;
	if(L >= x) insert(ls[k],x,_val);
	else insert(rs[k],x-L-1,_val);
	int tt = max(a[rt[ls[k]]].sum,a[rt[rs[k]]].sum);
	if(tt * 5 < a[rt[k]].sum * 4){
		if(tmp){
			if(ls[k] == tmp) rebuild(ls[k]);
			else rebuild(rs[k]);
			tmp = 0;
		}
	}
	else tmp = k;
}

int main(){// freopen("kthflea1.in","r",stdin);
//	freopen("tt.out","w",stdout);
	n = read();
	for(int i=1;i<=n;++i) val[i] = read();
	for(int i=1;i<=n;++i) dfn[i] = i;
	build(root,1,n);
	m = read();
	char str[4];
	int x, y, K;
	int lastans = 0;
	while(m--){
		scanf("%s",str);
		x = read()^lastans, y = read()^lastans;
		if(str[0] == 'Q'){
			K = read() ^ lastans;
			printf("%d\n",lastans = Ask(x,y,K));
		}
		else if(str[0] == 'M')
			modify(root,x,y);
		else {
				tmp = 0;
				insert(root,x-1,y);
				if(tmp){
					tmp = 0;
					rebuild(root);
			}
		}
	}
}
