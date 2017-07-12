
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
map<int,bool>mp;
const int N = 100;

LL f[N];
const int MAX = 1e9;

int main()
{
    f[0] = 0,f[1] = 1;int i;
    for(i=2;f[i-1]<=MAX;++i) f[i] = f[i-1] + f[i-2];
    mp[0] = 1;
    for(int j=1;j<=i;++j)
        for(int k=1;k<=j;++k)
            if(f[k]*f[j] <= MAX)
                mp[f[k]*f[j]] = 1;
    int T ; cin >> T;
    while(T--)
    {
        int x; cin >> x;
        printf("%s\n",mp[x] ? "TAK" : "NIE");
    }
}
