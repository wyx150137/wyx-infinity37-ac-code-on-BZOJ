
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
using namespace std;

int cnt[27][27];
int tot[N];
int MIN[27][27];
int MIN_L[27][27];
int sec[27][27];
char str[N];
int ans = 0;

void calc(int x,int y){
	if(cnt[x][y] != tot[y])
		ans = max(ans,MIN[x][y] - MIN_L[x][y]);
	else ans = max(ans,MIN[x][y]-sec[x][y]);
	if(MIN[x][y] < MIN_L[x][y])
	{
		if(cnt[x][y] == tot[y]) MIN_L[x][y] = MIN[x][y];
		else{
			sec[x][y] = MIN_L[x][y];
			MIN_L[x][y] = MIN[x][y];
			cnt[x][y] = tot[y];
		}
	}
	else if(MIN[x][y] < sec[x][y]) 
		if(cnt[x][y]!=tot[y])
			sec[x][y] = MIN_L[x][y];	
}

int main()
{
	int n; cin >> n;
	scanf("%s",str+1);
	memset(sec,0x3f,sizeof sec);
	for(int i=1,j=1;i<=n;++i)
	{
		int tmp = str[i] - 'a' + 1;
		tot[tmp] ++;
		for(j=1;j<=26;++j)
			if(tmp!=j)
			{
				MIN[tmp][j] ++;
				calc(tmp,j);
				MIN[j][tmp] --;
				calc(j,tmp);
			}
	}
	cout << ans << endl;
}
