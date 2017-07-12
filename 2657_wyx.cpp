
#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 200200
using namespace std;
struct abcd{
	int to,next;
}table[M<<1];
int head[M],tot;
int n,ans;
int max_dpt[M];
map<pair<int,int>,int>e;
void Add(int x,int y)
{
	table[++tot].to=y;
	table[tot].next=head[x];
	head[x]=tot;
}
void Get_Diameter(int x,int from)
{
	int i;
	max_dpt[x]=1;
	for(i=head[x];i;i=table[i].next)
	{
		if(table[i].to==from)
			continue;
		Get_Diameter(table[i].to,x);
		ans=max(ans,max_dpt[x]+max_dpt[table[i].to]);
		max_dpt[x]=max(max_dpt[x],max_dpt[table[i].to]+1);
	}
}
void Sort(int &x,int &y,int &z)
{
	int _x=min(min(x,y),z);
	int _z=max(max(x,y),z);
	int _y=x+y+z-_x-_z;
	x=_x;y=_y;z=_z;
}
int main()
{
	int i,x,y,z;
	map<pair<int,int>,int>::iterator it;
	cin>>n;--n;--n;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		Sort(x,y,z);		
		if(it=e.find(pair<int,int>(x,y)),it!=e.end())
			Add(it->second,i),Add(i,it->second),e.erase(it);
		else
			e[pair<int,int>(x,y)]=i;
		if(it=e.find(pair<int,int>(x,z)),it!=e.end())
			Add(it->second,i),Add(i,it->second),e.erase(it);
		else
			e[pair<int,int>(x,z)]=i;
		if(it=e.find(pair<int,int>(y,z)),it!=e.end())
			Add(it->second,i),Add(i,it->second),e.erase(it);
		else
			e[pair<int,int>(y,z)]=i;
	}
	Get_Diameter(1,0);
	cout<<ans<<endl;
	return 0;
}
