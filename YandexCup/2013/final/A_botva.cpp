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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;


char buf[1100000]; 

char lower(char c){
	if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
	return c;
}


void solve(){
  char fs,fsd;
  fs = fsd = char(1);

  for (int i = (int)strlen(buf); i > 0; ){
  	 int j = i-1;
  	 while (j != -1 && isalpha(buf[j])) j--;
  	 j++;
  	 string cur(buf+j, buf+i);
  	 if (!cur.size()){
  	 	i--;
  	 	continue;
  	 }
  	 cur += char(127);
//  	 eprintf("\n%s\n",cur.data());
  	 for (int k = 1; k < (int)cur.size(); k++){
//  	 	eprintf("%c %c %c\n", cur[k], fs, fsd);
  	    if (pair<char,char>(lower(cur[k]),lower(cur[k])) > pair<char,char>(fs, fsd)){
  	    	int clen = cur.size();
  	    	cur = string(cur.begin(), cur.begin()+k);
  	    	if (k != clen - 1) buf[j+k] = '.';
  	    	k++;
  	    	for (; k < clen-1; k++)
  	    		buf[j+k] = char(1);
  	    }
  	 }
//  	 eprintf("%s\n",buf);
  	 fsd = fs;
  	 fs = lower(cur[0]);
  	 for (int k = 0; k < (int)cur.size()-1; k++)
  	 	if (lower(cur[k]) != fs){
  	 		fsd = lower(cur[k]);
  	 		break;
  	 	}
  	 i = j-1;
  }




  int ptr = 0;
  for (int i = 0; buf[i]; i++)
  	if (buf[i] != 1)
      buf[ptr++] = buf[i];

  buf[ptr++] = 0;
  puts(buf);

}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  while (gets(buf)){
  	solve();
//  	break;
  }

      
  TIMESTAMP(end);
  return 0;
}