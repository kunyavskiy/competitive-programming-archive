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


char s[110000];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  String s = in.readLine();
        int n = s.length();
        BigInteger ans = BigInteger.ONE;
        for (int i = 0; i < n; i++)
            if (s.charAt(i) == '?') {
                if (i != 0)
                    ans = ans.multiply(BigInteger.TEN);
                else
                    ans = ans.multiply(BigInteger.valueOf(9));
            }
        boolean used[] = new boolean[10];
        for (int i = 0; i < n; i++)
            if ('A' <= s.charAt(i) && s.charAt(i) <= 'J')
                used[s.charAt(i)-'A'] = true;

        int cnt = 0;
        for (int i = 0; i < 10; i++)
            if (used[i])
                cnt++;
        //System.err.println(cnt);
        long coef = cnk(10,cnt);
        if ('A' <= s.charAt(0) && s.charAt(0) <= 'J')
             coef -= cnk(9,cnt-1);
        ans = ans.multiply(BigInteger.valueOf(coef));
        out.println(ans);
      
  TIMESTAMP(end);
  return 0;
}