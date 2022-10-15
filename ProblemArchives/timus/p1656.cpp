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


vector<int> v[10];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif                             
  	int n;
  	cin >> n;

  	vector<int> a(n*n);;



  	for (int i = 0; i < n; i++){
 		for (int j = 0; j < n; j++)
  			cin >> a[i*n+j];
  	}


  	sort(a.begin(),a.end());

  	for (int i = 0; i < n; i++){
		v[i] = vector<int>(a.begin()+i*n,a.begin()+(i+1)*n);
		reverse(v[i].begin()+n/2,v[i].end());
  	}                                        
  	reverse(v+n/2,v+n);

  	for (int i = 0; i < n; i++)
  		for (int j = 0; j < n; j++)
  			cout << v[i][j] <<" \n"[j==n-1];


  	
	
  return 0;
}