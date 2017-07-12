
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

inline int change(char s)
{
	if(s == 'B') return 1;
	if(s == 'E') return 2;
	if(s == 'S') return 3;
	if(s == 'I') return 4;
	if(s == 'G') return 5;
	if(s == 'O') return 6;
	if(s == 'M') return 7;
	return -1;
}

int T[8][7];

int main()
{
	int n ;
	cin >> n;
	char str[5];int x;
	for(int i=1;i<=n;++i)
	{
		scanf("%s%d",str,&x);
		int tt = change(str[0]);
		T[tt][(x%7+7)%7] ++;
	}

	LL ans = 0;
	for(int i=0;i<7;++i) //B
	for(int j=0;j<7;++j) //E
	for(int k=0;k<7;++k) //S
	for(int l=0;l<7;++l) //I
	for(int m=0;m<7;++m) //G
	for(int p=0;p<7;++p) //O
	for(int q=0;q<7;++q) //M
		if((i+j+k+k+l+j)%7 == 0 || (m+p+j+k)%7 ==0 || (q+p+p) %7 == 0)
			ans += (LL)T[1][i]*T[2][j]*T[3][k]*T[4][l]*T[5][m]*T[6][p]*T[7][q];
	cout << ans << endl;
}
