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

#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef long double ld;


char s[1100], t[1100];
int lt, ls, res;
bool canov[1100], canins[1100];
int D[1100];

int main(void)
{
  gets(s);
  gets(t);
  ls=strlen(s), lt=strlen(t); 
  for (int i = 0; i+lt <= ls; i++)
  {
    canins[i] = 1;
    for (int j = 0; j < lt; j++)
      if (s[i+j] != '?' && t[j] != s[i+j])
        canins[i] = 0;
  }
  for (int i=0; i < lt; i++)
  {
    canov[i] = 1;
    for (int j=0; i+j < lt; j++)
      if (t[j] != t[i+j]) 
        canov[i] = 0;      
  }
  for (int i=0; i+lt <= ls; i++)
  {
    if (canins[i])
      D[i] = 1;
    for (int j=0; j < i; j++)
      if (canins[i] && (i-j >= lt || canov[i-j]))
        D[i] = max(D[i], D[j]+1);
    res=max(res, D[i]);
  }
  cout << res << endl;
  return 0;
}
