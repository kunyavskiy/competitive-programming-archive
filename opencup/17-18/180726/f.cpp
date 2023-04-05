// #include <cstdio>
// #include <cassert>
// #include <ext/pb_ds/assoc_container.hpp>

// using namespace std;
// using namespace __gnu_pbds;

// int main() {
//   int tn, t, x;
//   tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> s;
  
//   scanf("%d", &tn);
//   while (tn--) {
//     scanf("%d%d", &t, &x);
//     if (t == 1)
//       s.insert(x);
//     else if (t == -1)
//       s.erase(x);
//     else 
//       printf("%d\n", *s.find_by_order(x - 1)); // k-й максимум
//   }
//   return 0;
// }

/** s.order_of_key(9999999) -- позиция ключа в дереве */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std; 
using namespace __gnu_pbds;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 250000 + 10;
const int M = 100;

int n;
ll k, f[N][M], INF = 3e18;

int main() {
    cin >> n >> k;
    if ((ll)n * (n - 1) % 4 != 0) {
        puts("NO");
        return 0;
    }
    f[0][0] = 1;
    for (int i = 1; i < min(N, n + 1); i++) {
        forn(j, M) {
            for (int k = 0; k < i && j - k >= 0; k++)
                if ((f[i][j] += f[i - 1][j - k]) >= INF)
                    f[i][j] = INF;
            if (f[i][j] == INF) {
                while (j < M)
                    f[i][j++] = INF;
            }
        }
        ll ma = (ll)i * (i - 1) / 2;
        for (ll j = ma + 1; j < M; j++)
            f[i][j] = 0;
        if (ma < 2 * M)
            for (ll j = ma; j > ma - j; j--)
                if (j < M)
                    f[i][j] = f[i][ma - j];
    }
    int notInf = min(N - 1, n);
    while (f[notInf][M - 1] == INF)
        notInf--;
    cerr << "notInf = " << notInf << " : " << f[notInf][M - 1] << endl;

    ll x = (ll)n * (n - 1) / 4;
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s;
    for (int i = 1; i <= n; i++) 
        s.insert(i);

    auto get = [&]( int n, ll x ) {
        ll ma = (ll)n * (n - 1) / 2;
        if (x < 0 || x > ma)
            return (ll)0;
        if (x > ma - x)
            x = ma - x;
        return (ll)f[n][min(x, (ll)M - 1)];
    };
    // printf("%d %lld --> %lld\n", n, x, get(n, x));
    if (get(n, x) < k) {
        puts("NO");
        return 0;
    }
    puts("YES");
    int cnt = 0; 
    while (n > 0) {
        ll ma = (ll)(n - 1) * (n - 2) / 2;
        int i = max(0LL, x - ma);
        // printf("n = %d, x = %lld [ma=%lld], k = %lld, get = %lld\n", n, x, ma, k, get(n, x));
        // assert(1 <= k && k <= get(n, x));
        while (1) {
            cnt++;
            assert(0 <= i && i < n);
            ll f = get(n - 1, x - i);
            // printf("%d : f(%d, %lld) = %lld\n", i, n - 1, x - i, f);
            if (f >= k) {
                x -= i, n--;
                int item = *s.find_by_order(i);
                printf("%d ", item);
                s.erase(item);
                break;
            }
            k -= f;
            i++;
        }
    }
    puts("");
    cerr << cnt << endl;
}
