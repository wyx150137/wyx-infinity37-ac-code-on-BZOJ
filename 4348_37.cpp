
#include <stdio.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define N 1005
int n,m,i,j,x,y,l,r,f[N][N],ans,t,q[10005][3],cnt;bool a[N][N];char ch[N];
struct P {int x,y,l,r,s;}s[N*N];
inline void up(int b) {if(ans<b)ans=b;}
inline void add(int x,int y,int z) 
{
	if(x&&x==y)return;
	q[++cnt][0]=x,q[cnt][1]=y,q[cnt][2]=z;
}
int main() 
{
	scanf("%d",&n);
	gets(ch);
	if(n==1){printf("1",ans);return 0;}
	for(int i = 1;i<= n;i++)
		for(gets(ch+1),j=1;j<=n;j++)
			if(ch[j]=='B')a[i][j]=1;
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			if(a[i][j]&&!f[i][j]) 
			{
				for(x=i;a[x][j];x++);
				for(y=j;a[i][y];y++);
				s[++m].x=i,s[m].y=--x,s[m].l=j,s[m].r=--y;
				up(s[m].s=(x-i+1)*(y-j+1));
				for(int I = i;I<= x;I++)
					for(int J = j;J<=y;J++)
						f[I][J]=m;
			}
	if(ans==n*n){printf("%d",ans);return 0;}
	for(i=n;~i;i--)
		for(j=n;~j;j--)
			f[i+1][j+1]=f[i][j];
	for(i=1;i<=m;i++)
		s[i].x++,s[i].y++,s[i].l++,s[i].r++;
	n+=2;
	ans=2;
	rep(i,1,m) 
	{
		x=s[i].x,y=s[i].y,l=s[i].l,r=s[i].r,cnt=0;
		if(x>2)rep(j,l,r) 
		{
			if(f[x-2][j])add(f[x-2][j],0,0);
			else 
			{
				t=s[i].s+2+s[f[x-2][j-1]].s+s[f[x-2][j+1]].s;
				if(f[x-2][j-1]!=f[x-1][j-1])t+=s[f[x-1][j-1]].s;
				if(f[x-2][j+1]!=f[x-1][j+1])t+=s[f[x-1][j+1]].s;
				if(x>3)t+=s[f[x-3][j]].s;
				up(t);
			}
		}
		if(y+2<=n)rep(j,l,r) 
		{
			if(f[y+2][j])add(f[y+2][j],0,0);
			else 
			{
				t=s[i].s+2+s[f[y+2][j-1]].s+s[f[y+2][j+1]].s;
				if(f[y+2][j-1]!=f[y+1][j-1])t+=s[f[y+1][j-1]].s;
				if(f[y+2][j+1]!=f[y+1][j+1])t+=s[f[y+1][j+1]].s;
				if(y+3<=n)t+=s[f[y+3][j]].s;
				up(t);
			}
		}
		if(l>2)rep(j,x,y) 
		{
			if(f[j][l-2])add(f[j][l-2],0,0);
			else 
			{
				t=s[i].s+2+s[f[j-1][l-2]].s+s[f[j+1][l-2]].s;
				if(f[j-1][l-2]!=f[j-1][l-1])t+=s[f[j-1][l-1]].s;
				if(f[j+1][l-2]!=f[j+1][l-1])t+=s[f[j+1][l-1]].s;
				if(l>3)t+=s[f[j][l-3]].s;
				up(t);
			}
		}
		if(r+2<=n)rep(j,x,y) 
		{
			if(f[j][r+2])add(f[j][r+2],0,0);
			else 
			{
				t=s[i].s+2+s[f[j-1][r+2]].s+s[f[j+1][r+2]].s;
				if(f[j-1][r+2]!=f[j-1][r+1])t+=s[f[j-1][r+1]].s;
				if(f[j+1][r+2]!=f[j+1][r+1])t+=s[f[j+1][r+1]].s;
				if(r+3<=n)t+=s[f[j][r+3]].s;
				up(t);
			}
		}
		if(f[x-1][l-1]) 
		{
			if(x>2)add(f[x-1][l-1],f[x-2][l],0);
			if(l>2)add(f[x-1][l-1],f[x][l-2],0);
		}
		if(f[y+1][l-1]) 
		{
			if(y+2<=n)add(f[y+1][l-1],f[y+2][l],0);
			if(l>2)add(f[y+1][l-1],f[y][l-2],0);
		}
		if(f[x-1][r+1]) 
		{
			if(x>2)add(f[x-1][r+1],f[x-2][r],0);
			if(r+2<=n)add(f[x-1][r+1],f[x][r+2],0);
		}
		if(f[y+1][r+1]) 
		{
			if(y+2<=n)add(f[y+1][r+1],f[y+2][r],0);
			if(r+2<=n)add(f[y+1][r+1],f[y][r+2],0);
		}
		if(x==y) 
		{
			if(l>2)add(f[x][l-2],f[x-1][l-1],f[x+1][l-1]);
			if(r+2<=n)add(f[x][r+2],f[x-1][r+1],f[x+1][r+1]);
		}
		if(l==r) 
		{
			if(x>2)add(f[x-2][l],f[x-1][l-1],f[x-1][l+1]);
			if(y+2<=n)add(f[y+2][l],f[y+1][l-1],f[y+1][l+1]);
		}
		up(s[i].s+2);
		rep(j,1,cnt) 
		{
			up(s[i].s+2+s[q[j][0]].s+s[q[j][1]].s+s[q[j][2]].s);
			rep(k,j+1,cnt) 
			{
				t=s[i].s+2+s[q[j][0]].s+s[q[j][1]].s+s[q[j][2]].s+s[q[k][0]].s+s[q[k][1]].s+s[q[k][2]].s;
				if(q[k][0]==q[j][0]||q[k][0]==q[j][1]||q[k][0]==q[j][2])t-=s[q[k][0]].s;
				if(q[k][1]==q[j][0]||q[k][1]==q[j][1]||q[k][1]==q[j][2])t-=s[q[k][1]].s;
				if(q[k][2]==q[j][0]||q[k][2]==q[j][1]||q[k][2]==q[j][2])t-=s[q[k][2]].s;
				up(t);
			}
		}
		if(x>1&&l>1&&!f[x-1][l-1]) 
		{
			t=s[i].s+2+s[f[x-2][l-1]].s+s[f[x-1][l-2]].s;
			if(x==y&&l==r) 
			{
				if(f[x-1][l-2]!=f[x][l-2])up(t+s[f[x][l-2]].s+s[f[x+1][l-1]].s);else up(t+s[f[x+1][l-1]].s);
				if(f[x-2][l-1]!=f[x-2][l])up(t+s[f[x-2][l]].s+s[f[x-1][l+1]].s);else up(t+s[f[x-1][l+1]].s);
			}else 
			{
				if(f[x-1][l-2]!=f[x][l-2])up(t+s[f[x][l-2]].s);
				if(f[x-2][l-1]!=f[x-2][l])up(t+s[f[x-2][l]].s);
			}
		}
		if(x>1&&r<n&&!f[x-1][r+1]) 
		{
			t=s[i].s+2+s[f[x-2][r+1]].s+s[f[x-1][r+2]].s;
			if(x==y&&l==r) 
			{
				if(f[x-1][r+2]!=f[x][r+2])up(t+s[f[x][r+2]].s+s[f[x+1][l+1]].s);else up(t+s[f[x+1][l+1]].s);
				if(f[x-2][r+1]!=f[x-2][r])up(t+s[f[x-2][r]].s+s[f[x-1][l-1]].s);else up(t+s[f[x-1][l-1]].s);
			}else 
			{
				if(f[x-1][r+2]!=f[x][r+2])up(t+s[f[x][r+2]].s);
				if(f[x-2][r+1]!=f[x-2][r])up(t+s[f[x-2][r]].s);
			}
		}
		if(y<n&&l>1&&!f[y+1][l-1]) 
		{
			t=s[i].s+2+s[f[y+2][l-1]].s+s[f[y+1][l-2]].s;
			if(x==y&&l==r) 
			{
				if(f[y+1][l-2]!=f[y][l-2])up(t+s[f[y][l-2]].s+s[f[x-1][l-1]].s);else up(t+s[f[x-1][l-1]].s);
				if(f[y+2][l-1]!=f[y+2][l])up(t+s[f[y+2][l]].s+s[f[x+1][l+1]].s);else up(t+s[f[x+1][l+1]].s);
			}else 
			{
				if(f[y+1][l-2]!=f[y][l-2])up(t+s[f[y][l-2]].s);
				if(f[y+2][l-1]!=f[y+2][l])up(t+s[f[y+2][l]].s);
			}
		}
		if(y<n&&r<n&&!f[y+1][r+1]) 
		{
			t=s[i].s+2+s[f[y+2][r+1]].s+s[f[y+1][r+2]].s;
			if(x==y&&l==r) 
			{
				if(f[y+1][r+2]!=f[y][r+2])up(t+s[f[y][r+2]].s+s[f[x-1][l+1]].s);else up(t+s[f[x-1][l+1]].s);
				if(f[y+2][r+1]!=f[y+2][r])up(t+s[f[y+2][r]].s+s[f[x+1][l-1]].s);else up(t+s[f[x+1][l-1]].s);
			}else 
			{
				if(f[y+1][r+2]!=f[y][r+2])up(t+s[f[y][r+2]].s);
				if(f[y+2][r+1]!=f[y+2][r])up(t+s[f[y+2][r]].s);
			}
		}
	}
	printf("%d",ans);
	return 0;
}
