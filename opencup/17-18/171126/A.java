
import java.io.*;
import java.util.StringTokenizer;

public class A {

    private void solve() throws IOException {
        int n = nextInt() + 3;
        int m = nextInt();
        char[][] a = new char[n][];
        for (int i = 0; i < n; i++) {
            a[i] = next().toCharArray();
        }
        int bal = 0;
        int middle = 0;
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && a[i][0] == '.') middle = i;
            for (int j = 0; j < 11; j++) {
                if (a[i][j] == '#') {
                    if (j <= 4) bal++;
                    if (j >= 6) bal--;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int bestX = -1;
            int bestY = -1;
            int[] max = null;
            for (int x = 0; x < n; x++) {
                int e = 0;
                for (int y = 0; y < 11; y++) {
                    if (a[x][y] == '-') e++;
                }
                for (int y = 0; y < 11; y++) {
                    if (a[x][y] == '-') {
                        int[] val = new int[6];
                        if (a[x - 1][y] == '.') val[0] = 1;
                        val[1] = e;
                        val[2] = -Math.min(Math.min(x, n - 1 - x), Math.abs(middle - x));
                        val[3] = -x;
                        val[4] = new int[]{3,1,4,0,5,2,5,0,4,1,3}[y];
                        if (bal <= 0 ) {
                            if (y <= 4) {
                                val[5] = 1;
                            }
                        } else {
                            if (y >= 6) {
                                val[5] = 1;
                            }
                        }
                        if (bestX == -1) {
                            bestX = x;
                            bestY = y;
                            max = val;
                        } else {
                            int q = 0;
                            while (max[q] == val[q]) q++;
                            if (val[q] > max[q]) {
                                bestX = x;
                                bestY = y;
                                max = val;
                            }
                        }
                    }
                }
            }
            a[bestX][bestY] = (char)('a' + i);
            if (bestY <= 4) bal++;
            if (bestY >= 6) bal--;

//            for (int j = 0; j < n; j ++) {
//                System.err.println(new String(a[j]));
//            }

        }
        for (int i = 0; i < n; i ++) {
            out.println(new String(a[i]));
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