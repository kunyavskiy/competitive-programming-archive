#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))


#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int64 t[20][3000][2];
int next[3000][10];
int len;
int mod;
int cnt;
int simbs[20];
int R[15];



void setdp(){
	memset(t,0,sizeof(t));
/*	for (int i=0;i<=len;i++){
		for (int k=0;k<mod;k++)
			for (int l=0;l<2;l++){
				t[i][k][l]=0;
			}
	}*/
}

int gcd(int a,int b){
	if (!a || !b) return a+b;
	return gcd(b,a%b);	
}

int nok(int mask){	
	int ans=1;
	for (int i=2;i<=9;i++)
		if (mask & (1<<i))
			ans=(ans*i)/gcd(ans,i);
	return ans;
}


void initdp(int mask,int Mod=-1){
	mod=1;
	cnt=0;
	for (int i=2;i<=9;i++)
		if (mask & (1<<i)){
			mod=(mod*i)/gcd(mod,i);
			simbs[cnt++]=i;			
		}
	if (Mod!=-1)
		mod=Mod;
	simbs[cnt++]=0;
	simbs[cnt++]=1;
	len=0;
	for (;R[len]!=-1;len++);
	for (int i=0;i<mod;i++)
		for (int j=0;j<cnt;j++)
			next[i][j]=(i*10+j)%mod;			
}

int64 read(int* x,int add){
	int64 X;
	cin>>X;
	X+=add;
	if (X<=0)
		return X;
	int64 tmp=X;
	int* nx=x;
	for (;X;X/=10)
		*(x++)=X%10;
	reverse(nx,x);
	*x=-1;
	return tmp;
}

int64 calcdp(int mask,int Mod=-1){
	initdp(mask,Mod);
	setdp();
	t[0][0][0]=1;
	for (int i=0;i<len;i++)
		for (int j=0;j<mod;j++){
			if (t[i][j]==0) continue;
			for (int nxt=0;nxt<cnt;nxt++)
				t[i+1][next[j][nxt]][1]+=t[i][j][1];
			for (int nxt=0;nxt<cnt;nxt++){
				if (simbs[nxt] < R[i])
					t[i+1][next[j][nxt]][1]+=t[i][j][0];
				else if (simbs[nxt] == R[i])
					t[i+1][next[j][nxt]][0]+=t[i][j][0];
			}
		}
	//cerr<<mask<<" "<<Mod<<" "<<len<<"  "<<t[len][0][0]<<" "<<t[len][0][1]<<endl;
	return t[len][0][0]+t[len][0][1];
}

int64 ans[1<<8][3000];

int64 getans(int mask,int mod){
	if (ans[mask][mod]!=-1)
		return ans[mask][mod];
    ans[mask][mod]=calcdp(mask*4,mod);    
    //cerr<<mask<<" "<<mod<<" "<<ans[mask][mod]<<endl;
    return ans[mask][mod];
}

int size[1<<8];


int64 solve(int add){
	int64 tmp=read(R,add);
	if (tmp<0)
		return 0;
	if (tmp==0)
		return 1;
	int64 ans=0;
	memset(::ans,-1,sizeof(::ans));
	for (int i=(1<<8)-1;i>=0;--i){
		int nk=nok(i*4);
		int64 add=getans(i,nk);
		for (int j=i;;j=(j-1)&i){
			if (size[i^j]%2==1)
				add-=getans(j,nk);
			else
				add+=getans(j,nk);
			if (j==0) break;
		}
		ans+=add;
	}
	return ans;
	
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	size[0]=0;
	for (int i=1;i<(1<<8);i++)
		size[i]=size[i&(i-1)]+1;
	int t;
	scanf("%d",&t);
	for (;t;--t){
		int64 lv=solve(-1);
		int64 rv=solve(0);
		cerr<<rv<<" "<<lv<<endl;
		cout<<rv-lv<<endl;
	}
    return 0;
}