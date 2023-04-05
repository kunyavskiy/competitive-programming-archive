
import java.io.*;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class I {

    private int[] pr;
    private boolean[] z;
    private int[][] a;
    private int[] d;

    class StringHash {
        int MOD = (int) (1e9 + 7);
        int[] px;
        int[] ph;
        String s;

        public StringHash(String s, int x) {
            this.s = s;
            px = new int[s.length() + 1];
            ph = new int[s.length() + 1];
            px[0] = 1;
            for (int i = 1; i < px.length; i++) {
                px[i] = (int) ((px[i - 1] * (long) x) % MOD);
            }
            ph[0] = 0;
            for (int i = 1; i < ph.length; i++) {
                ph[i] = (int) ((ph[i - 1] * (long) x + s.charAt(i - 1)) % MOD);
            }
        }

        long calcHash(int l, int r) {
            long res = (ph[r] - ph[l] * (long) px[r - l]) % MOD;
            if (res < 0) res += MOD;
            return res;
        }
    }

    class Pair {
        int a; int b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Pair pair = (Pair) o;

            if (a != pair.a) return false;
            return b == pair.b;
        }

        @Override
        public int hashCode() {
            int result = a;
            result = 31 * result + b;
            return result;
        }
    }

    private void solveTest() throws IOException {
        int n = nextInt();
        String[] s = new String[n];
        StringHash[][] hashes = new StringHash[n][2];
        int max = 0;
        for (int i = 0; i < n; i ++) {
            s[i] = next();
            max = Math.max(max, s[i].length());
            String ss = s[i] + s[i];
            hashes[i][0] = new StringHash(ss, 12312423);
            hashes[i][1] = new StringHash(ss, 52341424);
        }
        int l = 0;
        int r = max;
        a = new int[n][n];
        d = new int[n];
        int[] last = new int[n * (n + 1)];
        pr = new int[n * (n + 1)];
        z = new boolean[n];
        Map<Pair, Integer> map = new HashMap<>();
        while (r > l + 1) {
            int m = (l + r) / 2;
            int nn = 0;
            int mm = 0;
            map.clear();
            outer: for (int i = 0; i < n; i++) {
                if (s[i].length() < m) continue;
                d[nn] = 0;
                for (int j = 0; j < s[i].length(); j++) {
                    int h1 = (int) hashes[i][0].calcHash(j, j + m);
                    int h2 = (int) hashes[i][1].calcHash(j, j + m);
                    Pair p = new Pair(h1, h2);
                    Integer id = map.get(p);
                    if (id == null) {
                        id = mm++;
                        map.put(p, id);
                        last[id] = -1;
                        pr[id] = -1;
                    }
                    if (last[id] == i) continue;
                    last[id] = i;
                    if (d[nn] == n) {
                        continue outer;
                    }
                    a[nn][d[nn]] = id;
                    d[nn]++;
                }
                nn++;
            }
//            System.out.println(m);
//            for (int i = 0; i < nn; i++) {
//                System.out.print(i + ": ");
//                for (int j = 0; j < d[i]; j++) {
//                    System.out.print(a[i][j] + " ");
//                }
//                System.out.println();
//            }
//            System.out.println(Arrays.toString(pr));
            boolean ok = true;
            for (int i = 0; i < nn; i++) {
                Arrays.fill(z, false);
                if (!dfs(i)) {
                    ok = false;
//                    System.out.println(i + " !!!");
                    break;
                }
            }
//            System.out.println(Arrays.toString(pr));
            if (ok) {
                r = m;
            } else {
                l = m;
            }
        }
        out.println(r);
    }

    private boolean dfs(int i) {
        if (z[i]) return false;
        z[i] = true;
        for (int j = 0; j < d[i]; j++) {
            int x = a[i][j];
            if (pr[x] == -1 || dfs(pr[x])) {
                pr[x] = i;
                return true;
            }
        }
        return false;
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
        new I().run();
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