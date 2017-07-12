
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,ans,f[2][4][4][4][4];
inline int Get_Char()
{
	char c;
	do c=getchar(); while(c!='M'&&c!='F'&&c!='B');
	switch(c)
	{
		case 'M':return 1;
		case 'F':return 2;
		case 'B':return 3;
	}
}
inline int Score(int x,int y)
{
	if(x==0) return 1;
	return x==y?1:2;
}
inline int Score(int x,int y,int z)
{
	int temp=x*y*z;
	switch(temp)
	{
		case 6:return 3;
		case 1:
		case 8:
		case 27:return 1;
		case 0:return Score(y,z);
		default: return 2;
	}
}
int main()
{
	scanf("%d",&n);
	memset(f,0xef,sizeof f);
	f[0][0][0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		int temp=Get_Char();
		memset(f[i&1],0xef,sizeof(f[i&1]));
		for(int a1=0;a1<=3;a1++)
			for(int a2=(a1?1:0);a2<=3;a2++)
				for(int b1=0;b1<=3;b1++)
					for(int b2=(b1?1:0);b2<=3;b2++)
						if(f[~i&1][a1][a2][b1][b2]>=0)
						{
							f[i&1][a2][temp][b1][b2]=max(f[i&1][a2][temp][b1][b2]
														,f[~i&1][a1][a2][b1][b2]+Score(a1,a2,temp));
							f[i&1][a1][a2][b2][temp]=max(f[i&1][a1][a2][b2][temp]
														,f[~i&1][a1][a2][b1][b2]+Score(b1,b2,temp));
						}
	}
	for(int a1=0;a1<=3;a1++)
		for(int a2=(a1?1:0);a2<=3;a2++)
			for(int b1=0;b1<=3;b1++)
				for(int b2=(b1?1:0);b2<=3;b2++)
					ans=max(ans,f[n&1][a1][a2][b1][b2]);
	printf("%d\n",ans);
	return 0;
}
