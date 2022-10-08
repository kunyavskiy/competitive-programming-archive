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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	
  	int n;
  	scanf("%d",&n);
  	if (n == 5){
  		puts(">...v");
		puts("v.<..");
		puts("..^..");
		puts(">....");
		puts("..^.<");
		puts("1 1");
		return 0;
  	}

  	if (n == 3){
  		puts(">vv");
		puts("^<.");
		puts("^.<");
		puts("1 3");
		return 0;
  	}
    
    for (int i = 0; i < 100; i+=6){
    	for (int j = 0; j < 50; j++)
    		printf(">");
    	for (int j = 0; j < 50; j++)
    		printf("v");
    	printf("\n");

    	for (int j = 0; j < 99; j++)
    		printf(".");
    	printf("v");
    	printf("\n");


    	printf("^");
    	for (int j = 1; j < 50; j++)
    		printf("^");
    	for (int j = 0; j < 49; j++)
    		printf("<");
        printf("^");
    	printf("\n");

    	if (i == 96) {
    		printf("^");
    		for (int j = 1; j < 100; j++)
    			printf("<");
    		printf("\n");
    	} else {
    		printf("^");
    		for (int j = 1; j < 50; j++)
    			printf("v");
	    	for (int j = 0; j < 50; j++)
    			printf("<");
	    	printf("\n");
    	}

    	if (i == 96) break;
    	printf("^");
    	for (int j = 1; j < 100; j++)
    		printf(".");
    	printf("\n");
        printf("^");
    	for (int j = 0; j < 50; j++)
    		printf(">");
    	for (int j = 0; j < 49; j++)
    		printf("^");

    	printf("\n");
    }

    puts("1 1");
      
    TIMESTAMP(end);
    return 0;
}