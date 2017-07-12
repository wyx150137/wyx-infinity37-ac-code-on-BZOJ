
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+205;
#define stack_size (20001000) 
int stack[stack_size],bak; 
using namespace std;

struct sam{
	sam *son[27],*fa;
	int depth,size;
	bool mark;
	vector <sam*> V;
	sam (int _){
		depth = _, size = 0, mark = false, fa = NULL;
		memset(son,0,sizeof son);
	}
}*root = new sam(0), *last = root, *p, *np, *q, *nq;

void insert(int x){
	p = last; np = new sam(p->depth+1);
	last = np; np -> size ++;
	while(p && !p->son[x]) p -> son[x] = np, p = p -> fa;
	if(!p) np -> fa = root;
	else{
		q = p -> son[x];
		if(p->depth+1 == q->depth) np -> fa = q;
		else{
			nq = new sam(p->depth+1);
			nq -> fa = q -> fa;
			q -> fa = nq;
			np -> fa = nq;
			memcpy(nq->son,q->son,sizeof nq->son);
			while(p && p->son[x] == q){
				p -> son[x] = nq;
				p = p->fa;
			}
		}
	}

}

void DFS1(sam *p){
	if(p->fa)
		p->fa->V.push_back(p);
	p -> mark = 1;
	for(int i=0;i<27;++i){
		if(p->son[i] && !p->son[i]->mark)
			DFS1(p->son[i]);
	}
}

void DFS2(sam *p){
	vector <sam*> :: iterator it;
	for(it = p->V.begin(); it != p->V.end(); it ++)
		DFS2(*it), p->size += (*it)->size;
}

char str[N];
int tot;/*
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
    DFS1(root); DFS2(root);   
    __asm__ __volatile__    
    (    
        "mov %0,%%esp\n"  
        :    
        :"g"(bak)    
        :    
    );    
}  */
int main(){ //freopen("dic.in","r",stdin); freopen("dic.out","w",stdout);
	int n; cin >> n; tot = -1;
	for(int i=1;i<=n;++i){
		char ch = getchar();
		while(ch < 'a' || ch > 'z') ch = getchar();
		while(ch >='a' && ch <='z') {
			str[++tot] = ch;
			ch = getchar();
		}
		str[++tot] = 'z'+1;
	}
	tot ++;
	for(int i=0;i<tot;++i) insert(str[i]-'a');
	DFS1(root); DFS2(root);
//	CallDFS();
	int o = 0;
	for(int i=1,j;i<=n;++i){
		p = root;
		for(j=o;str[j] != 'z' + 1 && j < tot; ++ j) p = p->son[str[j]-'a'];
		o = j + 1;
		printf("%d\n",p->size);
	}
}
