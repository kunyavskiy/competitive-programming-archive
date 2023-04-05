#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;


int main() {
    int n = 1 << 20;
    vector<int> a(n), b(n);
    a[1] = a[2] = 1;
    b[1] = b[2] = 1;
    for (int i = 3; i < n; i++) {
        a[i] = a[i - a[i - 1]] + a[i - 1 - a[i - 2]];
    }
    for (int k = 2; k < n; k *= 2) {
        assert(k * 2 <= n);
        for (int i = 1; i < k; i++)
            b[i + k] = b[i + 1] + k / 2;
        b[k + k] = k;
    }
    for (int i = 1; i < n; i++) {
        int x = __builtin_popcount(i);
        assert(a[i] == b[i]);
        // printf("    %4d : %4d : %4d : %4d : ", i, a[i], b[i], x);
        // forn(j, 11)
        //     printf("%d", (i >> j) & 1);
        // puts("");
    }
}
