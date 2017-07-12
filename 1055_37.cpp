
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int c2n[256],num[5];
bool change[5][5][5];
int Able[205][205][5];
char str[205];
bool able(int l,int r,int target)
{
	if(r-l+1==2&&change[c2n[str[l]]][c2n[str[r]]][target])return true;
	else if(r-l+1==1&&target==c2n[str[l]])return true;
	if(Able[l][r][target]!=-1)return Able[l][r][target];
	for(int i = l;i<= r-1;i++)
		for(int k = 1;k<= 4;k++)
			for(int t = 1;t<= 4;t++)
				if(change[k][t][target]&&able(l,i,k)&&able(i+1,r,t))
					return Able[l][r][target] = 1;
	return Able[l][r][target] = 0;
}
int main()
{
	c2n['W'] = 1;
	c2n['I'] = 2;
	c2n['N'] = 3;
	c2n['G'] = 4;
	char s[3];
	for(int i = 1;i<= 4;i++)scanf("%d",&num[i]);
	for(int i = 1;i<= 4;i++)
		for(int j = 1;j<= num[i];j++)
		{
			scanf("%s",s);
			change[c2n[s[0]]][c2n[s[1]]][i] = true;
		}
	scanf("%s",str+1);
	int n = strlen(str+1);
	memset(Able,-1,sizeof(Able));
	bool flag = false;
	if(able(1,n,1))printf("W"),flag = true;
	if(able(1,n,2))printf("I"),flag = true;
	if(able(1,n,3))printf("N"),flag = true;
	if(able(1,n,4))printf("G"),flag = true;
	if(!flag)printf("The name is wrong!\n");
	return 0;
}
