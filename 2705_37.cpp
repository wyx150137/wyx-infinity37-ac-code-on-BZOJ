
#include<stdio.h>
#include<math.h>
typedef long long LL;
int main()
{
	 LL n;
	 while(scanf("%lld",&n)!=EOF)
	 {
	 	LL ans = n,tmp,q,cnt;
	 	tmp = (int)sqrt(n);
	 	for(int i = 2;i<= tmp;i++)
	 	{
	 		if(n%i==0)
	 		{
	 			cnt = 0;
	 			q = i;
	 			while(n%q==0)
	 			{
	 				cnt++;
	 				n = n/q;
	 			}
	 			ans = ans+ans*cnt*(q-1)/q;
	 		}
	 	}
	 	if(n!=1) ans = ans+ans*(n-1)/n;
	 	printf("%lld\n",ans);
	 }
	 return 0;
}
