
#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
 
#define Min(a, b) ((a)<(b)?(a):(b))
#define Max(a, b) ((a)>(b)?(a):(b))
#define Abs(x) ((x)>0?(x):-(x))
 
#define N 500010
#define M 500010

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n, m;
 
struct Point {
	int x, y;
	Point(int _x = 0, int _y = 0):x(_x),y(_y){}
	void set(int _, int __) {
		x = _, y = __;
	}
}P[N + M];
int Dis(const Point &A, const Point &B) {
	return Abs(A.x - B.x) + Abs(A.y - B.y);
}

bool sign;
inline bool cmp(const Point &A, const Point &B) {
	if (sign)
		return A.x ^ B.x ? A.x < B.x : A.y < B.y;
	else
		return A.y ^ B.y ? A.y < B.y : A.x < B.x;
}
 
struct Node {
	Node *l, *r;
	int x[2], y[2];
	Point p;
	 
	void set(const Point &P) {
		p = P;
		x[0] = x[1] = P.x;
		y[0] = y[1] = P.y;
	}

	int Dis(const Point &p) const {
		int res = 0;
		if (p.x < x[0] || p.x > x[1]) res += (p.x < x[0]) ? x[0] - p.x : p.x - x[1];
		if (p.y < y[0] || p.y > y[1]) res += (p.y < y[0]) ? y[0] - p.y : p.y - y[1];
		return res;
	}

	void up(Node *B) {
		x[0] = min(x[0],B->x[0]), x[1] = max(x[1],B->x[1]);
		y[0] = min(y[0],B->y[0]), y[1] = max(y[1],B->y[1]);
	}
}mem[N + M], *C = mem, Tnull, *null = &Tnull;
 
Node *Build(int L, int R, bool d) {
	if (L > R)
		return null;
	 
	int mid = (L + R) >> 1;
	sign = d;
	std::nth_element(P + L + 1, P + mid + 1, P + R + 1, cmp);
	 
	Node *q = C++;
	q->set(P[mid]);
	q->l = Build(L, mid - 1, d ^ 1);
	q->r = Build(mid + 1, R, d ^ 1);
	if (q->l != null)  q->up(q->l);
	if (q->r != null)  q->up(q->r);
	return q;
}
 
const int INF = 0x3f3f3f3f;

int res;
void Ask(Node *q, const Point &p) {
	res = Min(res, Dis(q->p, p));
	int DisL = q->l != null ? q->l->Dis(p) : INF;
	int DisR = q->r != null ? q->r->Dis(p) : INF;
	if (DisL < DisR) {
		if (q->l != null) Ask(q->l, p);
		if (DisR < res && q->r != null) Ask(q->r, p);
	}
	else {
		if (q->r != null) Ask(q->r, p);
		if (DisL < res && q->l != null) Ask(q->l, p);
	}
}
 
void Insert(Node *root, const Point &p) {
	Node *q = C++; q->l = q->r = null;
	q->set(p); sign = 0;
	while(1) {
		root->up(q);
		if (cmp(q->p, root->p)) {
			if (root->l == null) {
				root->l = q;
				break;
			}
			else
				root = root->l;
		}
		else {
			if (root->r == null) {
				root->r = q;
				break;
			}
			else
				root = root->r;
		}
		sign ^= 1;
	}
}
 
int main() {
	n = read(), m = read();	 
	register int i;
	int ope, x, y;
	for(i = 1; i <= n; ++i) {
		x = read(), y = read();
		P[i] = Point(x, y);
	}
	 
	Node* root = Build(1, n, 0);
	 
	while(m--) {
		ope = read(), x= read(), y = read();
		if (ope == 1) Insert(root, Point(x, y));
		else {
			res = INF; Ask(root, Point(x, y));
			printf("%d\n", res);
		}
	}
	 
	return 0;
}
