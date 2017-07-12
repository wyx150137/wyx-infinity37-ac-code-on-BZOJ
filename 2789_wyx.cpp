
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#define lowbit(x)((x)&(-x))
#define N 1000000+1
using namespace std;

int a[N];

void updata(int x,int num)
{
	while(x<N)
	{
		a[x]+= num;
		x+=lowbit(x);
	}
}

int ask(int x)
{
	int num = 0;
	while(x)
	{
		num += a[x];
		x -= lowbit(x);
	}	
	return num;
}

char str[N];
vector<int> v[27];
int last[27];
int tmp[N];

int main()
{
	int n;
	cin>>n;
	scanf("%s",str+1);
	for(int i=1;i<=n;++i)
		v[str[i]-'A'].push_back(i);
	scanf("%s",str+1);
	for(int i=1;i<=n;++i)
	{
		tmp[i] = v[str[i]-'A'][last[str[i]-'A']];
		last[str[i]-'A']++;
	}
	long long ans = 0;
	for(int i=1;i<=n;++i)
	{
		ans += ask(N-1)-ask(tmp[i]);
		updata(tmp[i],1);
	}
	cout<<ans;
}
