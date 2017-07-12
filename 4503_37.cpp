
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
const double pi = 3.14159265358979323;
#define N 300005
using namespace std;

struct cpx{ double r,i; }a[N],b[N],c[N]; int n1,n2,m,f[N],g[N],pos[N];
char s1[N],s2[N];
cpx operator +(cpx x,cpx y){ x.r+=y.r; x.i+=y.i; return x; }
cpx operator -(cpx x,cpx y){ x.r-=y.r; x.i-=y.i; return x; }
cpx operator *(cpx x,cpx y){
	cpx t; t.r=x.r*y.r-x.i*y.i; t.i=x.r*y.i+x.i*y.r; return t;
}
void dft(cpx *a,int flag){
	int i,j,k; cpx w,wn,u,v;
	if (flag>0) for (i=0; i<m; i++) a[i].i=0;
	for (k=1; k<m; k<<=1){
		wn.r=cos(pi*flag/k); wn.i=sin(pi*flag/k);
		for (i=0; i<m; i+=(k<<1)){
			w.r=1; w.i=0;
			for (j=i; j<i+k; j++){
				u=a[j]; v=a[j+k]*w;
				a[j]=u+v; a[j+k]=u-v; w=w*wn;
			}
		}
	}
	if (flag<0) for (i=0; i<m; i++) a[i].r/=m;
}
int main(){
	scanf("%s%s",s1+1,s2+1); int i,j,k,cnt=0;
	n1=strlen(s1+1); n2=strlen(s2+1);
	for (i=1; i<=n1; i++) f[i]=s1[i]-'a'+1;
	for (i=1; i<=n2; i++) g[n2-i+1]=(s2[i]=='?')?0:s2[i]-'a'+1;
	m=n1+n2+1;
	for (i=1; i<m; i<<=1) cnt++; m=i;
	for (i=0; i<m; i++)
		for (k=i,j=1; j<=cnt; j++,k>>=1) pos[i]=pos[i]<<1|(k&1);
	for (i=0; i<m; i++){ a[pos[i]].r=f[i]*f[i]; b[pos[i]].r=g[i]; }
	dft(a,1); dft(b,1);
	for (i=0; i<m; i++) c[pos[i]]=a[i]*b[i];
	for (i=0; i<m; i++){ a[pos[i]].r=1;  b[pos[i]].r=g[i]*g[i]*g[i]; }
	dft(a,1); dft(b,1);
	for (i=0; i<m; i++) c[pos[i]]=c[pos[i]]+a[i]*b[i];
	for (i=0; i<m; i++){ a[pos[i]].r=f[i]*2; b[pos[i]].r=g[i]*g[i]; }
	dft(a,1); dft(b,1);
	for (i=0; i<m; i++) c[pos[i]]=c[pos[i]]-a[i]*b[i];
	dft(c,-1); cnt=0;/*
	for(int i = 0;i<m;i++)
		printf("%.2f ",c[i].r);*/
	for (i=1; i<=n1-n2+1; i++) if (c[i+n2].r<0.5) f[++cnt]=i;
	printf("%d\n",cnt);
	for (i=1; i<=cnt; i++) printf("%d\n",f[i]-1);
	return 0;
}
