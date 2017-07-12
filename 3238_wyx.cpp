
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 500500+5;
using namespace std;
LL ans = 0;

struct sam {
	map<int,sam*> ch;
	vector <sam*> son;
	sam *fa;
	int depth,size;
	bool mark;
	sam (int x){
		fa = NULL;
		depth = x, size = 0;
		mark = false;
	}
}*root = new sam(0),*last = root;

void insert(int x){
	sam *p = last;
	sam *np = new sam(p->depth+1);
	last = np;
	for(;p&&!p->ch[x];p=p->fa) p->ch[x] = np;
	if(!p) np -> fa = root;
	else {
		sam *q = p->ch[x];
		if(p->depth+1==q->depth) np -> fa = q;
		else {
			sam *nq = new sam(p->depth+1);
			nq -> ch = q->ch;
			nq -> fa = q -> fa;
			q -> fa = nq;
			np -> fa = nq;
			for(; p && p->ch[x]==q; p=p->fa) p->ch[x] = nq;
		}
	}
	np -> size ++;
}

void DFS1(sam *x){
	map <int,sam*> :: iterator it;
	if(x->fa)  x -> fa -> son.push_back(x);
	x -> mark = 1;
	for(it = x->ch.begin(); it != x -> ch.end() ; it ++) 
		if(!it -> second -> mark) 
			DFS1(it -> second);
}

void DFS2(sam *p){
	vector <sam*> :: iterator it;
	for(it=p->son.begin();it!=p->son.end();it++){
		DFS2(*it);
		ans -= (LL)p->depth*p->size*((*it)->size<<1);
		p->size += (*it)->size;
	}
}

char str[N];

int main(){
	scanf("%s",str);
	int len = strlen(str);
	for(int i=len-1;~i;--i) insert(str[i]-'a');
	ans = (LL)(len-1)*len*(len+1)/2;
	DFS1(root); DFS2(root);
	cout << ans << endl;
}
