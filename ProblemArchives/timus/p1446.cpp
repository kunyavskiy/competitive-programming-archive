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

map<string,vector<string> > v;

void print(string s){
	printf("%s:\n",s.data());
	for (int i = 0; i < v[s].size(); i++)	
		printf("%s\n",v[s][i].data());
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  string s,t;
  getline(cin,s);
  sscanf(s.data(),"%d",&n);
  for (int i = 0; i < n; i++){
  	getline(cin,s);
  	getline(cin,t);
  	v[t].pb(s);
  }

  print("Slytherin");printf("\n");
  print("Hufflepuff");printf("\n");
  print("Gryffindor");printf("\n");
  print("Ravenclaw");
	
  return 0;
}