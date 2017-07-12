
#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
const int N = 8005;
// ---------- decimal lib start ----------
const int PREC=3010;
class Dec{
public:
    Dec();
    Dec(int x);
    bool is_zero() const;
    string to_string(int p) const;
    friend Dec operator + (const Dec &a,const Dec &b);
    friend Dec operator - (const Dec &a,const Dec &b);
    Dec & operator += (int x);
    Dec & operator += (ll x);
    Dec & operator -= (int x);
    Dec & operator /= (int x);
    friend Dec operator - (const Dec &a);
private:
    static const int len=PREC/9+1;
    static const int mo=1000000000;
    static void append_to_string(string &s,ll x);
    bool is_neg;
    ll integer;
    int data[len];
    void init_zero();
    void init(const char *s);
};
Dec::Dec(){init_zero();}
Dec::Dec(int x){
    init_zero();
    if(x<0){is_neg=1;x=-x;}
    integer=x;
}
void Dec::init_zero(){
    is_neg=0;
    integer=0;
    memset(data,0,len*sizeof(int));
}
bool Dec::is_zero()const{
    if(integer)return 0;
    for(int i=0;i<len;i++)if(data[i])return 0;
    return 1;
}
void Dec::init(const char *s){
    init_zero();
    is_neg=0;
    integer=0;
    while(*s!=0){
        if(*s=='-'){is_neg=1;++s;break;}
        else if(*s>=48&&*s<=57)break;
        ++s;
    }
    while(*s>=48&&*s<=57){integer=integer*10+*s-48;++s;}
    if(*s=='.'){
        int pos=0,x=mo/10;
        ++s;
        while(pos<len&&*s>=48&&*s<=57){
            data[pos]+=(*s-48)*x;
            ++s;x/=10;
            if(!x){++pos;x=mo/10;}
        }
    }
}
void Dec::append_to_string(string &s,ll x){
    if(x==0){s.append(1,48);return;}
    char _[30];
    int cnt=0;
    while(x){_[cnt++]=x%10;x/=10;}
    while(cnt--){s.append(1,_[cnt]+48);}
}
string Dec::to_string(int p)const{
    string ret;
    if(is_neg&&!is_zero())ret="-";
    append_to_string(ret,integer);
    ret.append(1,'.');
    for(int i=0;i<len;i++){
        int x=mo/10,tmp=data[i];
        while(x){
            ret.append(1,48+tmp/x);
            tmp%=x;x/=10;
            if(!--p)break;
        }
        if(!p)break;
    }
    if(p>0)ret.append(p,'0');
    return ret;
}
Dec & Dec::operator +=(ll x){
    if(!is_neg){
        if(integer+x>=0){integer+=x;}
        else{
            bool last=0;
            for(int i=len-1;i>=0;i--)
                if(last||data[i]){data[i]=mo-data[i]-last;last=1;}
                else last=0;
            integer=-x-integer-last;
            is_neg=1;
        }
    }else{
        if(integer-x>=0)integer-=x;
        else{
            bool last=0;
            for(int i=len-1;i>=0;i--)
                if(last||data[i]){data[i]=mo-data[i]-last;last=1;}
                else last=0;
            integer=x-integer-last;
            is_neg=0;
        }
    }
    return *this;
}
Dec & Dec::operator +=(int x){return *this+=(ll)x;}
Dec & Dec::operator -=(int x){return *this+=(ll)-x;}
Dec & Dec::operator /=(int x){
    if(x<0){is_neg^=1;x=-x;}
    int last=integer%x;
    integer/=x;
    for(int i=0;i<len;i++){
        ll tmp=1LL*last*mo+data[i];
        data[i]=tmp/x;
        last=tmp-1LL*data[i]*x;
    }
    if(is_neg&&!integer){
        int i;
        for(i=0;i<len;i++)if(data[i]!=0)break;
        if(i==len)is_neg=0;
    }
    return *this;
}
Dec operator -(const Dec &a){
    Dec ret=a;
    if(!ret.is_neg&&!ret.integer){
        int i;
        for(i=0;i<Dec::len;i++)if(!ret.data[i])break;
        if(i<Dec::len)ret.is_neg=1;
    }else ret.is_neg^=1;
    return ret;
}
Dec operator +(const Dec &a,int x){Dec ret=a;return ret+=x;}
Dec operator -(const Dec &a,int x){Dec ret=a;return ret-=x;}
Dec operator /(const Dec &a,int x){Dec ret=a;return ret/=x;}
Dec operator +(const Dec &a,const Dec &b){
    if(a.is_neg==b.is_neg){
        Dec ret=a;
        bool last=0;
        for(int i=Dec::len-1;i>=0;i--){
            ret.data[i]+=b.data[i]+last;
            if(ret.data[i]>=Dec::mo){ret.data[i]-=Dec::mo;last=1;}
            else last=0;
        }
        ret.integer+=b.integer+last;
        return ret;
    }else if(!a.is_neg)return a- -b;
    else return b- -a;
}
Dec operator -(const Dec &a,const Dec &b){return a+-b;}
// ---------- decimal lib end ----------
ld f[15][N],y[N];
int q[N],g[15][N],end[N];
ll h[N];
inline ld slope(int a,int b)
{
	return (y[b]-y[a])/(b-a);
}
int main()
{
	int n,k,p;
	scanf("%d%d%d",&n,&k,&p);
	scanf("%lld",&h[1]);
	for(int i = 2;i<= n;i++)
	{
		scanf("%lld",&h[i]);
		if(h[i]<=h[1])n--,i--;
	}
	sort(h+1,h+n+1);
	for(int i = 2;i<= n;i++)h[i]+=h[i-1];
	for(int i = 1;i<= n;i++)f[0][i] = h[1];
	k = min(k,n-1);int W = min(k,14);
	for(int i = 1;i<= W;i++)
	{
		int l = 1,r = 0;
		for(int j = 2;j<= n;j++)
		{
			y[j-1] = h[j-1]-f[i-1][j-1];
			while(l<r&&slope(q[r-1],q[r])>=slope(q[r],j-1))r--;
			q[++r] = j-1;
			y[j+1] = h[j];
			while(l<r&&slope(q[l],j+1)<=slope(q[l+1],j+1))l++;
			f[i][j] = slope(q[l],j+1);
			g[i][j] = q[l];
		}
	}
	end[W]=n-(k-W);
	for(int i = W;i;i--)end[i-1] = g[i][end[i]];
	Dec ans = Dec(h[1]);
	for(int i = 1;i<= W;i++)ans = (ans+h[end[i]]-h[end[i-1]])/(end[i]-end[i-1]+1);
	for(int i=end[W]+1;i<=n;i++)ans=(ans+h[i]-h[i-1])/2;
    cout<<ans.to_string(p+1);
}
