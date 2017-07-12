
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 8e5+5;
char str[N];
int last, p, np, q, nq, sz, depth[N], fa[N], root;
int son[N][27], size[N][2];

inline int newnode(int _) {
    depth[++sz] = _;
    return sz;
}

inline void insert(int x) {
    p = last; last = np = newnode(depth[p]+1);
    while(p && !son[p][x]) {
        son[p][x] = np;
        p = fa[p];
    }
    if(!p) fa[np] = root;
    else {
        q = son[p][x];
        if(depth[q] == depth[p] + 1) fa[np] = q;
        else {
            nq = newnode(depth[p] + 1);
            memcpy(son[nq], son[q], sizeof son[q]);
            fa[nq] = fa[q]; fa[q] = fa[np] = nq;
            while(p && son[p][x] == q) {
                son[p][x] = nq;
                p = fa[p];
            }
        }
    }
}

vector <int> V[N];

inline void DFS(int x){
    for(int i=0;i<V[x].size();++i) {
        DFS(V[x][i]);
        size[x][0] += size[V[x][i]][0];
        size[x][1] += size[V[x][i]][1];
    }
}

int main() {
    root = last = newnode(0);
    scanf("%s", str+1);
    for(int i=1;str[i];++i) insert(str[i]-'a'), size[last][0] ++;
    insert(26);
    scanf("%s", str+1);
    for(int i=1;str[i];++i) insert(str[i]-'a'), size[last][1] ++;
    for(int i=2;i<=sz;++i) V[fa[i]].push_back(i);
    DFS(root); 
    LL ans = 0;
    for(int i=1;i<=sz;++i) 
        ans += (LL) size[i][0] * size[i][1] * (depth[i] - depth[fa[i]]);
    cout << ans << endl;
}
