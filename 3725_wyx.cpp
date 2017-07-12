
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
using namespace std;
char str[N];
int main()
{
	scanf("%s",str);
	int n = strlen(str);
	int Min = n, now=0;
	int last = 0;
	register int i = 0;
	for(;str[i];++i) {
		if(str[i] != '*')  {
			if(!last) {
				last = str[i];
				now = i;
			}
			else if(last != str[i]) {
				Min = min(Min,i-now);
				now = i; last = str[i];
			}
			else now = i;
		}
	}
	cout << n - Min + 1 << endl;
}
