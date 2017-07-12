
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 6000+5;
const int mod = 10007;
struct Trie{
	Trie *son[26],*fail;
	bool en;
}*root,tr[6000+5],*cnt=tr,*p;

int n,m,ans;

int F[6000+5][110];

void insert(char *str){
	p = root;
	for(int i=0;str[i];++i){
		if(!p->son[str[i]-'A']) p->son[str[i]-'A'] = cnt++;
		p = p->son[str[i]-'A'];
	}
	p -> en = 1;
}

void build(){
	queue <Trie*> q;
	for(int i=0;i<26;++i)
		if(root -> son[i])
			root -> son[i] -> fail = root, q.push(root->son[i]);
		else root -> son[i] = root;
	while(!q.empty()){
		p = q.front(); q.pop();
		for(int i=0;i<26;++i)
			if(p->son[i]){
				p->son[i]->fail = p->fail->son[i];
				p->son[i]-> en |= p->son[i]->fail->en;
				q.push(p->son[i]);
			}
			else
				p->son[i] = p->fail->son[i];
	}
}

char str[N];

int main(){
	cin >> n >> m;
	root = cnt ++;
	for(int i=1;i<=n;++i) 
		scanf("%s",str), insert(str);
	build();
	F[0][0] = 1;
	for(int i=0;i<m;++i)
		for(int j=0;j<cnt-tr;++j)
			if(!tr[j].en)
				for(int k=0;k<26;++k)
					(F[tr[j].son[k]-tr][i+1] += F[j][i]) %= mod;
	ans = 1;
	for(int i=1;i<=m;++i) (ans *= 26) %= mod;
	for(int j=0;j<cnt-tr;++j)
		if(!tr[j].en)
			(ans += mod - F[j][m]) %= mod;
	cout << ans << endl;
}
