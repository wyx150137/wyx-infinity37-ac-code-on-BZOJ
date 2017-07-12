
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100+5;
using namespace std;

char str[N];
int f[N][N];
bool vis[N][N];

bool check(int l,int r,int x,int y){
	int len1 = r-l+1,len2 = y-x+1;
	if(len1%len2)return false;
	for(int i=l;i<=r;++i)
		if(str[i]!=str[(i-l)%(len2)+x])
			return false;
	return 1;
}

int calc(int x){
	int cnt = 0;
	while(x)x/=10,cnt++;
	return cnt;
}

int DFS(int l,int r){
	if(l==r)return 1;
	if(vis[l][r]) return f[l][r];
	vis[l][r] = 1;int len=r-l+1;
	for(int k=l;k<r;++k){
		len = min(len,DFS(l,k)+DFS(k+1,r));
		if(check(k+1,r,l,k))
			len = min(len,DFS(l,k)+2+calc((r-k)/(k-l+1)+1));
	}
	return f[l][r] = len;
}

int main(){
	scanf("%s",str);int len = strlen(str);
	printf("%d\n",DFS(0,len-1));
}
