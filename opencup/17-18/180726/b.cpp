#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int K = 100;

ll n, ans, deg[K];
double logP;
int k, p[K], cnt;

vector<ll> gen;

int m;

void precalc( int i, ll x ) {
    if (i == -1) {
        gen.push_back(x);
        return;
    }
    while (1) {
        precalc(i - 1, x);
        if (x > n / p[i])
            break;
        x *= p[i];
    }
}

void go( int i, ll x ) {
    if (i <= m) {
        ll rest = n / x;
        ans = max(ans, x * *(upper_bound(gen.begin(), gen.end(), rest) - 1));
        // int k = floor(log(rest) / logP + 1e-9);
        // ans = max(ans, x * deg[k]);
        return;
    }
    // ll rest = n / x;
    // forn(j, i + 1)
    //     while (rest % p[j] == 0)
    //         rest /= p[j], x *= p[j];
    if ((n / x) * x <= ans)
        return;
    cnt++;
    while (1) {
        go(i - 1, x);
        if (x > n / p[i])
            break;
        x *= p[i];
    }
}

bool prime( int x ) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

int main() {
    // vector<int> pr;
    // for (int i = 2; i < 100; i++)
    //     if (prime(i))
    //         pr.push_back(i);
    // cout << pr.size() << endl;
    // for (int x : pr)
    //     cout << x << " ";
    // cout << endl;

    cin >> k >> n;
    forn(i, k)
        cin >> p[i];
    sort(p, p + k);
    ans = 1;
    deg[0] = 1;
    forn(i, K - 1)
        deg[i + 1] = deg[i] * p[0];
    logP = log(p[0]);
    m = min(k - 1, 4);
    precalc(m, 1);
    sort(gen.begin(), gen.end());
    cerr << gen.size() << endl;
    go(k - 1, 1); 
    cout << ans << endl;
    cerr << "cnt = " << cnt << endl;
}
