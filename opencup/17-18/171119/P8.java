
import java.io.*;
import java.util.StringTokenizer;

public class P8 {

    int[] p;
    int[] rp;
    double[] base;
    double[] delta;

    void sort(int l, int r) {
        int i = l;
        int j = r;
        double x = delta[p[(l + r) / 2]];
        while (i <= j) {
            while (delta[p[i]] < x) i++;
            while (delta[p[j]] > x) j--;
            if (i <= j) {
                int t = p[i]; p[i] = p[j]; p[j] = t;
                i++; j--;
            }
        }
        if (i < r) sort(i, r);
        if (l < j) sort(l, j);
    }

    private void solveTest() throws IOException {
        int n = nextInt();
        double[] aaa = new double[n];
        double[] ddd = new double[n];
        for (int i = 0; i < n; i++) {
            aaa[i] = nextInt();
        }
        for (int i = 0; i < n; i++) {
            ddd[i] = nextInt();
        }
        p = new int[n];
        rp = new int[n];
        base = new double[n];
        delta = new double[n];

        l = new int[n * 20];
        r = new int[n * 20];
        s = new double[n * 20];
        cnt = new int[n * 20];

        for (int i = 0; i < n; i++) {
            base[i] = ddd[i];
            delta[i] = aaa[i] - ddd[i];
            p[i] = i;
        }

        sort(0, n - 1);

        for (int i = 0; i < n; i++) {
            rp[p[i]] = i;
        }
        int[] root = new int[n + 1];
        root[0] = init(n);

        for (int i = 0; i < n; i++) {
            root[i + 1] = add(root[i], 0, n, rp[i]);
        }

        double[] pref = new double[n + 1];
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + base[i];
        }

        int q = nextInt();
        for (int i = 0; i < q; i++) {
            int L = nextInt() - 1;
            int R = nextInt();
            int D = R - L;
            double res = pref[R] - pref[L];
            res += (sum(root[R], root[L], D / 3) + sum(root[R], root[L], D * 2 / 3)) / 2.0;
            out.println(res);
        }
    }

    private double sum(int v, int u, int k) {
        if (l[v] == -1) {
            return s[v] - s[u];
        }
        int q = cnt[r[v]] - cnt[r[u]];
        if (q >= k) {
            return sum(r[v], r[u], k);
        } else {
            return s[r[v]] - s[r[u]] + sum(l[v], l[u], k - q);
        }
    }

    private int add(int v, int L, int R, int x) {
        if (R == L + 1) {
            l[m] = r[m] = -1;
            cnt[m] = 1;
            s[m] = delta[p[L]];
            return m++;
        }
        int M = (L + R) / 2;
        if (x < M) {
            int ll = add(l[v], L, M, x);
            l[m] = ll;
            r[m] = r[v];
        } else {
            int rr = add(r[v], M, R, x);
            l[m] = l[v];
            r[m] = rr;
        }
        cnt[m] = cnt[l[m]] + cnt[r[m]];
        s[m] = s[l[m]] + s[r[m]];
        return m++;
    }

    int m;
    int[] l;
    int[] r;
    int[] cnt;
    double[] s;

    private int init(int n) {
        if (n == 1) {
            l[m] = r[m] = -1;
            return m++;
        }
        int l = init(n / 2);
        int r = init((n + 1) / 2);
        this.l[m] = l;
        this.r[m] = r;
        return m++;
    }

    private void solve() throws IOException {
                solveTest();
    }

    // --------------------------------------

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() throws IOException {
        try {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        } catch (Exception e) {
            throw new IOException();
        }
    }

    int nextInt() throws IOException {
        try {
            return Integer.parseInt(next());
        } catch (Exception e) {
            throw new IOException();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        new P8().run();
    }

    private void run() throws FileNotFoundException {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}