
#include <bits/stdc++.h>
using namespace std;
__attribute__((always_inline)) char getc()
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

__attribute__((always_inline)) int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc())) if(ch == EOF) return -1;
	for(D=ch-'0'; isdigit(ch=getc());) D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
#define RG register
namespace io
{
	const int MaxBuff = 1 << 20;
	const int Output = 1 << 24;
	char B[MaxBuff], *S = B, *T = B;
	//#define getc() getchar()
	#define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
	char Out[Output], *iter = Out;
	__attribute__((always_inline)) void flush()
	{
		fwrite(Out, 1, iter - Out, stdout);
		iter = Out;
	}
}

template<class Type> __attribute__((always_inline)) void print(RG Type x, RG char ch = '\n')
{
	using namespace io;
	if(!x) *iter++ = '0';
	else
	{
		if(x < 0) *iter++ = '-', x = -x;
		static int S2[100]; RG int t = 0;
		while(x) S2[++t] = x % 10, x /= 10;
		while(t) *iter++ = '0' + S2[t--];
	}
	*iter++ = ch;
}

const int MAXN = 100000;
const int MAX_VAL = 30000;
int v[MAXN], bucL[MAX_VAL + 1], T[MAX_VAL + 1];
namespace Concurrent {
/*concurrent*/
	inline void concurrentSolve() {
		register int i, n, tmp;
		n = read();
		for (i = 0; i < n; i++) tmp = read(), T[MAX_VAL - (v[i] = tmp)]++;
		T[MAX_VAL - v[0]]--;
		int minL = v[0], maxL = v[0];
		long long ans = 0;
		n--;
		for (i = 1; i < n; i++) {
			int last = v[i - 1], cur = v[i];
			if (last < minL) minL = last;
			else if (last > maxL) maxL = last;
			bucL[last]++;
			T[MAX_VAL - cur]--;
			int bufx = cur << 1, low = std::max(minL, bufx - MAX_VAL),
						 high = std::min(maxL, bufx - 1);
			int tmp = 0, *p1 = bucL + low, *pr = bucL + high - 14,
						  *p2 = T + MAX_VAL - bufx + low;
			while (p1 <= pr) {
				tmp += (*p1) * (*p2) + (*(p1 + 1)) * (*(p2 + 1)) + (*(p1 + 2)) *
					   (*(p2 + 2)) + (*(p1 + 3)) * (*(p2 + 3)) + (*(p1 + 4)) * (*(p2 + 4))
					   + (*(p1 + 5)) * (*(p2 + 5)) + (*(p1 + 6)) * (*(p2 + 6)) + (*(p1 + 7))
					   * (*(p2 + 7)) + (*(p1 + 8)) * (*(p2 + 8)) + (*(p1 + 9)) * (*(p2 + 9))
					   + (*(p1 + 10)) * (*(p2 + 10)) + (*(p1 + 11)) * (*(p2 + 11))
					   + (*(p1 + 12)) * (*(p2 + 12)) + (*(p1 + 13)) * (*(p2 + 13))
					   + (*(p1 + 14)) * (*(p2 + 14));
				p1 += 15, p2 += 15;
			}
			while (p1 <= bucL + high) tmp += (*(p1++)) * (*(p2++));
			ans += tmp;
		}
		print(ans);
	}
}
int main() {
	Concurrent::concurrentSolve();
	io::flush();
	return 0;
}
