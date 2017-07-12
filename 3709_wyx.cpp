
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

const int N = 100000+5;
typedef long long LL;

using namespace std;

void quit()
{
    puts("NIE");
    exit(0);
}

struct data
{
    int a,b,id;
    bool operator < (const data &z)const
    {
        return a < z.a;
    }
}a[N];

struct tmp
{
    int a,b,id;
    bool operator < (const tmp &z)const{
        return b > z.b;
    }
}b[N];

inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int main()
{
    int n = read();
    LL  z = read();
    int cnt1 = 0, cnt2 = 0;
    for(int i=1;i<=n;++i){
        int x = read(), y =  read();
        if(y-x >= 0)
            a[++cnt1].a = x, a[cnt1].b = y,a[cnt1].id = i;
        else
            b[++cnt2].a = x, b[cnt2].b = y,b[cnt2].id = i;
    }
    sort(a+1,a+cnt1+1);
    sort(b+1,b+cnt2+1);

//    for(int i=1;i<=cnt1;++i) cout << a[i].id << endl;
//    for(int i=1;i<=cnt2;++i) cout << b[i].b - b[i].a << endl;

    for(int i=1;i<=cnt1;++i)
    {
        if(z <= a[i].a) quit();
        z += a[i].b - a[i].a;
    }
    for(int i=1;i<=cnt2;++i)
    {
        if(z <= b[i].a) quit();
        z += b[i].b - b[i].a;
    }

    puts("TAK");
    for(int i=1;i<=cnt1;++i) printf("%d ",a[i].id);
    for(int i=1;i<=cnt2;++i) printf("%d ",b[i].id);
    puts("");
}
