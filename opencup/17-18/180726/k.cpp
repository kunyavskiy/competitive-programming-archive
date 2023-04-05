#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<ll> x(n + 2);
    x[0] = 0;
    forn(i, n)
        scanf("%lld", &x[i + 1]);
    x[n + 1] = 1e18;
    n += 2;
    vector<ll> sx(n + 1);
    forn(i, n)
        sx[i + 1] = sx[i] + x[i];
    vector<pair<int, int>> d(m);
    forn(i, m) 
        scanf("%d", &d[i].first), d[i].second = i;
    sort(d.begin(), d.end());

    vector<ll> ans(m);
    ll res1 = 0, res2 = 0;
    set<pair<double, int>> s;
    vector<int> k(n, 1);
    auto event = [&]( int i ) {
        return pair<double, int> {(double)(x[i + k[i]] - x[i]) / k[i], i};
    };
    forn(i, n - 1) 
        s.insert(event(i));
    auto get1 = [&]( int i ) {
        return (ll)x[i] * k[i] - (sx[i + k[i]] - sx[i]);
    };
    auto get2 = [&]( int i ) {
        return (ll)k[i] * (k[i] - 1) / 2;
    };
    forn(i, m) {
        while (s.size() && s.begin()->first <= d[i].first) {
            int i = s.begin()->second;
            s.erase(event(i));
            int next = i + k[i];
            assert(next < n && next + k[next] < n);
            res1 -= get1(i) + get1(next);
            res2 -= get2(i) + get2(next);
            s.erase(event(next));
            k[i] += k[next];
            s.insert(event(i));
            res1 += get1(i);
            res2 += get2(i);
        }
        ans[d[i].second] = res1 + res2 * d[i].first;
    }
    forn(i, m)
        printf("%lld\n", ans[i]);
    // puts("");
}
