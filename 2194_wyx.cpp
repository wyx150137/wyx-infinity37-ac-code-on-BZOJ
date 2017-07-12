
#include <bits/stdc++.h>
using namespace std;
#define N 262144
#define pi M_PI
#define ll long long
typedef complex<double> E;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,L;
int R[N];
E a[N],b[N];
void fft(E *a,int f)
{
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));
		for(int j=0;j<n;j+=(i<<1))
		{
			E w(1,0);
			for(int k=0;k<i;k++,w*=wn)
			{
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)for(int i=0;i<n;i++)a[i]/=n;
}
int main()
{
	scanf("%d\n",&n);n--;
	for(int i=0;i<=n;i++)
	{
		a[i]=read();
		b[n-i]=read();
	}
	m=2*n;for(n=1;n<=m;n<<=1)L++;
	for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	fft(a,1);fft(b,1);
	for(int i=0;i<=n;i++)a[i]*=b[i];
	fft(a,-1);
	for(int i=m/2;i<=m;i++)printf("%d\n",(int)(a[i].real()+0.1));
	return 0;
}
