
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

int solve(char *str)
{
	int len = strlen(str), i, j, k;
	for(i=0,j=1,k=0;i<len && j<len;k=0)
	{
		while(str[(i+k)%len] == str[(j+k)%len]) k ++; if(k == len) break;
		if(str[(i+k)%len] > str[(j+k)%len]) i += k + 1, i = (i==j) ? i + 1 : i;
		else j += k+1, j = (i==j) ? j + 1 : j; 
	}
	return min(i,j);
}

char str1[1000000+5],str2[1000000+5];

int main()
{
	scanf("%s%s",str1,str2);
	int tmp1 = solve(str1), tmp2 = solve(str2);
	int len = strlen(str1);
	bool flag = true;
	for(int i=0;i<len;++i) 
		flag &= (str1[(tmp1+i)%len] == str2[(tmp2+i)%len]);
	if(!flag) 
		puts("No");
	else
	{
		puts("Yes");
		for(int i=0;i<len;++i) 
			printf("%c",str1[(tmp1+i)%len]);
	}
}
