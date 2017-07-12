
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 500010;
int n,opt,top,num;
int l[40],r1[40],r2[40];
bool t;
double A,B,C,sum;
inline double sqr(double x){return x*x;}
struct Point
{
	double x,y;
}ins[N],newq[N],q1[N],q2[N];
inline bool cmp1(const Point &a,const Point &b)   
{return a.x==b.x?a.y>b.y:a.x<b.x;}
inline bool cmp2(const Point &a,const Point &b)   
{return a.x==b.x?a.y<b.y:a.x<b.x;}
void rebuild() 
{
	while (num&&top-l[num]==l[num]-l[num-1])    
		num--;
	l[++num]=top;
	int L=l[num-1]+1,R=L-1,cnt=0;
	for (int i=L;i<=top;i++)    
		newq[++cnt]=ins[i];
	sort(newq+1,newq+cnt+1,cmp1);
	for (int i=1;i<=cnt;i++)
	{
		while (R>L&&(q1[R].y-q1[R-1].y)*(newq[i].x-q1[R].x)<=(newq[i].y-q1[R].y)*(q1[R].x-q1[R-1].x))   
			R--;
		q1[++R]=newq[i];
	}
	r1[num]=R;
	R=L-1;
	sort(newq+1,newq+cnt+1,cmp2);
	for (int i=1;i<=cnt;i++)
	{
		while (R>L&&(q2[R].y-q2[R-1].y)*(newq[i].x-q2[R].x)>=(newq[i].y-q2[R].y)*(q2[R].x-q2[R-1].x))   
			R--;
		q2[++R]=newq[i];
	}
	r2[num]=R;
}
inline double calc(Point x) 
{return A*x.x+B*x.y;}
bool query1(int l,int r)
{
	int mid1,mid2,len;double s1,s2;
	while (l<=r)
	{
		len=(r-l)/3;
		mid1=l+len;
		mid2=r-len;
		s1=calc(q1[mid1]);
		s2=calc(q1[mid2]);
		if (s1<s2)  
			{if (s1<C)  return t=1;r=mid2-1;}
		else    
			{if (s2<C)  return t=1;l=mid1+1;}
	}
	return 0;
}
bool query2(int l,int r)
{
	int mid1,mid2,len;double s1,s2;
	while (l<=r)
	{
		len=(r-l)/3;
		mid1=l+len;
		mid2=r-len;
		s1=calc(q2[mid1]);
		s2=calc(q2[mid2]);
		if (s1<s2)  
			{if (s1<C)  return t=1;r=mid2-1;}
		else    
			{if (s2<C)  return t=1;l=mid1+1;}
	}
	return 0;
}
inline void Query()
{
	t=0;
	for (int i=1;i<=num;i++)
	{
		if (B<0)    
			query1(l[i-1]+1,r1[i]); 
		else    
			query2(l[i-1]+1,r2[i]);
		if (t)  return;
	}
}
int main()
{
	scanf("%d",&n);
	while (n--)
	{
		scanf("%d%lf%lf",&opt,&A,&B);A+=sum,B+=sum;
		if  (opt==0)    
			ins[++top].x=A,ins[top].y=B,rebuild();
		else    
		{
			if (!top)   
				{puts("No");continue;}
			C=sqr(A)+sqr(B);
			A*=2;B*=2;
			Query();
			puts(t?"No":"Yes");
			if (!t) sum++;
		}
	}
}
