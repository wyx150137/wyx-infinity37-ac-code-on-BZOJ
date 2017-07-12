#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
char str[N];
int main() {
	freopen("temp.in","r",stdin);
	FILE *p = NULL;
	char pname[20] = {};
	while(gets(str)) {
		if(str[0] == 'P' && str[1] == 'r' && str[2] == 'o' && str[3] == 'b' && str[4] == 'l' && str[5] == 'e' && str[6] == 'm') {
			if(p != NULL) fclose(p);
			pname[0] = str[7], pname[1] = str[8], pname[2] = str[9], pname[3] = str[10];
			pname[4] = '_'; pname[5] = '3'; pname[6] = '7'; 
			pname[7] = '.'; pname[8] = 'c'; pname[9] = pname[10] = 'p';
			p = fopen(pname, "w");
		}
		else {
			fprintf(p,"%s\n", str);
		}
 	}
}
