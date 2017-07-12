
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
LL v[7][7];
int main()
{
	int n,x;
	char tmp[3];
	scanf("%d",&n);
	for(int i= 1;i<= n;i++)
	{
		scanf("%s%d",tmp,&x);
		if(tmp[0]=='B')v[0][(x%7+7)%7]++;
		else if(tmp[0]=='E')v[1][(x%7+7)%7]++;
		else if(tmp[0]=='S')v[2][(x%7+7)%7]++;
		else if(tmp[0]=='I')v[3][(x%7+7)%7]++;
		else if(tmp[0]=='G')v[4][(x%7+7)%7]++;
		else if(tmp[0]=='O')v[5][(x%7+7)%7]++;
		else v[6][(x%7+7)%7]++;
	}
	LL ans = 0;
	for(int B = 0;B<7;B++)
	for(int E = 0;E<7;E++)
	for(int S = 0;S<7;S++)
	for(int I = 0;I<7;I++)
	for(int G = 0;G<7;G++)
	for(int O = 0;O<7;O++)
	for(int M = 0;M<7;M++)
	{
		if((B+E+S+S+I+E)*(G+O+E+S)*(M+O+O)%7==0)
			ans += v[0][B]*v[1][E]*v[2][S]*v[3][I]*v[4][G]*v[5][O]*v[6][M];
	}
	printf("%lld\n",ans);
	return 0;
}
