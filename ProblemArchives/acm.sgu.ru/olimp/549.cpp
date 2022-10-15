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

int day(string s)
{
		if (s=="Monday")return 0;
		if (s=="Tuesday")return 1;
		if (s=="Wednesday")return 2;
		if (s=="Thursday")return 3;
		if (s=="Friday")return 4;
		if (s=="Saturday")return 5;
		if (s=="Sunday")return 6;
	
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  string s1,s2;
  cin>>s1>>s2;
  cout<<day(s2)-day(s1)+((day(s2)-day(s1)<=0))*7<<endl;;
  return 0;
}