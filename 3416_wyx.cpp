
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+10;
using namespace std;

int last[N<<1];
int stack[N];
int pos[N];
int sum[N];
char str[N];

std::vector<int> ans[N];

int main()
{
	int n , k ;
	cin >> n >> k;
	scanf("%s",str+1);
	for(int i=1;i<=n;++i) sum[i] = sum[i-1] + (str[i] == 'c' ? (-k) : 1);
//	for(int i=1;i<=n;++i) cout << sum[i] << " " ; 
	last[n] = 1;
	int cnt = 0,top = 0;
	int j;

	for(int i=1;i<=n;++i){
		sum[i] += n;
		if(!last[sum[i]]){
			stack[++top] = i;
			last[sum[i]] = 1;
		}
		else{
			cnt ++;
			for(j=top-k+1;j<=top;++j){
				ans[cnt].push_back(stack[j]);
				last[sum[stack[j]]] = false;
			}
			ans[cnt].push_back(i); top -= k;

		}
	}

	for(int i=cnt;i;--i)
	{
		for(j=0;j<ans[i].size();++j)
			printf("%d ",ans[i][j]);
		puts("");
	}
}
