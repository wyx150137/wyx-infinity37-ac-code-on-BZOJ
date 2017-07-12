
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 8e5+5;
const double PI = 3.14159265358979323;
struct cp
{
	double x,y;
	cp(double _x=0,double _y=0):x(_x),y(_y){}
	friend cp operator +(const cp &a,const cp &b)
	{return cp(a.x+b.x,a.y+b.y);}
	friend cp operator -(const cp &a,const cp &b)
	{return cp(a.x-b.x,a.y-b.y);}
	friend cp operator *(const cp &a,const cp &b)
	{return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
}a[N],b[N],c[N];
const int R = 505;
char s[R][R],s2[R][R];
void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[t],a[i]);
		for(int j = (len>>1);(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<= len;i<<=1)
	{
		cp wn = cp(cos(2*PI*type/i),sin(2*PI*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp w(1,0),tmp;
			for(int k = 0;k<i>>1;w=w*wn,k++)
			{
				tmp = w*a[j+k+(i>>1)];
				a[j+k+(i>>1)] = a[j+k]-tmp;
				a[j+k] = a[j+k]+tmp;
			}
		}
	}
	if(type==-1)
		for(int i = 0;i<len;i++)
			a[i].x/=len;
}
int ans[N];
void conv(cp *a,cp *b,cp *c,int len)
{
	FFT(a,len,1),FFT(b,len,1);
	for(int i = 0;i<len;i++)c[i]=a[i]*b[i];
	FFT(c,len,-1);
}
int main()
{
	int row,col,h,w,len,l;
	scanf("%d%d",&row,&col);
	for(int i = 0;i<row;i++)scanf("%s",s[i]);
	for(len=1;len<=row*col*2+2;len<<=1);
	l = row*col-1;
	int cas,Ans;
	scanf("%d",&cas);
	for(int Cas = 1;Cas<=cas;Cas++)
	{
		Ans = 0;
		scanf("%d%d",&h,&w);
		for(int i = 0;i<h;i++)scanf("%s",s2[i]);
		for(int i = 0;i<row;i++)
			for(int j = 0;j<col;j++)a[i*col+j]=cp(s[i][j]=='G'?1:-1,0);
		for(int i = l+1;i<len;i++)a[i]=cp();
		for(int i = 0;i<len;i++)b[i]=cp();
		for(int i = 0;i<h;i++)
			for(int j = 0;j<w;j++)b[l-i*col-j]=cp(s2[i][j]=='G'?1:-1,0);
		for(int i = 0;i<len;i++)c[i]=cp();
		conv(a,b,c,len);
		for(int i = 0;i<len-l;i++)ans[i]=(int)(c[l+i].x+0.5);
		int px=0,py=0,t1=0,t2=0;
		for(int i = 0;i<= row-h;i++)for(int j = 0;j<= col-w;j++)
			if(ans[i*col+j]>Ans){Ans=ans[i*col+j],px=i,py=j;}
		for(int i = 0;i<h;i++)for(int j = 0;j<w;j++)
			if(s[px+i][py+j]==s2[i][j])
			{
				if(s2[i][j]=='G')t1++;else t2++;
			}
		printf("Case #%d: %d %d %d %d\n",Cas,px+1,py+1,t1,t2);
	}
	return 0;
}
