
#include <bits/stdc++.h>
typedef std::vector<int> pol;
typedef long long LL;
typedef unsigned long long u64;
const int P=1000003;
int max(int a,int b) {return a>b?a:b;}
template<int p>
LL pw(int a,int n) {
	if(n<0)n+=p-1;
	LL v=1;
	for(;n;n>>=1,a=LL(a)*a%p)if(n&1)v=v*a%p;
	return v;
}
int N,K,r[1<<20|111];
typedef double ld;
struct cplx {
	ld a,b;
	cplx(ld _x=0,ld _y=0):a(_x),b(_y) {}
	cplx operator+(cplx w) {return cplx(a+w.a,b+w.b);}
	cplx operator-(cplx w) {return cplx(a-w.a,b-w.b);}
	cplx operator*(cplx w) {return cplx(a*w.a-b*w.b,a*w.b+b*w.a);}
}A[1<<20|111],B[1<<20|111],*Es[2][20],C[1<<20|111],D[1<<20|111];
void pre(int n) {
	for(N=2,K=0;N<n;N<<=1,++K);
	for(int i=1;i<N;++i)r[i]=r[i>>1]>>1|(i&1)<<K;
	memset(A,0,sizeof(cplx)* N);
	memset(B,0,sizeof(cplx)* N);
	memset(C,0,sizeof(cplx)* N);
	memset(D,0,sizeof(cplx)* N);
}
const ld pi=acos(-1);
void FFT(cplx*a,int t) {
	for(int i=1;i<N;++i)if(i<r[i])std::swap(a[i],a[r[i]]);
	for(int i=1,z=0;i<N;i<<=1,++z) {
		if(!Es[t==1][z]) {
			cplx*E=Es[t==1][z]=new cplx[i];
			for(int j=0;j<i;++j)E[j]=cplx(cos(j*pi/i),t*sin(j*pi/i));
		}
		cplx*E=Es[t==1][z];
		for(int j=0;j<N;j+=i<<1) {
			cplx*b=a+j,*c=b+i;
			for(int k=0;k<i;++k) {
				cplx x=b[k],y=c[k]*E[k];
				b[k]=x+y;
				c[k]=x-y;
			}
		}
	}
	if(t==-1)for(int i=0;i<N;++i)a[i].a/=N;
}
void mul(cplx*a,cplx*b) {
	for(int i=0;i<N;++i)a[i]=a[i]*b[i];
}
void mov(const pol&x,cplx*a) {
	for(int i=0;i<x.size();++i)a[i].a=x[i];
}
void mov(cplx*a,const pol&_x) {
	pol&x=const_cast<pol&>(_x);
	for(int i=0;i<x.size();++i)x[i]=LL(a[i].a+0.49)%P;
}
void mov(const pol&x,int*a) {
	memcpy(a,x.data(),x.size()*sizeof(int));
}
void mov(int*a,const pol&_x) {
	pol&x=const_cast<pol&>(_x);
	memcpy(x.data(),a,x.size()*sizeof(int));
}
void chk(pol&w) {
	int p=w.size();
	while(p&&!w[p-1])--p;
	w.resize(p);
}
void rev(pol&w) {
	std::reverse(w.data(),w.data()+w.size());
}
u64 _c[1007];
pol operator*(const pol&a,const pol&b) {
	pol c(a.size()+b.size()-1);
	if(c.size()<=600) {
		const int*as=a.data(),ap=a.size(),*bs=b.data(),bp=b.size();
		int*cs=c.data();
		for(int i=0;i<c.size();++i)_c[i]=0;
		for(int i=0;i<ap;++i)for(int j=0;j<bp;++j)_c[i+j]+=u64(as[i])*bs[j];
		for(int i=0;i<c.size();++i)cs[i]=_c[i]%P;
	}else if(c.size()<=5000) {
		pre(c.size());
		mov(a,A),mov(b,B);
		FFT(A,1),FFT(B,1);
		mul(A,B);
		FFT(A,-1);
		mov(A,c);
	}else {
		pre(c.size());
		for(int i=0;i<a.size();++i) {
			A[i]=a[i]>>10;
			B[i]=a[i]&1023;
		}
		for(int i=0;i<b.size();++i) {
			C[i]=b[i]>>10;
			D[i]=b[i]&1023;
		}
		FFT(A,1);FFT(B,1);FFT(C,1);FFT(D,1);
		for(int i=0;i<N;++i) {
			cplx v1=A[i]*C[i];
			cplx v2=A[i]*D[i]+B[i]*C[i];
			cplx v3=B[i]*D[i];
			A[i]=v1;
			B[i]=v2;
			C[i]=v3;
		}
		FFT(A,-1);FFT(B,-1);FFT(C,-1);
		for(int i=0;i<c.size();++i) {
			c[i]=((LL(A[i].a+0.49)<<20)+(LL(B[i].a+0.49)<<10)+LL(C[i].a+0.49))%P;
		}
	}
	chk(c);
	return c;
}
pol operator*(const pol&w,int x) {
	pol a(w);
	for(int i=0;i<a.size();++i)a[i]=LL(a[i])*x%P;
	return a;
}
pol operator-(const pol&a,const pol&b) {
	pol c(max(a.size(),b.size()));
	mov(a,c.data());
	for(int i=0;i<b.size();++i)c[i]=(c[i]-b[i]+P)%P;
	chk(c);
	return c;
}
pol inv(pol a) {
	if(a.size()==1) {
		a.resize(1);
		a[0]=pw<P>(a[0],P-2);
		return a;
	}
	pol b=inv(pol(a.data(),a.data()+(a.size()-1)/2+1));
	pol c=b*b*a;
	c=b*2-c;
	c.resize(a.size());
	return c;
}
pol operator/(pol a,pol b) {
	chk(a),chk(b);
	rev(a),rev(b);
	int sz=a.size()-b.size()+1;
	b.resize(sz);
	pol c=a*inv(b);
	c.resize(sz);
	rev(c);
	chk(c);
	return c;
}
pol operator%(const pol&a,const pol&b) {
	if(a.size()<b.size())return a;
	return a-a/b*b;
}
int cal(const pol&w,LL x) {
	int y=0;
	for(int p=w.size()-1;p>=0;--p)y=(y*x+w[p])%P;
	return y;
}
int n,b,c,d,e,a[67777],as[67777];
struct Q {int x,id;}qs[67777];
bool operator<(Q a,Q b) {return a.x<b.x;}
pol tr[67777*4];
void calc0(int w,int L,int R) {
	if(L==R) {
		tr[w]=pol(2);
		tr[w][1]=1;
		tr[w][0]=(P-qs[L].x)%P;
		return;
	}
	int M=(L+R)/2;
	calc0(w<<1,L,M);
	calc0(w<<1^1,M+1,R);
	tr[w]=tr[w<<1]*tr[w<<1^1];
}
void calc1(const pol&a,int w,int L,int R) {
	if(R-L<=600) {
		for(int i=L;i<=R;++i)as[qs[i].id]=cal(a,qs[i].x);
		return;
	}
	int M=(L+R)/2;
	calc1(a%tr[w<<1],w<<1,L,M);
	calc1(a%tr[w<<1^1],w<<1^1,M+1,R);
}
int main() {
	scanf("%d%d%d%d%d",&n,&b,&c,&d,&e);
	for(int i=0;i<n;++i)scanf("%d",a+i);
	for(int i=0;i<n;++i) {
		qs[i].x=(b*pw<P>(c,4*i)+d*pw<P>(c,2*i)+e)%P;
		qs[i].id=i;
	}
	std::sort(qs,qs+n);
	tr[0]=pol(n);
	mov(a,tr[0]);
	calc0(1,0,n-1);
	calc1(tr[0],1,0,n-1);
	for(int i=0;i<n;++i)printf("%d\n",(as[i]+P)%P);
	return 0;
}
﻿
