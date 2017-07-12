
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
char A[N],B[N];
int fail[N],f[N],pos[N];
int main()
{
	scanf("%s",A+1);
	scanf("%s",B+1);
	int lenA = strlen(A+1),lenB = strlen(B+1);
	int j = 0;
	for(int i = 2;i<= lenB;i++)
	{
		while(B[i]!=B[j+1]&&j)
			j = fail[j];
		if(B[i]==B[j+1])j++;
		fail[i] = j;
	}
	for(int i = 1;i<= lenA;i++)
	{
		j = f[pos[pos[0]]];
		while(A[i]!=B[j+1]&&j)
			j = fail[j];
		if(A[i]==B[j+1])j++;
		if(j==lenB)pos[0]-=lenB-1;
		else {f[i] = j;pos[++pos[0]] = i;}
	}
	for(int i = 1;i<= pos[0];i++)
		printf("%c",A[pos[i]]);
	return 0;
}
