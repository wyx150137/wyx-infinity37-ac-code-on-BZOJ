
#include <bits/stdc++.h>

using namespace std;

#define LL long long
#define inf 0x3f3f3f3f
#define Pi acos(-1.0)
#define eps 1e-12
#define N 6020
#define M 400020

int dcmp(double x)
{
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
int sgn(LL x)
{
	if(x == 0) return 0;
	return x < 0 ? -1 : 1;
}
struct point
{
	double x, y, ang;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	point operator - (const point &b) const 
	{
		return point(x - b.x, y - b.y);
	}
	point operator + (const point &b) const 
	{
		return point(x + b.x, y + b.y);
	}
	point operator * (const double &k) const 
	{
		return point(x * k, y * k);
	}
	bool operator < (const point &b) const 
	{
		return ang < b.ang;
	}
	bool operator == (const point &b) const 
	{
		return x == b.x && y == b.y;
	}
	inline double len()
	{
		return sqrt(x * x + y * y);
	}
	inline void get_ang()
	{
		ang = atan2(y, x);
	}
	inline void input()
	{
		int xx, yy;
		scanf("%d%d", &xx, &yy);
		x = 1.0 * xx, y = 1.0 * yy;
	}
};
double dot(point a, point b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}
point get_intersection(point a1, point a2, point b1, point b2)
{
	point u = a1 - b1, av = a2 - a1, bv = b2 - b1;
	double t = cross(bv, u) / cross(av, bv);
	return a1 + av * t;
}
const point O = point(0, 0);
point base;
struct Seg{
	point u, v;
	int id, in;
	double ang;
	Seg(){}
	Seg(point u, point v, int in, int id, double ang) : u(u), v(v), in(in), id(id), ang(ang) {}
	bool operator < (const Seg &b) const 
	{
		if(u == b.u)
		{
			return cross(v - u, b.v - u) < 0;
		}
		point aa = get_intersection(u, v, O, base);
		point bb = get_intersection(b.u, b.v, O, base);
		return aa.len() < bb.len();
	}
}L[N];
bool cmp(Seg a, Seg b)
{
	return dcmp(a.ang - b.ang) < 0 || dcmp(a.ang - b.ang) == 0 && a.in > b.in;
}

int all, tot;
multiset<Seg> S;
multiset<Seg>::iterator it[N];
point pp[N], p[N];
point tri[N][3], t[N][4];
void add(point u, point v, int id)
{
	if(u.ang > v.ang) swap(u, v);
	L[all++] = Seg(u, v, 1, id, u.ang);
	L[all++] = Seg(v, u, 0, id, v.ang);
}
double calc(Seg s)
{
	point a = get_intersection(s.u, s.v, O, base);
	return a.len();
}
int solve(int n)
{
	sort(p, p + n);
	sort(L, L + all, cmp);
	S.clear();
	int ret = 0, i = 0, j = 0;
	for(; i < n; ++i)
	{
		while(j < all && (dcmp(L[j].ang - p[i].ang) < 0 || (dcmp(L[j].ang - p[i].ang) == 0 && L[j].in)))
		{
			base = L[j].u;
			if(L[j].in)
				it[L[j].id] = S.insert(L[j]);
			else
				S.erase(it[L[j].id]);
			++j;
		}
		if(S.empty()){++ret; continue;}
		base = p[i];
		double dis = calc(*S.begin());
		if(dcmp(p[i].len() - dis) <= 0) ++ret;
	}
	return ret;
}

int main()
{
	int V, T;
	scanf("%d%d", &V, &T);
		for(int i = 1; i <= V; ++i)
			pp[i].input();
		for(int i = 1; i <= T; ++i)
			for(int j = 0; j < 3; ++j)
				tri[i][j].input();

		int ans = 0;
		for(int i = 1; i <= V; ++i){
			int cnt = 0;
			for(int j = i + 1; j <= V; ++j){
				p[cnt++] = pp[j] - pp[i];
				p[cnt-1].get_ang();
			}
			tot = all = 0;
			for(int j = 1; j <= T; ++j){
				for(int k = 0; k < 3; ++k)
					t[j][k] = tri[j][k] - pp[i];
				t[j][3] = t[j][0];
				point u, v;
				double mx = 0;
				for(int k = 0; k < 3; ++k){
					double ang = dot(t[j][k], t[j][k+1]) / t[j][k].len() / t[j][k+1].len();
					ang = acos(ang);
					if(ang > mx)
						mx = ang, u = t[j][k], v = t[j][k+1];
				}
				u.get_ang(), v.get_ang();
				double d = fabs(u.ang - v.ang);
				if(d < Pi)
					add(u, v, tot++);
				else{
					point tmp = get_intersection(u, v, O, point(-1.0, 0));
					tmp.ang = Pi * dcmp(u.ang);
					add(u, tmp, tot++);
					tmp.ang = Pi * dcmp(v.ang);
					add(v, tmp, tot++);
				}
			}
			int ret = solve(cnt);
			ans += ret;
		}
		printf("%d\n", ans);
	return 0;
}
