
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

public class E {

    private int n;
    private int m;
    private int k;
    private int w;
    private boolean[] sp;
    private int[][] e1;
    private int[][] e2;
    private int m1, m2;
    private long sum;
    private int bad;
    private int[] p;
    private int[] r;

    private void solveTest() throws IOException {
        n = nextInt();
        m = nextInt();
        k = nextInt();
        w = nextInt();
        sp = new boolean[n];
        for (int i = 0;i < k; i++) {
            sp[nextInt() - 1] = true;
        }
        e1 = new int[m][3];
        e2 = new int[m][3];
        m1 = 0;
        m2 = 0;
        for (int i = 0; i < m;i++) {
            int x = nextInt() - 1;
            int y = nextInt() - 1;
            int ww = nextInt();
            if (sp[x] == sp[y]) {
                e1[m1][0] = x;
                e1[m1][1] = y;
                e1[m1][2] = ww * 2;
                m1++;
            } else {
                e2[m2][0] = x;
                e2[m2][1] = y;
                e2[m2][2] = ww * 2;
                m2++;
            }
        }
        Arrays.sort(e1, 0, m1, new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                return Integer.compare(a[2], b[2]);
            }
        });
        Arrays.sort(e2, 0, m2, new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                return Integer.compare(a[2], b[2]);
            }
        });
        p = new int[n];
        r = new int[n];
        if (!calc(0)){
            out.println(-1);
            return;
        }
        long l = (long) -1e11;
        long r = (long) 1e11;
        calc(r);
        if (bad > w) {
            out.println(-1);
            return;
        }
        calc(l);
        if (bad < w) {
            out.println(-1);
            return;
        }
        while (r > l + 1) {
            long mm = (l + r) / 2;
            calc(mm);
            if (bad > w) {
                l = mm;
            } else {
                r = mm;
            }
        }
        calc(r);
//        System.out.println(r + " " + sum + " " + bad + " " + w);
        out.println((sum - w * r) / 2);
    }

    private boolean calc(long mm) {
        int c1 = 0;
        int c2 = 0;
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 0;
        }
        sum = 0;
        bad = 0;
        int c=  0;
        for (int i = 0; i < m; i++) {
            if (c2 == m2 || c1 < m1 && e1[c1][2] <= e2[c2][2] + mm) {
                int x = get(e1[c1][0]);
                int y = get(e1[c1][1]);
                if (x != y) {
                    join(x, y);
                    sum += e1[c1][2];
                    c++;
                }
                c1++;
            } else {
                int x = get(e2[c2][0]);
                int y = get(e2[c2][1]);
                if (x != y) {
                    join(x, y);
                    sum += e2[c2][2] + mm;
                    bad++;
                    c++;
                }
                c2++;
            }
        }
        return c == n - 1;
    }

    private void join(int x, int y) {
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) {
                r[x]++;
            }
        }
    }

    private int get(int i) {
        if (p[i] == i) return i;
        p[i] = get(p[i]);
        return p[i];
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
        new E().run();
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