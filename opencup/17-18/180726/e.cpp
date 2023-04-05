#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 2000;

int n, p[N], x[N], y[N], size[N];

bool solve( int R ) {
    forn(i, n) p[i] = i;
    sort(p, p + n, [&]( int i, int j) { return make_pair(x[i], y[i]) > make_pair(x[j], y[j]); });
    ll sum = 0;
    int maY = INT_MIN, miY = INT_MAX, maX = INT_MIN, miX = INT_MAX;
    forn(_i, n) {
        int i = p[_i];
        size[i] = R - x[i];
        for (int _j = _i; _j < n; _j++) {
            int j = p[_j];
            if (y[j] < y[i] && y[i] < y[j] + size[j])
                size[i] = min(size[i], x[j] - x[i]);
            else if (y[j] > y[i])
                size[i] = min(size[i], max(x[j] - x[i], y[j] - y[i]));
        }
        maY = max(maY, y[i] + size[i]);
        miY = min(miY, y[i]);
        maX = max(maX, x[i] + size[i]);
        miX = min(miX, x[i]);
        sum += (ll)size[i] * size[i];
        if (size[i] <= 0)
            return 0;
    }
    return sum == (maY - miY) * (maX - miX);
}

bool run() {
    scanf("%d", &n);
    if (n == 1) {
        size[0] = 1;
        return 1;
    }
    int mi = INT_MAX;
    forn(i, n) {
        scanf("%d%d", &x[i], &y[i]);
        mi = min(mi, y[i]);
    }
    vector<int> p;
    forn(i, n)
        if (y[i] == mi)
            p.push_back(i);
    sort(p.begin(), p.end(), [&]( int i, int j ){ return x[i] < x[j]; });
    int ma = p.back();
    forn(i, n)
        if (solve(x[ma] + y[i] - y[ma])) {
            return 1;
        }
    swap(x[n - 1], x[ma]);
    swap(y[n - 1], y[ma]);
    n--;
    if (solve(x[ma])) {
        int up = INT_MIN;
        forn(i, n)
            up = max(up, y[i] + size[i]);
        size[n] = up - y[n];
        n++;
        swap(size[n - 1], size[ma]);
    }
    return 0;
}

int main() {
    int tn;
    scanf("%d", &tn);
    while (tn--) {
        if (!run())
            puts("NO");
        else {
            printf("YES ");
            forn(i, n)
                printf("%d ", size[i]);
            puts("");
        }
    }
}