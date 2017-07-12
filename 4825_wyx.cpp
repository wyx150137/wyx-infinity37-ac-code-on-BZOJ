
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define mp make_pair
#define fir first
#define sec second
using namespace std;
const int N = 1e5+5;
const int M = N << 2;
int n, m;


__attribute__((always_inline)) char getc()
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

__attribute__((always_inline)) int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc())) if(ch == EOF) return -1;
	for(D=ch-'0'; isdigit(ch=getc());) D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
#define RG register
namespace io
{
	const int MaxBuff = 1 << 20;
	const int Output = 1 << 24;
	char B[MaxBuff], *S = B, *T = B;
	//#define getc() getchar()
	#define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
	char Out[Output], *iter = Out;
	__attribute__((always_inline)) void flush()
	{
		fwrite(Out, 1, iter - Out, stdout);
		iter = Out;
	}
}

template<class Type> __attribute__((always_inline)) void print(RG Type x, RG char ch = '\n')
{
	using namespace io;
	if(!x) *iter++ = '0';
	else
	{
		if(x < 0) *iter++ = '-', x = -x;
		static int S2[100]; RG int t = 0;
		while(x) S2[++t] = x % 10, x /= 10;
		while(t) *iter++ = '0' + S2[t--];
	}
	*iter++ = ch;
}



struct data {
	int x, id;
	bool operator < (const data &z) const {
		return x < z.x;
	}
} b[N];

int tr[M], Min[M], Max[M], cnt[M], lazy[M];

inline void updata(int k) {
	tr[k] = min(tr[k<<1], tr[k<<1|1]);
	cnt[k] = cnt[k<<1] + cnt[k<<1|1];
	if(cnt[k<<1]) Min[k] = Min[k<<1]; 
	else Min[k] = Min[k<<1|1];
	if(cnt[k<<1|1]) Max[k] = Max[k<<1|1];
	else Max[k] = Max[k<<1];
}

inline void down(int k,int l,int r) {
	if(!lazy[k] || l == r)  return;
	int tmp = lazy[k]; lazy[k] = 0;
	if(cnt[k<<1]) {
		tr[k<<1] += tmp;
		Min[k<<1] += tmp;
		Max[k<<1] += tmp;
		lazy[k<<1] += tmp;
	}
	if(cnt[k<<1|1]) {
		tr[k<<1|1] += tmp;
		Min[k<<1|1] += tmp;
		Max[k<<1|1] += tmp;
		lazy[k<<1|1] += tmp;
	}
}

inline int find_pre(int k,int l,int r,int pos) {
	if(r == pos) return Max[k];
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos <= mid) return find_pre(k<<1,l,mid,pos);
	int tt = find_pre(k<<1|1,mid+1,r,pos);
	if(tt > 0) return tt;
	else return Max[k<<1];
}

inline int find_nxt(int k,int l,int r,int pos) {
	if(l == pos) return Min[k];
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos > mid) return find_nxt(k<<1|1,mid+1,r,pos);
	int tt = find_nxt(k<<1,l,mid,pos);
	if(tt > 0) return tt;
	else return Min[k<<1|1];
}

inline int get_pos_1(int k,int l,int r,int val) {
	if(l==r) return l;
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(cnt[k<<1] && tr[k<<1]<val) return get_pos_1(k<<1,l,mid,val);
	else return get_pos_1(k<<1|1,mid+1,r,val);
}

inline int get_pos_2(int k,int l,int r,int val) {
	if(l==r) return l;
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(cnt[k<<1|1] && tr[k<<1|1] < val) return get_pos_2(k<<1|1,mid+1,r,val);
	else return get_pos_2(k<<1,l,mid,val); 
}

inline pair<int,int> get_Min(int k,int l,int r) {
	if(l==r) return mp(tr[k], l);
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(cnt[k<<1]) return get_Min(k<<1,l,mid);
	else return get_Min(k<<1|1,mid+1,r);
}

inline pair<int,int> get_Max(int k,int l,int r) {
	if(l==r) return mp(tr[k], l);
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(cnt[k<<1|1]) return get_Max(k<<1|1,mid+1,r);
	else return get_Max(k<<1,l,mid);
}

inline void insert(int k,int l,int r,int pos,int val) {
	if(l==r) {
		tr[k] = Min[k] = Max[k] = val;
		cnt[k] = 1; return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos <= mid) insert(k<<1,l,mid,pos,val);
	else insert(k<<1|1,mid+1,r,pos,val);
	updata(k);
}

inline void del(int k,int l,int r,int pos)  {
	if(l==r) {
		tr[k] = n;
		Min[k] = Max[k] = 0;
		cnt[k] = 0;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos <= mid) del(k<<1,l,mid,pos);
	else del(k<<1|1,mid+1,r,pos);
	updata(k);
}

inline void change(int k,int l,int r,int x,int y,int val) {
	if(!cnt[k]) return;
	if(l==x && r==y) {
		Min[k] += val;
		Max[k] += val;
		tr[k] += val;
		lazy[k] += val;
		return;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
	updata(k);
}

int opt[N], depth, a[N];

int main() {
//	freopen("splay.in","r",stdin);
//	freopen("splay.out","w",stdout);
	m = read();
	for(int i=0;i<m;++i) {
		opt[i] = read();
		if(opt[i] == 1) b[++n].x = read(), b[n].id = n;
	}
	sort(b+1,b+n+1);
	pair <int,int> tt;
	for(int i=1;i<=n;++i) a[b[i].id] = i;
	++n; int cnt = 0;
	memset(tr, 0x3f, sizeof tr);
	for(int i=0;i<m;++i) {
		if(opt[i] == 1) {
			cnt ++;
			int tmp1 = find_pre(1, 0, n, a[cnt]);
			int tmp2 = find_nxt(1, 0, n, a[cnt]);
			insert(1, 0, n, a[cnt], max(tmp1,tmp2)+1);
			depth = max(tmp1, tmp2) + 1;
		}
		else if(opt[i] == 2 || opt[i] == 4) {
			tt = get_Min(1, 0, n);
			del(1, 0, n, tt.sec);
			int pos = get_pos_1(1, 0, n, tt.fir);
			change(1, 0, n, pos, n, 1);
			if(opt[i] == 4) 
				change(1, 0, n, 0, n, -1);
			else  insert(1, 0, n, tt.sec, 1);
			depth = tt.fir;
		} 
		else {
			tt = get_Max(1, 0, n);
			del(1, 0, n, tt.sec);
			int pos = get_pos_2(1, 0, n, tt.fir);
			change(1, 0, n, 0, pos, 1);
			if(opt[i] == 5) 
				change(1, 0, n, 0, n, -1);
			else  insert(1, 0, n, tt.sec, 1);	
			depth = tt.fir;
		}
		print(depth);
	}
	io::flush();
}

