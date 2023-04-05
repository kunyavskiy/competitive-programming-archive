    #include <bits/stdc++.h>

    using namespace std; 

    #define forn(i, n) for (int i = 0; i < (int)(n); i++)

    typedef long long ll;

    const int MOD = 1e9 + 7;
    const int K = 10;

    void add(ll &a, int b) {
      if ((a += b) >= MOD) a -= MOD;
    }

    void sub(ll &a, int b) {
      if ((a -= b) < 0) a += MOD;
    }

    ll mul(ll a, ll b) {
        return (int) ((a * 1LL * b) % MOD);
    }

    int inv[K];

    void solve() {
        int n;
        ll a, b, res = 0;
        assert(scanf("%d%lld%lld", &n, &a, &b) == 3);
        vector<ll> s(n);
        forn(i, n)
            assert(scanf("%lld", &s[i]) == 1);
        
        // ll ans = 0;
        // for (ll l = a; l <= b; l++)
        //     for (ll r = l; r <= b; r++) {
        //         map<ll, ll> cnt;
        //         for (ll i = l; i <= r; i++)
        //             cnt[s[i % n] + n * (i / n)]++;
        //         for (auto p : cnt)
        //             add(ans, mul(p.first, mul(p.second, p.second))); 
        //     }
        // printf("[ans=%lld] ", ans);


        forn(i, n)
            forn(j, n)
                if ((s[i] - s[j]) % n == 0) {
                    ll k = (s[i] - s[j]) / n;
                    ll i1 = i, j1 = j + n * k;
                    if (i1 > j1) swap(i1, j1);
                    if (i1 < a) {
                        k = (a - i1 + n - 1) / n;
                        i1 += n * k;
                        j1 += n * k;
                    }
                    if (j1 <= b) {
                        ll x = (i1 - a + 1);
                        ll y = (b - j1 + 1);
                        assert(x > 0 && y > 0);
                        k = y / n; // 0, 1, 2, .. k
                        ll z = (s[i1 % n] + n * (i1 / n));
                        x %= MOD;                   
                        y %= MOD;                   
                        z %= MOD;                   
                        k %= MOD;                   
                        res += mul(z, mul(x, mul(y, (k + 1))));
                        res += mul(mul(n, mul(x, y) + mul(z, y) - mul(x, z)), mul(k, mul(k + 1, inv[2])));
                        res += mul(n, mul(n, mul(y - x - z, mul(k, mul(k + 1, mul(2 * k + 1, inv[6]))))));
                        res -= mul(n, mul(n, mul(n, mul(k, mul(k, mul(k + 1, mul(k + 1, inv[4])))))));
                        res %= MOD;
                    }
                }
        printf("%lld\n", (res % MOD + MOD) % MOD);
    }

    int main() {
        inv[1] = 1;
        for (int i = 2; i < K; i++) {
            inv[i] = mul(MOD - inv[MOD % i], MOD / i);
            assert(mul(i, inv[i]) == 1);
        }

        int tn;
        scanf("%d", &tn);
        while (tn--)
            solve();
    }
