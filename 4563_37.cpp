
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int B = 2000;
const int mod = 10000;
struct BigNum
{
	int d[B],len;
	BigNum(){memset(d,0,sizeof(d));len = 1;}
	BigNum(int x)
	{
		memset(d,0,sizeof(d));
		len = 1;
		while(x)d[len] = x%mod,x/=mod,len++;
		len--;
	}
	void print()
	{
		printf("%d",d[len]);
		for(int i = len-1;i;i--)
			printf("%04d",d[i]);
	}
	void operator +=(const BigNum &s)
	{
		len = max(len,s.len);
		for(int i = 1;i<=len;i++)
		{
			d[i] = d[i]+s.d[i];
			if(d[i]>=mod)
				d[i+1]++,d[i]%=mod;
		}
		if(d[len+1])len++;
	}
	friend BigNum operator +(const BigNum &a,const BigNum &b)
	{
		BigNum res = a;res+=b;
		return res;
	}
	void operator *=(const int &s)
	{
		int num = 0;
		for(int i = 1;i<= len;i++)
		{
			num = num+d[i]*s;
			d[i] = num%mod;
			num/=mod;
		}
		if(num)d[++len] = num;
	}
}f[205];
int main()
{
	f[0] = BigNum(1);f[1] = BigNum(0);
	int n;
	scanf("%d",&n);
	for(int i = 2;i<= n;i++)
		f[i] = f[i-1]+f[i-2],f[i]*=(i-1);
	f[n].print();
	return 0;
}
