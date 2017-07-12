
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int Max = 1e6+1e5;
int c[2][Max];
int a[N],ans[N],n;
inline int Get_bit(int x,int y)
{
	return (x>>(y-1))&1;
}
void Update(int id,int x,int y)
{
	for(int i = x;i<Max;i+=i&(-i))
		c[id][i]+=y;
}
int Getans(int id,int x)
{
	int res = 0;
	for(int i = x;i;i-=i&(-i))
		res+=c[id][i];
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		a[i]+=a[i-1];
	}
	for(int i = 1,ba = 1;i<= 20;i++)
	{
		memset(c,0,sizeof(c));
		for(int j = 1;j<= n;j++)
		{
			ans[i]+=Getans(Get_bit(a[j],i),ba+1)-Getans(Get_bit(a[j],i),a[j]%ba+1)
			+Getans(!Get_bit(a[j],i),a[j]%ba+1)+Get_bit(a[j],i);
			Update(Get_bit(a[j],i),a[j]%ba+1,1);
		}
		ba = ba<<1;
	}
	int Ans = 0;
	for(int i = 1,ba = 1;i<= 20;i++,ba<<=1)Ans+=(ans[i]&1)*ba;
	printf("%d\n",Ans);
	return 0;
}
