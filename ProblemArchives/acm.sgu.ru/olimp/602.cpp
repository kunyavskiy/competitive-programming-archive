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

const int ans[12]={31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int x;
	cin>>x;
	cout<<ans[x-1]<<endl;
  return 0;
}