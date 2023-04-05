
import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.StringTokenizer;

public class H {

    private static final long MOD = (long) (1e9 + 7);

    private void solveTest() throws IOException {
        int n = nextInt();
        int[] p = new int[n];
        int[] q = new int[4];
        for (int i = 0; i < n; i++) {
            p[i] = nextInt() - 1;
        }
        for (int i = 0; i < 4; i++) {
            q[i] = nextInt() - 1;
        }
        out.println(calc(n, p, q));
//        int n = 10;
//        int[] p = new int[n];
//        int[] q = new int[4];
//        for (int i = 0; i < p.length; i++) {
//            p[i] = i;
//        }
//        for (int i = 0; i < q.length; i++) {
//            q[i] = i;
//        }
//        Random random = new Random(12312423423312L);
//        while (true) {
//            for (int i = 1; i < n; i++) {
//                int j = random.nextInt(i + 1);
//                int t = p[i]; p[i] = p[j]; p[j] = t;
//            }
//            for (int i = 1; i < 4; i++) {
//                int j = random.nextInt(i + 1);
//                int t = q[i]; q[i] = q[j]; q[j] = t;
//            }
//            int s1 = calc2(n, p, q);
//            int s2 = calc(n, p, q);
//            if (s1 != s2) {
//                System.out.println(n);
//                for (int i = 0; i < n; i++) {
//                    System.out.print((p[i] + 1) + " ");
//                }
//                System.out.println();
//                for (int i = 0; i < 4; i++) {
//                    System.out.print((q[i] + 1) + " ");
//                }
//                System.out.println();
//                System.out.println(s1 + " " + s2);
//                throw new RuntimeException();
//            }
//        }
    }

    private int calc2(int n, int[] p, int[] q) {
        int res = 0;
        for (int a = 1; a < n; a++) {
            for (int b = 1; a + b < n; b++) {
                for (int c = 1; a + b + c < n; c++) {
                    int[] smin = new int[4];
                    int[] smax = new int[4];
                    smin[0] = min(p, 0, a);
                    smax[0] = max(p, 0, a);
                    smin[1] = min(p, a, a + b);
                    smax[1] = max(p, a, a + b);
                    smin[2] = min(p, a + b, a + b + c);
                    smax[2] = max(p, a + b, a + b + c);
                    smin[3] = min(p, a + b + c, n);
                    smax[3] = max(p, a + b + c, n);
                    int s = 0;
                    for (int i = 0; i < 4; i++) {
                        s += (smax[i] - smin[i] + 1);
                    }
                    if (s != n) continue;
                    boolean ok = true;
                    for (int i = 0; i < 4; i++) {
                        for (int j = i + 1; j< 4; j++) {
                            if ((smin[i] - smin[j]) * (q[i] - q[j]) < 0) {
                                ok = false;
                            }
                        }
                    }
                    if (ok) {
                        res++;
                    }
                }
            }
        }
        return res;
    }

    private int min(int[] p, int l, int r) {
        int res = p[l];
        for (int i = l; i < r; i++) {
            res = Math.min(res, p[i]);
        }
        return res;
    }

    private int max(int[] p, int l, int r) {
        int res = p[l];
        for (int i = l; i < r; i++) {
            res = Math.max(res, p[i]);
        }
        return res;
    }

