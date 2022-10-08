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

int64 sum(int x){
	return (x*1LL*(x+1))/2;
}

int posx[1100];
int posy[1100];
char s[1100][1100];
int n,m;

vector<pair<int,int> > stat;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	gets(s[0]);
	sscanf(s[0],"%d %d",&n,&m);
	for (int i=0;i<n;i++)
		gets(s[i]);
	int cnt=0;
	memset(posx,-1,sizeof(posx));
	memset(posy,-1,sizeof(posy));
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (s[i][j]=='X'){
				posx[i]=j;
				posy[j]=i;
				cnt++;
				stat.pb(mp(i,j));
			}
	int64 ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			int coef=1;
			if (s[i][j]=='X')
				coef*=-1;
			int64 add=0;
			add=(sum(i)+sum(n-i-1))*m;
			add+=(sum(j)+sum(m-j-1))*n;
			
			if (posx[i]!=-1){
				if (j < posx[i])
					add += (m-posx[i]-1)*2;
				if (j > posx[i])
					add += posx[i]*2;
			}
			if (posy[j]!=-1){
				if (i < posy[j])
					add += (n-posy[j]-1)*2;
				if (i > posy[j])
					add += posy[j]*2;
			}
			ans+=add*coef;
		}
	for (int i=0;i<stat.size();i++)
		for (int j=0;j<stat.size();j++)
			ans+=(abs(stat[i].first-stat[j].first)+abs(stat[i].second-stat[j].second));
	int64 kol=(n*m-cnt)*1LL*(n*m-cnt);
	cout.precision(15);
	cout<<fixed<<ans/(ld)kol<<endl;
	return 0;
}