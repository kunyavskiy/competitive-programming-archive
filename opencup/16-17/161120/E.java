
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class E {

    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        char[][] c = new char[1][0];
        int mm = 0;
        int nn = 1;
        boolean left = false;
        while (mm < m) {
            if (left) {
                char[][] cc = new char[1][mm + 1];
                System.arraycopy(c[0], 0, cc[0], 1, mm);
                cc[0][0] = '0';
                if (query(cc)) {
                    mm++;
                    c = cc;
                } else {
                    mm++;
                    cc[0][0] = '1';
                    c = cc;
                }
            } else {
                char[][] cc = new char[1][mm + 1];
                System.arraycopy(c[0], 0, cc[0], 0, mm);
                cc[0][mm] = '0';
                
                if (query(cc)) {
                    mm++;
                    c = cc;
                } else {
                    cc[0][mm] = '1';
                    if (query(cc)) {
                        mm++;
                        c = cc;
                    } else {
                        left = true;
                    }
                }
            }
        }
        boolean top = false;
        while (nn < n) {
            if (top) {
                char[][] cc = new char[nn + 1][mm];
                System.arraycopy(c, 0, cc, 1, nn);
                cc[0] = new char[mm];
                Arrays.fill(cc[0], '?');
                for (int i = 0; i < mm; i++) {
                    cc[0][i] = '0';
                    if (!query(cc)) {
                        cc[0][i] = '1';
                    }
                }
                nn++;
                c = cc;
            } else {
                char[][] cc = new char[nn + 1][mm];
                System.arraycopy(c, 0, cc, 0, nn);
                cc[nn] = new char[mm];
                Arrays.fill(cc[nn], '?');
                boolean ok = true;
                cc[nn][0] = '0';
                if (!query(cc)) {
                    cc[nn][0] = '1';
                    if (!query(cc)) {
                        top = true;
                        ok = false;
                    }
                }
                if (ok) {
                    for (int i = 1; i < mm; i++) {
                        cc[nn][i] = '0';
                        if (!query(cc)) {
                            cc[nn][i] = '1';
                        }
                    }
                    nn++;
                    c = cc;
                }
            }
        }
        out.println("Answer:");
        for (char[] chars : c) {
            out.println(new String(chars));
        }
    }

    boolean query(char[][] c) throws IOException {
        out.println("Query: " + c.length + " " + c[0].length);
        for (char[] chars : c) {
            out.println(new String(chars));
        }
        out.flush();
        return nextInt() == 1;
    }


    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
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