
import java.io.*;
import java.util.*;

public class A {

    private void solveTest() throws IOException {
        int n = nextInt();
        List<Seq> pos = new ArrayList<>();
        List<Seq> neg = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            String ss = next();
            int b = 0;
            int min = 0;
            for (int j = 0; j < ss.length(); j++) {
                if (ss.charAt(j) == '(') {
                    b++;
                } else {
                    b--;
                }
                min = Math.min(min, b);
            }
            if (b >= 0) {
                pos.add(new Seq(b, min, ss.length()));
            } else {
                neg.add(new Seq(-b, min - b, ss.length()));
            }
        }
        int[] posMax = calc(pos);
        int[] negMax = calc(neg);
        int res = 0;
        for (int i = 0; i< Math.min(posMax.length, negMax.length); i++) {
            if (posMax[i] > Integer.MIN_VALUE && negMax[i] > Integer.MIN_VALUE) {
                res = Math.max(res, posMax[i] + negMax[i]);
            }
        }
        out.println(res);
    }

    private int[] calc(List<Seq> s) {
        int max = 0;
        for (Seq seq : s) {
            max += seq.bal;
        }
        int[] res = new int[max + 1];
        Arrays.fill(res, Integer.MIN_VALUE);
        res[0] = 0;
        Collections.sort(s, new Comparator<Seq>() {
            @Override
            public int compare(Seq a, Seq b) {
                return -Integer.compare(a.min, b.min);
            }
        });
        for (Seq seq : s) {
            for (int i = max; i >= -seq.min; i--) {
                if (res[i] > Integer.MIN_VALUE) {
                    res[i + seq.bal] = Math.max(res[i + seq.bal], res[i] + seq.len);
                }
            }
        }
        return res;
    }

    class Seq {
        int bal, min, len;

        public Seq(int bal, int min, int len) {
            this.bal = bal;
            this.min = min;
            this.len = len;
        }
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
        new A().run();
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