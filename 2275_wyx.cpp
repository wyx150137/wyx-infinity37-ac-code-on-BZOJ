
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
using namespace std;
LL F[100], n; int cnt;
int main() {
    cin >> n;
    F[cnt] = F[++cnt] = 1;
    while(F[cnt] < n) F[++cnt] = F[cnt-1] + F[cnt-2] ;
    if(F[cnt] == n) cout << n << endl;
    else while(n) {
            while(F[cnt] > n) cnt --;
            if(F[cnt] == n) { cout << n << endl; break;}
            n -= F[cnt];
        }
}
