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

const string YES = "Possible";
const string NO = "Impossible";


class FoxAndCake2 {

public:
    string isPossible(int a, int b) {
        if (__gcd(a, b) != 1) return YES;

        for (int i = 1; i <= 100 && i < a; i++) {
            for (int j = 1; j <= 100 && j < b; j++) {
                if (__gcd(a - i, b - j) != 1) return YES;
            }
        }

        return NO;
    }
};










