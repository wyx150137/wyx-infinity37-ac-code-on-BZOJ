
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define mp(a,b) make_pair(a,b)
const int N = 1e5+5;
int a[N],b[3],c[3];
set<pair<int,pair<int,int> > >S;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]]++;
	}
	b[0]>>=1,b[1]>>=1,b[2]>>=1;
	for(int i = 1;i<= n;i++)
	{
		c[a[i]]++;
		if(b[0]==c[0]&&b[1]==c[1]&&b[2]==c[2])
			return printf("1\n"),0;
	}
	c[0] = c[1] = c[2] = 0;
	for(int i = 1;i<= n;i++)
	{
		c[a[i]]++;
		if(S.count(mp(c[0]-b[0],mp(c[1]-b[1],c[2]-b[2]))))
			return printf("2\n"),0;
		S.insert(mp(c[0],mp(c[1],c[2])));
	}
	printf("3\n");
	return 0;
}
