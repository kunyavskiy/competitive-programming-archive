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

string s;
vector<int> p;
string a,b;

void print(int n){
	if (n == 0){
		printf("No\n");
		return;
	}
	if (p[n-1] == 0){
		printf("Yes\n");
		exit(0);		
	}
	print(n - p[n-1]);
	printf("%s%c",string(b.begin()+n-p[n-1],b.begin()+n).data()," \n"[n==b.size()]);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  cin >>a>>b;
  s = a + char(1)+b;

  p.resize(s.size());
  p[0] = 0;

  for (int i = 1; i < s.size(); i++){
  	int j = p[i-1];
  	for (;j && s[j] != s[i]; j=p[j-1]);
  	if (s[j] == s[i])	
  		j++;
  	p[i] = j;
  }

  p.erase(p.begin(),p.begin()+a.size()+1);


  print(b.size());	


  return 0;
}