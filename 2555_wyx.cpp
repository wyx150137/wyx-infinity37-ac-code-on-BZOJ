
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3e6+5;
int mask;
char s[3000005];
string chars;

int root;

void Gets(int mask) {
	scanf("%s",s);
	chars=s;
	for (int j=0;j<chars.length();j++) {
		mask=(mask*131+j)%chars.length();
		char t=chars[j];
		chars[j]=chars[mask];
		chars[mask]=t;
	}
}

namespace lct {
	bool root[N];
	int ch[N][2], lazy[N], tr[N], fa[N];

	inline void add(int x,int val) {
		tr[x] += val;
		lazy[x] += val;
	//	cout << x << ' ' << val << endl;
	}

	inline void push_down(int k) {
		if(!lazy[k]) return;
		if(ch[k][0]) add(ch[k][0], lazy[k]);
		if(ch[k][1]) add(ch[k][1], lazy[k]);
		lazy[k] = 0;
	}

	inline void down(int x) {
		static int stack[N];
		int top=0; stack[++top]=x;
		for(int i=x;!root[i];i=fa[i]) stack[++top]=fa[i];
		for(int i=top;i;i--) push_down(stack[i]);
	}

	inline void rotate(int x) {
		int y = fa[x], z = ch[y][1] == x;
		ch[y][z] = ch[x][!z]; fa[ch[y][z]] = y;
		ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
		if(root[y]) swap(root[x], root[y]);
		else ch[fa[x]][ch[fa[x]][1] == y] = x;
	}

	inline void splay(int x) {
		down(x);
		while(!root[x]) {
			int y = fa[x], z = fa[y];
			if(root[y]) rotate(x);
			else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
			else rotate(x), rotate(x);
		}
	}

	inline void access(int x) {
		int y = 0;
		while(x) {
			splay(x);
			root[ch[x][1]] = 1;
			root[ch[x][1] = y] = 0;
			y = x;
			x = fa[x];
		}
	}

	inline void link(int x,int y) {
		access(y);
		splay(y);
		fa[x] = y;
		add(y, tr[x]);
	}

	inline void cut(int x) {
		access(x);
		splay(x);
		if(ch[x][0]) {
			add(ch[x][0], -tr[x]);
			fa[ch[x][0]] = 0;
			root[ch[x][0]] = 1;
			ch[x][0] = 0;
		}
	}

	inline void init() {
		for(int i=0;i<N;++i) root[i] = 1;
	}
}

namespace sam {
	int son[N][26], fa[N], depth[N], sz;

	inline int newnode(int _) {
		depth[++sz] = _;
		return sz;
	}

	int p, np, q, nq, last;

	inline void insert(int x) {
		p = last; last = np = newnode(depth[p]+1); 
		lct::tr[np] = 1;

		while(p && !son[p][x]) {
			son[p][x] = np;
			p = fa[p];
		}
		if(!p) {
			lct::link(np, root);
			fa[np] = root;
			return;
		}
		else {
			q = son[p][x];
			if(depth[q] == depth[p] + 1)  {
				fa[np] = q;
				lct::link(np, q);
			}
			else {
				nq = newnode(depth[p] + 1); 
				memcpy(son[nq], son[q], sizeof son[q]);
				lct::link(nq, fa[q]); fa[nq] = fa[q];
				lct::cut(q);
				lct::link(q, nq); fa[q] = nq;
				lct::link(np,nq); fa[np] = nq;
				while(p && son[p][x] == q) {
					son[p][x] = nq;
					p = fa[p];
				}
			}
		}
	}
	
	int pos[50];

	inline int ask () {
		Gets(mask);
		int p = root;
		for(int i = 0; i < chars.length(); ++i) {
			if(!son[p][chars[i] - 'A']) return 0;
			p = son[p][chars[i] - 'A'] ;
		}
		lct::splay(p);
		return lct::tr[p];
	}

	void build() {
		scanf("%s",s);
		root = last = newnode(0);
		int l = strlen(s);
		for(int i = 0; i < l ; i++)
			insert(s[i]-'A');
	}
	void add() {
		Gets(mask);
		int l = chars.length();
		for(int i = 0; i < l ; i++)
			insert(chars[i]-'A');
	}
	
	void show() {
		for(int i=2;i<=sz;++i)
			cout << fa[i] << " " << i << endl;
	}
}

int main() {
//	freopen("tt.in","r",stdin);
	lct::init();
	int Q;
	scanf("%d",&Q);
	sam::build();
	while(Q--) {
		scanf("%s",s);
		if(s[0]=='A')sam::add();
		else {
			int ans = sam::ask();
			printf("%d\n", ans);
			mask ^= ans;
		}
	}
	return 0;
}
