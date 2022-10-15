#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "NOLOGIC"

typedef long long ll;
typedef long double ld;

bool ok[26];

char s[1100];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif


    int t;
    gets(s);
    sscanf(s,"%d",&t);

    while (t --> 0){
    	gets(s);
    	memset(ok,1,sizeof(ok));
    	for (int i = 0; s[i]; i++)
    		if ('a' <= s[i] && s[i] <= 'z')
    			ok[s[i]-'a'] = 0;
    		else if ('A' <= s[i] && s[i] <= 'Z')
    			ok[s[i]-'A'] = 0;

		bool any = 0;
		for (int i = 0; i < 26; i++)
			if (ok[i]){
				printf("%c",'a'+i);
				any = true;
				break;
			}
		if (!any) printf("~");
		printf("\n");

    }
      
  return 0;
}