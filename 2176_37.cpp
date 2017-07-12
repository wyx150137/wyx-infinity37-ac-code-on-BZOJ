
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e7+5;
unsigned char s[N];
int mp(int n)
{
	int i,j,k,N = n<<1;
	i = 1,j = 2;
	while(i<n&&j<n)
	{
		k = 0;
		while(s[i+k]==s[j+k])k++;
		if(k==n)return min(i,j);
		if(s[i+k]>s[j+k])i = max(j+1,i+k+1);
		else j = max(i+1,j+k+1);
	}
	if(i<n)return i;else return j;
}
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i = 1;i<= n;i++)
		s[i+n]=s[i];
	int st = mp(n);
	for(int i = st;i<st+n;i++)
		printf("%c",s[i]);
	return 0;
}
