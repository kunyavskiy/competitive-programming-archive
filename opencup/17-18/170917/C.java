
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class C {

    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        char[][] a = new char[n][];
        for (int i = 0; i < n; i++) {
            a[i] = next().toCharArray();
        }

        int[][] q = new int[2][2 * n * m + 5];
        int h = 0;
        int t = 0;
        int[][] d = new int[n][m];
        for (int[] ints : d) {
            Arrays.fill(ints, Integer.MAX_VALUE);
        }
        for (int j = 0; j < m; j++) {
            d[n - 1][j] = 0;
            q[0][t] = n - 1;
            q[1][t] = j;
            t++;
        }
        int[] dx = {-1, 1, 0, 0};
        int[] dy = {0, 0, -1, 1};
        while (t != h) {
            int x = q[0][h];
            int y = q[1][h];
            h++;
            if (h == q[0].length) h = 0;
            if (a[x][y] == '.') {
                if (x > 0) {
                    if (d[x - 1][y] > d[x][y] + 1) {
                        d[x - 1][y] = d[x][y] + 1;
                        q[0][t] = x - 1;
                        q[1][t] = y;
                        t++;
                    }
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    int xx = x + dx[i];
                    int yy = y + dy[i];
                    if (xx >= 0 && xx < n && yy >= 0 && yy < m && a[xx][yy] == '#') {
                        if (d[xx][yy] > d[x][y]) {
                            d[xx][yy] = d[x][y];
                            if (h == 0) h = q[0].length;
                            h--;
                            q[0][h] = xx;
                            q[1][h] = yy;
                        }
                    }
                }
                if (x > 0) {
                    if (d[x - 1][y] > d[x][y]) {
                        d[x - 1][y] = d[x][y];
                        if (h == 0) h = q[0].length;
                        h--;
                        q[0][h] = x - 1;
                        q[1][h] = y;
                    }
                }
            }
        }
        char[][] b = new char[n][m];
        for (char[] chars : b) {
            Arrays.fill(chars, '.');
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == '#') {
                    b[i + d[i][j]][j] = '#';
                }
            }
        }
        for (char[] chars : b) {
            out.println(new String(chars));
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
        new C().run();
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