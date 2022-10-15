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

char buf[1000];


string tostr(int k){
	sprintf(buf,"%d",k);
	return buf;
}


string gena(int n,int k){
	if (n == k)
		return "sin("+tostr(n)+")";
	return "sin("+tostr(k) + (k%2?"-":"+") + gena(n,k+1) + ")";	
}

string gens(int n,int k){
	if (n == k)
		return gena(1,1)+"+"+tostr(n);
	return "("+gens(n,k+1)+")"+gena(n-k+1,1) +"+"+tostr(k);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif                  
   int n;
   cin >> n;
   cout << gens(n,1) << endl;
  return 0;
}