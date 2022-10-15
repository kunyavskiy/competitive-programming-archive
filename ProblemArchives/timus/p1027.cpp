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


char last,cur;
int bal;
bool coment;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  last = cur = 0;
  bal = coment = 0;

  while ( (cur = getc(stdin)) != EOF){
  	if (coment){
  		if (last == '*' && cur == ')')
  			coment = false;
  		last = cur;
  		continue;
  	}
  	if (last == '(' && cur == '*'){
  		--bal;
  		coment = true;
		last = 0;
  		continue;
  	}
  	last = cur;
  	if (cur == '('){
  		++bal;
  		continue;
  	}
  	if (cur == ')'){
  		--bal;
  		if (bal < 0){
  			printf("NO\n");
  			return 0;
  		}
  		continue;
  	}

  	if (!(('0' <= cur && cur <= '9') || (cur == '=') || 
  		(cur == '*') || (cur == '+') || (cur == '-') || (cur == '/') || cur == 10 || cur == 13)){
  			if (bal != 0){
  				printf("NO\n");
  				return 0;
  			}
  		}
  }

  if (bal != 0 || coment){
  	printf("NO\n");
  	return 0;
  }

  printf("YES\n");
	
  return 0;
}