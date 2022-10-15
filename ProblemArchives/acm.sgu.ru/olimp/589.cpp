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
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int a[4];
	cin>>a[0]>>a[1]>>a[2]>>a[3];
	sort(a,a+4);
	if (a[0]==a[1] && a[2]==a[3])
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
  return 0;
}