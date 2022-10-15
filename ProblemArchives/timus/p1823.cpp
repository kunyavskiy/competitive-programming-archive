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

map<char,ld> val;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  for (int i = 0; i < 3; i++){
  	ld v;char c;
  	scanf(" %c = ",&c);
  	cin >> v;
  	val[c] = v;
  }

  ld R = 8.314;

  if (val.find('p') == val.end()){
  	cout.precision(15);
  	cout << fixed << "p = "<<val['n']*R*val['T']/val['V'] << endl;
  	return 0;
  }


  if (val.find('n') == val.end()){
  	cout.precision(15);
  	cout << fixed << "n = "<<val['p']*val['V']/(R*val['T']) << endl;
  	return 0;
  }

  if (val.find('T') == val.end()){
  
  	cout.precision(15);

  	if (val['n'] < 1e-9){
  		if (val['p']*val['V'] < 1e-9)
  			printf("undefined\n");
  		else
  			printf("error\n");
  		return 0;
  	}

  	if (val['V'] * val['p'] < 1e-9){
  		printf("error\n");
  		return 0;
  	}

  	cout << fixed << "T = "<<val['V']*val['p']/(R*val['n']) << endl;
  	return 0;
  }


  if (val.find('V') == val.end()){
  	cout.precision(15);

  	if (val['p'] < 1e-9){
  		if (val['n'] < 1e-9)
  			printf("undefined\n");
  		else
  			printf("error\n");
  		return 0;
  	}


  	if (val['n'] < 1e-9){
  		printf("error\n");
  		return 0;
  	}


  	cout << fixed << "V = "<<(R*val['n']*val['T'])/val['p'] << endl;
  	return 0;
  }                                                                   	

  return 0;
}