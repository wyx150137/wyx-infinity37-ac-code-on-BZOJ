
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
char s[N];
int main()
{
	scanf("%s",s+1);
	int n = strlen(s+1);
	int last,now = 0,mn = n;
	for(int i = 1;i<= n;i++)
		if(s[i]!='*')
		{
			if(!last||last == s[i])last = s[i],now = i;
			else
			{
				mn = min(mn,i-now);
				last = s[i],now = i;
			}
		}
	printf("%d\n",n-mn+1);
	return 0;
}
