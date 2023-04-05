
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

public class F {

    private void solveTest() throws IOException {
        int n = nextInt();
        n += 2;
        int w = nextInt();
        Rect[] r =new Rect[n];
        r[0] = new Rect(0, 0, -1, -1, 0);
        r[1] = new Rect(1, 0, -1, -1, 0);
        for (int i = 2; i < n; i++) {
            r[i] = new Rect(nextInt(), nextInt(), nextInt(), nextInt(), nextInt());
        }

        Arrays.sort(r);
        int[] l = new int[n];
        for (int i = 0; i < n; i++) {
            int ll = -1;
            int rr = n;
            while (rr > ll + 1) {
                int mm = (ll + rr) / 2;
                if (r[mm].b > r[i].a) {
                    rr = mm;
                } else {
                    ll = mm;
                }
            }
            l[i] = rr;
        }
        int[][] d = new int[n][n];
        int[] p = new int[n + 1];
        int res = 0;
        for (int i = 0; i < n; i++) {
            p[0] = Integer.MIN_VALUE;
            for (int j = 0; j < i; j++) {
                d[i][j] = d[j][i];
                p[j + 1] = Math.max(p[j], d[i][j]);
            }
            for (int j = i; j < n; j++) {
                if (r[j].type != r[i].type && (r[j].a >= r[i].b || r[j].l + r[i].l <= w)) {
                    d[i][j] = Math.max(r[i].v + r[j].v, r[j].v + p[l[j]]);
                } else {
                    d[i][j] = Integer.MIN_VALUE;
                }
                res = Math.max(res, d[i][j]);
                p[j + 1] = Math.max(p[j], d[i][j]);
            }
        }
        out.println(res);
    }

    class Rect implements Comparable<Rect>{
        int type, l, a, b, v;

        public Rect(int type, int l, int a, int b, int v) {
            this.type = type;
            this.l = l;
            this.a = a;
            this.b = b;
            this.v = v;
        }

        @Override
        public int compareTo(Rect rect) {
            return Integer.compare(b, rect.b);
        }
    }

    private void solve() throws IOException {
        while (true) {
            try {
                solveTest();
            } catch (IOException e) {
                return;
            }
        }
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
        new F().run();
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