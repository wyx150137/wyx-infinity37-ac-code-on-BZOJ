
 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct abcd{
    int green[2],not_green[2];
    //0=min 1=max
};
abcd Tree_Dp()
{
    int p;
    abcd re;
    scanf("%1d",&p);
    if(!p)
    {
        re.green[0]=re.green[1]=1;
        re.not_green[0]=re.not_green[1]=0;
        return re;
    }
    if(p==1)
    {
        abcd son=Tree_Dp();
        re.green[0]=son.not_green[0]+1;
        re.green[1]=son.not_green[1]+1;
        re.not_green[0]=min(son.green[0],son.not_green[0]);
        re.not_green[1]=max(son.green[1],son.not_green[1]);
        return re;
    }
    if(p==2)
    {
        abcd ls=Tree_Dp();
        abcd rs=Tree_Dp();
        re.green[0]=ls.not_green[0]+rs.not_green[0]+1;
        re.green[1]=ls.not_green[1]+rs.not_green[1]+1;
        re.not_green[0]=min(ls.green[0]+rs.not_green[0],ls.not_green[0]+rs.green[0]);
        re.not_green[1]=max(ls.green[1]+rs.not_green[1],ls.not_green[1]+rs.green[1]);
        return re;
    }
}
int main()
{
    abcd ans=Tree_Dp();
    printf("%d %d\n", max(ans.green[1],ans.not_green[1]) , min(ans.green[0],ans.not_green[0]) );
}
