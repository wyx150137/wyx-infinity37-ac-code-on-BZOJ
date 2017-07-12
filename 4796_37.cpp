
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
char str[N];
int s[N];
int check(vector<int> &a)
{
	int ans = 0;
	for(int i = 0;i+1<a.size();i++)
		ans+=a[i]^a[i+1];
	return ans+1;
}
int main()
{
	scanf("%s",str);
	int n = strlen(str)/3;
	for(int i = 0;i<3*n;i++)
		s[i] = str[i]-'0';
	vector<int>ans;
	for(int i = 0;i<n;i++)
	{
		vector<int>a;
	  	a.clear();
		for(int j = -1;j<= 2;j++)
		{
			if(i==0&&j==-1)a.push_back(0);
			else a.push_back(s[i*3+j]);
		}
		if(check(a)>=3)continue;
		a[1]^=1,a[2]^=1;
		if(check(a)>=3)
		{
			s[i*3]^=1;s[i*3+1]^=1;
			ans.push_back(i*3);
			continue;
		}
		a[1]^=1,a[2]^=1;

		a[2]^=1,a[3]^=1;
		assert(check(a)>=3);
		s[i*3+1]^=1,s[i*3+2]^=1;
		ans.push_back(3*i+1);
	}
	int sz = ans.size();
	printf("%d\n",sz);
	for(int i = 0;i<sz;i++)
	{
		printf("%d",ans[i]+1);
		if(i==sz-1)printf("\n");
		else printf(" ");
	}
	return 0;
}
