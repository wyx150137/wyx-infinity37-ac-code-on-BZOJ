
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200+50
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
char p[5]="WING";
int q[N],t[4];;
char ch[N],a[4][20][2];
int f[N][N][4];
bool dp(int l,int r,int k)
{
	if(l==r)
		return (ch[l]==p[k]);
	int &res=f[l][r][k];
	if(res!=-1)return res;
	for(int i=1;i<=t[k];i++)
		for(int j=l;j<=r-1;j++)
			if(dp(l,j,q[a[k][i][0]])&&dp(j+1,r,q[a[k][i][1]]))
				return res=1;
	return res=0;
}
int main()
{
	memset(f,-1,sizeof(f));
	q['W']=0;q['I']=1;q['N']=2;q['G']=3;
	for(int i=0;i<4;i++)t[i]=read();
	for(int i=0;i<4;i++)
		for(int j=1;j<=t[i];j++)scanf("%s",a[i][j]);
	scanf("%s",ch+1);
	int n=strlen(ch+1);
	bool flag=0;
	for(int i=0;i<4;i++)
		if(dp(1,n,i))flag=1,printf("%c",p[i]);
	if(!flag)puts("The name is wrong!");
	return 0;
}
