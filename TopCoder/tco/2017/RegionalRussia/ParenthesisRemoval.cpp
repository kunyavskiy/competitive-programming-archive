#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class ParenthesisRemoval {
public:
    int countWays(string s) {
        int bal = 0;
        int ans = 1;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                bal++;
            } else if (s[i] == ')') {
                ans = (ans * 1LL *bal) % 1000000007;
                bal--;
            }
        }
        return ans;
    }
};










