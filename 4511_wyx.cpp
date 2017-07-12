
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int MIN[7];

inline char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
 
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
int main()
{
	int sum = 0, n = read(),ans = 0;
	for(int i=1;i<=n;++i){
		sum = sum + read();
		sum %= 7;
		if(!MIN[sum]) MIN[sum] = i;
		else ans = max(ans,i - MIN[sum]);
	}
	cout << ans << endl;
}
