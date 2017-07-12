
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 1e9+7;
const int seed = 131;
const int N = 500005;
int nxt[N],Pre[N],n,sum[N][26];
void init()
{
    Pre[0] = 1;
    for(int i = 1;i< N;i++)
        Pre[i] = (LL)Pre[i-1]*seed%mod;
}
char s[N];

int gethash(int a,int b)
{
    int lth = b-a+1;
    return (LL)(nxt[a]-(LL)nxt[b+1]*Pre[lth]%mod+mod)%mod;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i = 1;i<= n;i++)
    {
        for(int j = 0;j<26;j++)
            sum[i][j] = sum[i-1][j];
        sum[i][s[i]-'a']++;
    }
    
    for(int i = n;i>=1;i--)
        nxt[i] = ((LL)nxt[i+1]*seed+s[i]-'a')%mod;
    init();
    int q = read();
   	while(q--)
    {
        int a = read(),b = read();
        int MIN_len = b-a+1, L = MIN_len;
        for(int j = 0;j<26;j++)
        	if(sum[b][j]-sum[a-1][j])
            	MIN_len = __gcd(MIN_len,sum[b][j]-sum[a-1][j]);
        int ans = L;
        for(int j = 1;j*j<= MIN_len;j++)
            if(MIN_len%j==0)
            {
            	int tt = L / j;
                if(gethash(a,b- tt )==gethash(a+tt,b))
                    ans = min(ans,tt);
                tt = L/(MIN_len/j);
                if(gethash(a,b-tt)==gethash(a+tt,b))
                    ans = min(ans,tt);
            }
        
        printf("%d\n",ans);
    }
    return 0;
}
