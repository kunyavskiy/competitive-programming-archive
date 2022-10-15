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
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld double
#define fileinout
using namespace std;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int t,s,l;
 	cout<<fixed;
 	cout.precision(5);
  for (;;){
  	scanf("%d %d %d",&t,&s,&l);
  	if (t==0 && s==0 && l==0)
  		return 0;
  	ld p=s/l;
  	ld s=t;
  	ld c=(p*p-4*s)/(2*p);
  	ld h=2*s/c;
  	cout<<h<<endl;
  }
  return 0;
}