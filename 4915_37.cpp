
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int main()
{
	ll l,r;
	scanf("%lld%lld",&l,&r);
	printf("4\n%lld\n",max(r/11-l+1,0ll)+max(r/29-l+1,0ll));
	return 0;
}
