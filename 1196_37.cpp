
#include <cstdio> 
#include <cstring> 
#include <iostream> 
#include <algorithm> 
#define MAX 20010 
using namespace std;  
struct Edge{
 	int x,y; 	
	int cost,_cost;  	
	bool operator <(const Edge &a)const 
	{ 		
		return cost < a.cost; 	
	} 	
	void Read() 
	{ 		
		scanf("%d%d%d%d",&x,&y,&cost,&_cost); 	
	} 
}edge[MAX];  
int points,k,edges; 
int father[MAX];  
int Find(int x) 
{ 	
	if(father[x] == x)	
	return x; 	
	return father[x] = Find(father[x]); 
}  
inline bool Judge(int ans) 
{ 	
	for(int i = 1; i <= points; ++i) 		
		father[i] = i; 	
	int first = 0,added = 0; 	
	for(int i = 1; i <= edges; ++i) 
	{ 		
		int fx = Find(edge[i].x);
		int fy = Find(edge[i].y); 		
		if(fx != fy)
		 { 			
		 	if(edge[i].cost <= ans)
			{ 				
				++first,++added;
				father[fx] = fy; 			
			} 			
			else if(edge[i]._cost <= ans) 
			{ 				
				++added; 				
				father[fx] = fy;
 			} 		
		 } 	
	 } 	
	 return first >= k && added == points - 1;
  }  
int main() 
{ 	
	cin >> points >> k >> edges; 	
	for(int i = 1; i <= edges - 1; ++i)  	
		edge[i].Read(); 	
	sort(edge + 1,edge + edges + 1); 	
	int l = 0,r = 30000,ans = 30000; 	
	while(l <= r) 
	{ 		
		int mid = (l + r) >> 1; 		
		if(Judge(mid)) 			
			ans = mid,r = mid - 1; 		
		else	
			l = mid + 1; 	
	} 	
	cout << ans << endl;
 	return 0; 
 }
 
