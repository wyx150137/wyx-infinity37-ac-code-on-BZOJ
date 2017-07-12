
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e7+5;
int divs[N];
bool cmp(const int &a,const int &b){return a>b;}
int main()
{
	int n,k,x,top = 0;
	scanf("%d%d",&n,&k);
	while(n--)
	{
		scanf("%d",&x);
		for(int i = 1;i*i<= x;i++)
			if(x%i==0)
			{
				divs[++top] = i;
				if(i*i!=x)divs[++top]=x/i;
			}
	}
	sort(divs+1,divs+top+1,cmp);
	int cnt = 1;
	for(int i = 1;i<= top;i++)
	{
		if(divs[i]!=divs[i-1])cnt=1;
		else cnt++;
		if(cnt>=k){printf("%d\n",divs[i]);break;}
	}
	return 0;
}
