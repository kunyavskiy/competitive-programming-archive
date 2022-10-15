#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool used[5][5];
set<string> s;

const int dx[4]={0,1,-1,0};
const int dy[4]={1,0,0,-1};

char c[5][5];

void dfs(int x,int y,string s){
	if (x < 0 || y < 0 || x>= 4 || y>=4)
		return;
	if (used[x][y])
		return;
	s+= c[x][y];
	used[x][y] = true;
	::s.insert(s);

	for (int i = 0; i < 4; i++)
		dfs(x+dx[i],y+dy[i],s);

	used[x][y] = false;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	for (int i = 0;i < 4; i++)
		for (int j=0; j < 4; j++)
			scanf(" %c",&c[i][j]);
	for (int i = 0; i < 4; i++)	
		for (int j = 0; j < 4; j++)
			dfs(i,j,"");
	int n;
	cin >> n;
	for (int i = 0;i < n; i++){
		string s;
		cin >> s;
		cout << s <<": "<<(( ::s.find(s) == ::s.end()) ? "NO" : "YES") << endl;
	}
  return 0;
}