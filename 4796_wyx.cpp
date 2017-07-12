
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;

char str[N];
const int op[]={1,2,0,1,0,0,0,2,2,0,0,0,1,0,2,1};
int ans[N];

int main(){
	int n;
	scanf("%s", str+1);
	n = strlen(str+1) / 3;
	for(int i=1;i<=3*n;++i) str[i] -= '0';
	int top = 0;
	for(int i=0;i<n;++i) {
		int t = (str[3*i] << 3) + (str[3*i+1] << 2) + (str[3*i+2] << 1) + (str[3*i+3] << 0);
		if(op[t]) {
			ans [++top] = 3 * i + op[t];
			str[3*i+op[t]] ^= 1;
			str[3*i+op[t] + 1] ^= 1;
		}
	}
	cout << top << endl;
	for(int i=1;i<=top;++i) printf("%d ", ans[i]);
}
