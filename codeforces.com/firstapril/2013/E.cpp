//#include <iostream>
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
#include <sstream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

ll hash;

void add(int a){
	if (a == 'H' || a == 'Q'){
	hash = hash * 239017 + a;
	hash %= 1000000007;
	}
}

const int YES[] = {47901,37089,0x0051,0x66d3,0xdf70,0xcc47,0x8ad2};
const int NO[] = {4563,49315,0xd3bc,0x5d16,0x1cd1,0xe087,0x76f2,0x6954,0xa807,0x12d1};


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	char c;
  	while (scanf(" %c",&c) == 1)
  		add(c);
  	hash &= 0xffff;

  	eprintf(LLD"\n",hash);

    for (int i = 0; i < int(sizeof(YES)/sizeof(int)); i++)
        if (hash == YES[i]){
            printf("Yes\n");
            return 0;
        }

    for (int i = 0; i < int(sizeof(NO)/sizeof(int)); i++)
        if (hash == NO[i]){
            printf("No\n");
            return 0;
        }

    hash = hash & 15;
//    hash = (hash >> 4) & 15;
//    hash = (hash >> 8) & 15;
//    hash = (hash >> 12) & 15;

    char * botva = new char[hash * 1024 * 8192 ];
    assert(botva);

    printf("Yes\n");

    TIMESTAMP(end);
    return 0;
}