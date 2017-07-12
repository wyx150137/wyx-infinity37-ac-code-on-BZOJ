
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define s(no,i) s[no][i]-'a'
typedef long double ld;
const int P = 81;
int n,L,k;
struct Matrix
{
	int w,h;
	ld d[P][P];
	Matrix(){}
	Matrix(int _w,int _h):w(_w),h(_h){}

	void operator*=(const Matrix &S)
	{
		Matrix res(w,S.h);
		for(int i = 0;i<res.w;i++)
			for(int j = 0;j<res.h;j++)
			{
				res.d[i][j] = 0;
				for(int k = 0;k<h;k++)
					res.d[i][j]+=d[i][k]*S.d[k][j];
			}
		*this = res;
	}
};
int len[6];
char s[6][20];
bool cover(int a,int b)
{
	if(len[a]<len[b])return false;
	for(int i = 1;i+len[b]-1<=len[a];i++)
	{
		bool flag = true;
		for(int j = 1;j<= len[b];j++)
			if(s[a][i+j-1]!=s[b][j])
				{flag=false;break;}
		if(flag)return true;
	}
	return false;
}
struct AC_Machine
{
	int ch[P][26],fail[P];
	int cnt,q[P],h,t;
	bool end[P];
	void insert(int no)
	{
		int now = 0,i = 1;
		while(s[no][i])
		{
			if(!ch[now][s(no,i)])ch[now][s(no,i)] = ++cnt;
			now = ch[now][s(no,i)];
			i++;
		}
		end[now]=true;
	}
	void build()
	{
		h = 0,t = -1;
		for(int i = 0;i<k;i++)
			if(ch[0][i])
				q[++t] = ch[0][i];
		while(h<=t)
		{
			int x=q[h++];
			for(int i = 0;i<k;i++)
			{
				int j = ch[x][i];
				if(j)
				{
					q[++t] = j;
					int r = fail[x];
					while(r&&!ch[r][i])r = fail[r];
					fail[j] = ch[r][i];
					end[j]|=end[fail[j]];
				}
				else ch[x][i] = ch[fail[x]][i];
			}
		}
	}
}AC;
bool covered[6];
int main()
{
	scanf("%d%d%d",&n,&L,&k);
	for(int i = 1;i<= n;i++)
		scanf("%s",s[i]+1);
	for(int i = 1;i<= n;i++)
		len[i] = strlen(s[i]+1);
	for(int i = 1;i<= n;i++)
		for(int j = i+1;j<= n;j++)
			if(cover(i,j))
				covered[i] = true;
	bool a_c = true;
	for(int i = 1;i<= n;i++)
		if(!covered[i])a_c = false;
	if(a_c)covered[1] = false;
	AC.cnt = 0;
	for(int i = 1;i<= n;i++)
		if(!covered[i])
			AC.insert(i);
	AC.build();
	int cnt = AC.cnt;
	Matrix res(1,cnt+2);
	res.d[0][0] = 1;
	Matrix add(cnt+2,cnt+2);add.d[cnt+1][cnt+1] = 1;
	for(int i = 0;i<=cnt;i++)
		for(int j = 0;j<k;j++)
			if(AC.end[AC.ch[i][j]])add.d[i][cnt+1]+=(ld)1/(ld)k,add.d[i][0]+=(ld)1/(ld)k;
			else add.d[i][AC.ch[i][j]]+=(ld)1/(ld)k;
	for(;L;L>>=1,add*=add)if(L&1)res*=add;
	double ans = res.d[0][cnt+1];
	printf("%.6lf\n",ans);
	return 0;
}
