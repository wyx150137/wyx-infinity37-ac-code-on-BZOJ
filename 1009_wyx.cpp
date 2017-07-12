
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
using namespace std;

int son[N][10];
int fail[N*10];
bool end[N*10];
int root,sz,mod;
int n,m;

struct Matrix{
	int a[105][105];
	Matrix () {
		memset(a,0,sizeof a);
	}
	void init(){ int i;
		memset(a,0,sizeof a);
		for(i=1;i<=sz;++i)
			a[i][i] = 1;
	}
}a,ans;

Matrix & operator * (const Matrix &a,const Matrix &b){
	static Matrix res;
	memset(res.a,0,sizeof res.a);
	int i,j,k;
	for(i=1;i<=sz;++i)
		for(j=1;j<=sz;++j)
			for(k=1;k<=sz;++k)
				(res.a[i][j] += a.a[i][k]*b.a[k][j]%mod) %= mod;
	return res;
}

Matrix& pow(Matrix a,int b){
	static Matrix res;
	memset(res.a,0,sizeof res.a);
	res.init();
	for(;b;b>>=1,a=a*a)
		if(b&1)
			res = res*a;
	return res;
}

void insert(char *str){ int i,p = root;
	for(i=0;str[i];++i) {
		if(!son[p][str[i]-'0'])
			son[p][str[i]-'0'] = ++sz;
		p = son[p][str[i]-'0'];
	}
	end[p] = 1;
}

void init(){
	queue <int> q;
	register int i;
	for(i=0;i<10;++i)
		if(son[root][i])
			q.push(son[root][i]), fail[son[root][i]] = root;
		else son[root][i] = root;
	while(!q.empty()) {
		int tt = q.front(); q.pop();
		if(end[fail[tt]]) end[tt] = 1;
		for(i=0;i<10;++i) {
			if(!son[tt][i]) son[tt][i] = son[fail[tt]][i];
			else {
				fail[son[tt][i]] = son[fail[tt]][i];
				q.push(son[tt][i]);
			}
		}
	}
}

void build(){ int i,j;
	for(i=1;i<=sz;++i) if(!end[i])
		for(j=0;j<10;++j) if(son[i][j] && !end[son[i][j]])
				a.a[i][son[i][j]] ++;
}

char str[N];

int main(){ root = ++sz;
	cin >> n >> m >> mod; scanf("%s",str); 
	insert(str); init(); build();
	ans = pow(a,n);
	int tmp = 0; int i;
	for(i=1;i<=sz;++i) (tmp += ans.a[1][i]) %= mod;
	cout << tmp << endl;
}
