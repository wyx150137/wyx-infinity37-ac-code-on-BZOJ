
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 60 * N;
int root[N], son[M][10], tr[M], now[M];
int len, sz;
char str[100];

inline void insert(int x,int &y,int pos,int val) {
	y = ++sz;
	memcpy(son[y], son[x], sizeof son[y]);
	now[y] = now[x] + val;
	tr[y] = max(now[y], tr[x]);
	if(pos == len) return;
	int temp = str[pos] - 'a';
	insert(son[x][temp], son[y][temp], pos+1, val);
}

inline int ask(int x,int pos) {
	if(pos == len) return tr[x];
	int temp = str[pos] - 'a';
	return ask(son[x][temp], pos+1);
}

int main() {
	int n;
	scanf("%d", &n);
	int lastans = 0;
	for(int i=1;i<=n;++i) {
		int opt;
		scanf("%d", &opt);
		if(opt == 1) {
			scanf("%s", str);
			len = strlen(str);
			insert(root[i-1], root[i], 0, 1);
		}
		else if(opt == 2) {
			scanf("%s", str);
			len = strlen(str);
			insert(root[i-1], root[i], 0, -1);
		}
		else {
			root[i] = root[i-1];
			int l = 1, r = i+1;
			scanf("%s", str);
			len = strlen(str);
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			int temp = ((long long)a * abs(lastans) + b) % c;
			while(l < r) {
				int mid = (l+r) >> 1;
				if(ask(root[mid], 0) <= temp) l = mid + 1;
				else r = mid;
			}
			if(l != i + 1) lastans = l;
			else lastans = -1;
			printf("%d\n", lastans);
 		}
	}
}
