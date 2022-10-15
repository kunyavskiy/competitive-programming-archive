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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int64 f1=0;
  int64 f2=1;
	int n;
	int64 sum=0;
	cin>>n;
	for (int i=0;i<n;i++){
		int64 tmp=f2;
		f2=f1+f2;
		f1=tmp;
		sum+=tmp;
	}
	cout<<sum;
  return 0;
}