    private int calc(int n, int[] p, int[] q) {
        if (q[0] != 0 && q[1] != 0) {
            reverse(p);
            reverse(q);
        }

//        for (int i = 0; i < n; i++)
//            rp[p[i]] = i;
        int[] minL = calcMin(p);
        int[] maxL = calcMax(p);
        int[] minR;
        int[] maxR;
        int[] pr = calcpr(p, q);
        int[] sf;
        {
            reverse(p);
            reverse(q);
            sf = calcpr(p, q);
            minR = calcMin(p);
            maxR = calcMax(p);
            reverse(minR);
            reverse(maxR);
            reverse(p);
            reverse(q);
            reverse(sf);
        }
        long res = 0;
//        System.out.println(Arrays.toString(p));
//        System.out.println(Arrays.toString(q));
//
//        System.out.println(Arrays.toString(pr));
//        System.out.println(Arrays.toString(sf));
        int min = Integer.MAX_VALUE;
        for (int i = 2; i <= n - 2; i++) {
            if (maxL[i - 1] == i - 1) {
                min = Integer.MAX_VALUE;
            } else {
                min = Math.min(min, p[i - 1]);
            }
            if (Math.max(q[0], q[1]) < Math.min(q[2], q[3])) {
                if (maxL[i - 1] < minR[i]) {
                    res += 1l * pr[i - 2] * sf[i];
                    res %= MOD;
                }
            } else if (Math.min(q[0], q[1]) > Math.max(q[2], q[3])) {
                if (minL[i - 1] > maxR[i]) {
                    res += 1l * pr[i - 2] * sf[i];
                    res %= MOD;
                }
            } else {
                if (q[0] + q[1] == 3) {
                    int l = minR[i];
                    int r = maxR[i];
                    if (l > 0 && r < n - 1 && r - l + 1 == n - i) {
                        if (q[0] == 0) {
                            if (maxL[l - 1] == l - 1) {
                                res += 1l * sf[i];
                                res %= MOD;
                            }
                        } else {
                            if (minL[n - 2 - r] == r + 1) {
                                res += 1l * sf[i];
                                res %= MOD;
                            }
                        }
                    }
                } else {
                    int[] s = new int[4];
                    s[0] = minR[i];
                    s[2] = i - s[0];
                    s[3] = n - 1 - maxL[i - 1];
                    s[1] = n - s[0] - s[2] - s[3];
                    if (s[0] > 0 && s[1] > 0 && s[2] > 0 && s[3] > 0) {
                        if (q[0] == 0) {
                            if (maxL[s[0] - 1] != s[0] - 1 || min != s[0] + s[1]) {
                                continue;
                            }
                        } else {
                            if (minL[s[2] - 1] != s[0] + s[1] || maxL[s[2] - 1] != s[0] + s[1] + s[2] - 1) {
                                continue;
                            }
                        }
                        if (q[3] == 3) {
                            if (minR[n - s[3]] != n - s[3]) {
                                continue;
                            }
                        } else {
                            if (minR[n - s[1]] != s[0] || maxR[n - s[1]] != s[0] + s[1] - 1) {
                                continue;
                            }
                        }
//                        System.out.println(i);
                        res++;
                        res %= MOD;
                    }
                }
            }
        }
        return (int) res;
    }

    private int[] calcMin(int[] a) {
        int[] res = new int[a.length];
        res[0] = a[0];
        for (int i = 1; i < a.length; i++) {
            res[i] = Math.min(res[i - 1], a[i]);
        }
        return res;
    }

    private int[] calcMax(int[] a) {
        int[] res = new int[a.length];
        res[0] = a[0];
        for (int i = 1; i < a.length; i++) {
            res[i] = Math.max(res[i - 1], a[i]);
        }
        return res;
    }

    private void reverse(int[] a) {
        int i = 0;
        int j = a.length - 1;
        while (j > i) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    }

    private int[] calcpr(int[] p, int[] q) {
        if (q[0] < q[1]) {
            for (int i = 0; i < p.length; i++) {
                p[i] = -p[i];
            }
        }
        int[] sl = new int[p.length];
        int[] sr = new int[p.length];
        int[] res = new int[p.length - 1];
        int sp = 0;
        int min = p[0];
        for (int i = 1; i < p.length; i++) {
            while (sp > 0) {
                if (p[i] < sr[sp - 1]) {
                    break;
                }
                sr[sp - 1] = Math.max(sr[sp - 1], p[i]);
                if (sr[sp - 1] > sl[sp - 1]) {
                    sp--;
                } else {
                    break;
                }
            }
            if (p[i] < min) {
                sl[sp] = min;
                sr[sp] = p[i];
                sp++;
            }
            res[i - 1] = sp;
            min = Math.min(min, p[i]);
        }
        if (q[0] < q[1]) {
            for (int i = 0; i < p.length; i++) {
                p[i] = -p[i];
            }
        }
        return res;
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
        new H().run();
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