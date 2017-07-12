
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
const int SED = 37;
int MOD[2] = {23333333,99824435};
int pre[2][N],pow[2][N],n;
char s[N];
void init()
{
	for(int i = 1;i<= n;i++)
	{
		pre[0][i] = ((LL)pre[0][i-1]*SED+s[i]-'a')%MOD[0];
		pre[1][i] = ((LL)pre[1][i-1]*SED+s[i]-'a')%MOD[1];
	}
	pow[0][0] = pow[1][0] = 1;
	for(int i = 1;i<= n;i++)
	{
		pow[0][i] = ((LL)pow[0][i-1]*SED)%MOD[0];
		pow[1][i] = ((LL)pow[1][i-1]*SED)%MOD[1];	
	}
}
int gethash(int l,int r,int no)
{
	int lth = r-l+1;
	return (pre[no][r]-(LL)pre[no][l-1]*pow[no][lth]%MOD[no]+MOD[no])%MOD[no];
}
bool check(int l1,int r1,int l2,int r2)
{
	return gethash(l1,r1,0)==gethash(l2,r2,0)&&gethash(l1,r1,1)==gethash(l2,r2,1);
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	init();
	int ans = 0;
	for(int i = n>>1,j = 0;i>0;i--,j = min(j+2,n/2-i))
		if(check(1,i,n-i+1,n))
			for(;~j;j--)
				if(check(i+1,i+j,n-i-j+1,n-i))
				{
					ans = max(ans,i+j);
					break;
				}
	printf("%d\n",ans);
	return 0;
}
