
#include <bits/stdc++.h>
const int mod = 1e9+7;
using namespace std;
typedef long long LL;
int len[105],cnt,n,m,l,ans;
char s[55][105];
inline void inc(int &x,int y) {x=(x+y)%mod;}

struct Trie{
	int ch[205][27],leef[205],fail[205];
	char s[205];
	void add() {
		scanf("%s",s+1); int n = strlen(s+1);
		int p = 0;
		for (int i=1;i<=n;i++) {
			int c = s[i] - 'a';
			if (!ch[p][c]) ch[p][c] = ++cnt;
			p = ch[p][c];
		}
		leef[p] = 1;
	}

	void set() {
		queue<int> q;
		for (int i=0;i<26;i++) if (ch[0][i])
			fail[ ch[0][i] ] = 0, q.push(ch[0][i]);

		while (!q.empty()) {
			int u=q.front(); q.pop();
			for (int i=0;i<26;i++) if (ch[u][i]) {
				int v = ch[u][i], t = fail[u];
				while (t && !ch[t][i]) t = fail[t];
				fail[v] = ch[t][i];
				leef[v] = leef[v] || leef[ fail[v] ];
				q.push(v);
			}
		}
	}

	int g(int u,char *s) {
		int len = strlen(s+1);
		for (int i=1;i<=len;i++) {
			int c = s[i]-'a';
			while (u && !ch[u][c]) u = fail[u];
			if (ch[u][c]) u = ch[u][c];
			if (leef[u]) return -1;
		}
		return u;
	}

}T;

namespace planA
{
	int F[105][5050];
	void solve() 
	{
		F[0][0] = 1;
		for (int _=0;_<l;_++)
			for (int i=0;i<=cnt;i++) if (F[_][i])
				for (int j=1;j<=n;j++) if (_+len[j]<=l) 
				{
					int ni = T.g(i,s[j]);
					if (ni == -1) continue;
					inc(F[_+len[j]][ni], F[_][i]);
				}
		for (int _=0;_<=cnt;_++) inc(ans, F[l][_]);
		cout << ans << endl;
	}
}

namespace planB
{

	struct Matrix{int a,d[205][205];}A,B,id;

	Matrix operator*(Matrix p1, Matrix p2) 
	{
		Matrix ret = id;ret.a = p1.a;
		for (int i=0;i<=p1.a;i++)
			for (int j=0;j<=p1.a;j++)
				for (int k=0;k<=p1.a;k++)
					inc(ret.d[i][j], 1LL*p1.d[i][k] * p2.d[k][j] % mod);
		return ret;
	}

	Matrix qp(Matrix A, int b) 
	{
		Matrix ret = id;
		ret.a = A.a;
		for (int i=0;i<=A.a;i++) ret.d[i][i] = 1;

		while (b) 
		{
			if (b&1) ret = ret * A;
			b >>= 1, A = A * A;
		}
		return ret;
	}

	void solve() 
	{
		int tp = cnt+1;
		A.a = B.a = 2*tp-1;
		A.d[0][0+tp] = 1;

		for (int i=0;i<=cnt;i++) B.d[i+tp][i] = 1;
		for (int i=0;i<=cnt;i++) 
		{
			for (int j=1;j<=n;j++) 
			{
				int ni = T.g(i,s[j]);
				if (ni == -1) continue;
				if (len[j] == 1)
					B.d[i+tp][ni+tp]++;
				else
					B.d[i][ni+tp]++;
			}
		}
		A = A * B;
		B = qp(B, l);
		A = A * B;
		for (int i=0;i<=cnt;i++) inc(ans, A.d[0][i]);
		cout << ans << endl;
	}
}

int main() 
{
	scanf("%d%d%d",&n,&m,&l);
	for (int i=1;i<=n;i++) 
		scanf("%s",s[i]+1), len[i] = strlen(s[i]+1);
	for (int i=1;i<=m;i++) 
		T.add();
	T.set();
	if (l <= 100) planA::solve(); else planB::solve();
	return 0;
}
