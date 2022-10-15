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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


char s[11000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int cnt1,cnt2;
  cnt1 = cnt2 = 0;

  char c;


  scanf("%[a-z]",s);
  do { 
  	if (strlen(s) == 0)
  		continue;
  	if (string(s) == "tram")
  		cnt1++;
  	else if (string(s) == "trolleybus") 
  		cnt2++;                        
  	s[0] = 0;
  } while (scanf("%c%[a-z]",&c,s) != EOF);


  if (cnt1 > cnt2)
  	cout << "Tram driver" << endl;
  else if (cnt2 > cnt1)
  	cout << "Trolleybus driver" << endl;
  else
  	cout << "Bus driver" << endl;     
  	
  return 0;
}