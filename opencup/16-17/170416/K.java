
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;
import java.util.StringTokenizer;

public class K {

    private void solve() throws IOException {
        int n = 6;
        Random random = new Random(1231242234L);
        while (true) {
            char[] a = new char[n];
            c = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = random.nextBoolean() ? '(' : ')';
                c[i] = random.nextInt(10);
            }
            int k = random.nextInt(n + 1);
            String s1 = calc1(n, k, a, 0);
            String s2 = calc2(n, k, a, 0);
            if (!s1.equals(s2)) {
                System.out.println("!!!!");
                System.out.println(new String(a));
                System.out.println(c);
                System.out.println(s1 + " " + s2);
            }
        }
//        solveTest();
    }


    private int[] c;
    private int[] rp;

    private void solveTest() throws IOException {
        int n = nextInt();
        int k = nextInt();
        k++;
//        if (k >= n) {
//            out.println("?");
//        }
        char[] a = next().toCharArray();
        c = new int[n];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            c[i] = nextInt();
            if (c[i] < 0) {
                sum += c[i];
                c[i] = -c[i];
                a[i] = a[i] == '(' ? ')' : '(';
            }
        }
        if (n % 2 == 1) {
            out.println(sum);
            return;
        }

        out.println(calc1(n, k, a, sum));
    }

    private String calc2(int n, int k, char[] a, int sum) {
        for (int m1 = 0; m1 < (1 << n); m1++) {
            for (int m2 = 0; m2 < (1 << n); m2++) {

            }
        }
    }

    private String calc1(int n, int k, char[] a, int sum) {
        int[][] p = new int[n][2];
        for (int i = 0; i < n; i++) {
            p[i][0] = i;
            p[i][1] = c[i];
        }
        Arrays.sort(p, new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                return Integer.compare(a[1], b[1]);
            }
        });

        rp = new int[n];
        for (int i = 0; i < n; i++) {
            rp[p[i][0]] = i;
        }

        SegmentTree st = new SegmentTree(n);

        int bl = 0;
        int br = 0;
        for (int i = 0; i < n; i++) {
            br += a[i] == '(' ? 1 : -1;
            if (a[i] == ')') st.set(rp[i], c[i]);
        }

        int res = Integer.MAX_VALUE;

        for (int i = -1; i < n; i++) {
            if (i >= 0) {
                if (a[i] == '(') {
                    bl--;
                    br--;
                    st.set(rp[i], c[i]);
                } else {
                    bl++;
                    br++;
                    st.remove(rp[i]);
                }
            }
            int r = half(bl) + half(br);
            int c = k - r;
            if (c <= 0) {
                out.println(sum);
                return null;
            }
            if (st.num[0] >= c) {
//                System.out.println(i + " " + (st.sum(c) + sum));
                res = Math.min(res, st.sum(c));
            }
        }
        return (res == Integer.MAX_VALUE ? "?" : ("" + (res + sum)));
    }


    private int half(int x) {
        if (x >= 0) return (x + 1) / 2;
        return x / 2;
    }

    class SegmentTree {

        private int[] num;
        private int[] sum;
        private int size;

        public SegmentTree(int size) {
            this.size = size;
            num = new int[4 * size];
            sum = new int[4 * size];
        }

        private void set(int i, int v) {
            set(0, 0, size, i, v);
        }

        private void set(int n, int l, int r, int i, int v) {
            if (r == l + 1) {
                num[n] = 1;
                sum[n] = v;
            } else {
                int m = (l + r) / 2;
                if (i < m) {
                    set(n * 2 + 1, l, m, i, v);
                } else {
                    set(n * 2 + 2, m, r, i, v);
                }
                num[n] = num[n * 2 + 1] + num[n * 2 + 2];
                sum[n] = sum[n * 2 + 1] + sum[n * 2 + 2];
            }
        }

        public void remove(int i) {
            remove(0, 0, size, i);
        }

        private void remove(int n, int l, int r, int i) {
            if (r == l + 1) {
                num[n] = 0;
                sum[n] = 0;
            } else {
                int m = (l + r) / 2;
                if (i < m) {
                    remove(n * 2 + 1, l, m, i);
                } else {
                    remove(n * 2 + 2, m, r, i);
                }
                num[n] = num[n * 2 + 1] + num[n * 2 + 2];
                sum[n] = sum[n * 2 + 1] + sum[n * 2 + 2];
            }
        }

        private int sum(int k) {
            return sum(0, 0, size, k);
        }

        private int sum(int n, int l, int r, int k) {
            if (r == l + 1) {
                return sum[n];
            } else {
                int m = (l + r) / 2;
                int nl = num[n * 2 + 1];
                if (nl >= k) {
                    return sum(n * 2 + 1, l, m, k);
                } else {
                    return sum[n * 2 + 1] + sum(n * 2 + 2, m, r, k - nl);
                }
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
        new K().run();
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