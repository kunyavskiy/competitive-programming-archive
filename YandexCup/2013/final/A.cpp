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

vector<string> v;
vector<char> split;


char buf[1100000]; 

string ropt;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  gets(buf);
  ropt += char(2);

  for (int i = (int)strlen(buf); i > 0; ){
  	 int j = i-1;
  	 while (j != -1 && isalpha(buf[j])) j--;
  	 j++;
  	 string cur(buf+j, buf+i);
  	 cur += char(127);
  	 int tmp = (int)ropt.size()-1;
//  	 eprintf("%s %s\n",cur.data(),ropt.data());
  	 for (int k = 1; k < (int)cur.size(); k++){
  	 	if (tolower(cur[k]) < ropt[tmp]) {
  	 		tmp = (int)ropt.size() - 1;
  	 	} else {
  	 	  if (tolower(cur[k]) == ropt[tmp]) {
  	 	     tmp--;
  	 	  } else {
  	 	     string temp(buf+j, buf+j+k);
  	 	     reverse(temp.begin(), temp.end());
  	 	     for (int q = 0; q < (int)temp.size(); q++)
  	 	     	temp[q] = tolower(temp[q]);
  	 	     ropt += temp;
  	 	     if (k != (int)cur.size() - 1) buf[j+k] = '.';
  	 	  	 k++;
  	 	  	 for (; k < (int)cur.size()-1; k++)
  	 	  	 	buf[j+k] = char(1);
  	      }
  	    }
  	 }
  	 i = j-1;
  }




  int ptr = 0;
  for (int i = 0; buf[i]; i++)
  	if (buf[i] != 1)
      buf[ptr++] = buf[i];

  buf[ptr++] = 0;
  puts(buf);
      
  TIMESTAMP(end);
  return 0;
}