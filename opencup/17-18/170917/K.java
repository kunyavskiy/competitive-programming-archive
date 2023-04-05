
import java.io.*;
import java.util.StringTokenizer;

public class K {

    int[] num = new int[4];
    int[][] map = new int[1600][1600];
    int p;

    private void solve() throws IOException {
        for (int i = 0; i < 4; i++) {
            num[i] = nextInt();
        }
        p = num[0] + 2 * (num[1] + num[3]) + 3 * num[2] - 10;
        bt(800, 800, 1, 0);
    }

    int[] dx = {-1, 0, 1, 0};
    int[] dy = {0, -1, 0, 1};

    private boolean bt(int x, int y, int c, int l) {
        map[x][y] = c;

        int tx, ty;
        if (l < p / 4) {
            tx = 0;
            ty = p / 4;
        } else if (l < p / 2) {
            tx = p / 4;
            ty = p / 4;
        } else if (l < p * 3 / 4) {
            tx = p / 4;
            ty = 0;
        } else {
            tx = 0;
            ty = 0;
        }
        tx += 800;
        ty += 800;

        for (int tp = 3; tp >= 0; tp--) {
            if (num[tp] == 0) continue;
            num[tp]--;
            int[][] d;
            if (tp == 3) {
                d = new int[][]{
                        {0, 1, 1},
                        {0, 1, 0}
                        {}

                };
            } else {
                int[] d = new int[4];
                int[] xx = new int[4];
                int[] yy = new int[4];
                int[] dd = new int[4];
                for (int i = 0; i < 4; i++) {
                    xx[i] = x + dx[i] * (tp + 1);
                    yy[i] = y + dy[i] * (tp + 1);
                    dd[i] = Math.abs(xx[i] - tx) + Math.abs(yy[i] - ty);
                    d[i] = i;
                }
                for (int i = 0; i < 4; i++) {
                    for (int j = i + 1; j < 4; j++) {
                        if (dd[d[j]] < dd[d[i]]) {
                            int t = d[i];
                            d[i] = d[j];
                            d[j] = t;
                        }
                    }
                }
                for (int i = 0; i < 4; i++) {
                    boolean ok = true;

                    boolean last = (num[0] + num[1] + num[2] + num[3] == 0);

                    for (int j = 1; j <= tp; j++) {
                        if (!good(x + dx[d[i]] * j, y + dy[d[i]] * j, d[i], last && j == tp)) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) {
                        for (int j = 1; j <= tp; j++) {
                            map[x + dx[d[i]] * j][y + dy[d[i]] * j] = c;
                        }
                        if (last) {
                            if (xx[d[i]] == 0)

                        } good(x + dx[d[i]] * j, y + dy[d[i]] * j, d[i], last && j == tp))
                        bt()
                    }
                }
            }
            num[tp]++;
        }
        map[x][y] = 0;
        return false;
    }

    private boolean good(int x, int y, int d, boolean last) {
        if (last) {
            return map[x][y] == 0;
        }
        for (int i = 0; i < 4; i++) {
            if (i != d) {
                int xx = x + dx[i];
                int yy = y + dy[i];
                if (map[xx][yy] != 0) return false;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (i != d) {
                for (int j = 0; j < 4; j++) {
                    if (j != d) {
                        int xx = x + dx[i] + dx[j];
                        int yy = y + dy[i] + dy[j];
                        if (map[xx][yy] != 0) return false;
                    }
                }
            }
        }
        return true;
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