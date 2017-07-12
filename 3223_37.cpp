
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct S{
	S *son[2],*fa;
	int val,size,flag;
	S(){}
	void reverse()
	{
		flag ^=1;
		swap(son[0],son[1]);
	}
	void push_down()
	{
		if(flag==1)
		{
			son[0]->reverse();
			son[1]->reverse();
			flag = 0;
		}
	}
	void push_up()
	{
		size = son[0]->size+son[1]->size+1;
	}
	void Combine(S *a,bool dir) 
	{
        son[dir] = a;
        a->fa = this;
    }
    bool Check() {
        return fa->son[1] == this;
    }
}none,*nil = &none,*root = nil;
int n,m;
S* Newnode(S *now,int x)
{
	S *re = new S();
	re->val = x;
	re->son[0] = re->son[1]  = nil;
	re->size = 1; re->flag = 0;
	re->fa = now;
	return re;
}
S* build(int l,int r)
{
	if(l>r)return nil;
	int mid = (l+r)>>1;
	S *re = nil;
	re = Newnode(re,mid);
	re->Combine(build(l,mid - 1),false);
    re->Combine(build(mid + 1,r),true);
	re->push_up();
	return re;
}
void Rotate(S *a,bool dir)
{
    S *f = a->fa;
    f->push_down(),a->push_down();
    f->son[!dir] = a->son[dir];
    f->son[!dir]->fa = f;
    a->son[dir] = f;
    a->fa = f->fa;
    f->fa->son[f->Check()] = a;
    f->fa = a;
    f->push_up();
    if(root == f)   root = a;
}
 
void Splay(S *a,S *aim)
{
    while(a->fa != aim) {
        if(a->fa->fa == aim) 
            Rotate(a,!a->Check());
        else if(!a->fa->Check()) {
            if(!a->Check()) {
                Rotate(a->fa,true);
                Rotate(a,true);
            }
            else {
                Rotate(a,false);
                Rotate(a,true);
            }
        }
        else {
            if(a->Check()) {
                Rotate(a->fa,false);
                Rotate(a,false);
            }
            else {
                Rotate(a,true);
                Rotate(a,false);
            }
        }
    }
    a->push_up();
}
S* find_rank(S *now,int x)
{
	now->push_down();
	if(x<=now->son[0]->size)return find_rank(now->son[0],x);
	x = x-now->son[0]->size;
	if(x==1)return now;
	return find_rank(now->son[1],x-1);
}
void work(int x,int y)
{
	x++;y++;
	Splay(find_rank(root,x-1),nil);
	Splay(find_rank(root,y+1),root);
	root->son[1]->son[0]->reverse();
}
void print(S *now)
{
	if(now==nil)return ;
	now->push_down();
	print(now->son[0]);
	if(now->val&&now->val!=n+1)
		printf("%d ",now->val);
	print(now->son[1]);
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	root = build(0,n+1);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		work(x,y);
	}
	print(root);
	return 0;
}
