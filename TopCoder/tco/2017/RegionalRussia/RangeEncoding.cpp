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


class RangeEncoding {
public:
    int minRanges(vector <int> a) {
        int ans = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            if (i == 0 || a[i] != a[i - 1] + 1) {
                ans++;
            }
        }
        return ans;
    }
};










