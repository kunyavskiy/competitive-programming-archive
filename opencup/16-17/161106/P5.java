
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class P5 {

    private void solve() throws IOException {
        int n = nextInt();
        int k = nextInt();
        int t = nextInt() - 1;
        int[][] c = new int[n][k + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                c[i][j] = nextInt();
            }
        }
        long min = Long.MAX_VALUE;
        int[] res = new int[n];
        for (int x = 1; x <= n; x++) {
            Mincost mincost = new Mincost();
            mincost.init(n + k + 4, (n + 1) * (k + 2) + 3);
            for (int i = 0; i < n; i++) {
                mincost.addEdge(0, 3 + i, 1, 0);
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= k; j++) {
                    mincost.addEdge(3 + i, 3 + n + j, 1, c[i][j]);
                }
            }
            for (int i = 0; i <= k; i++) {
                int cc = x - 1;
                if (i == t) cc = n - x;
                if (i == k) cc = n;
                mincost.addEdge(3 + n + i, 1, cc, 0);
            }
            mincost.addEdge(3 + n + t, 2, x, 0);
            mincost.addEdge(1, 2, n - x, 0);

            long cost = mincost.minCostMaxFlow(0, 2);
            if (mincost.maxFlow != n) throw new RuntimeException();

            if (cost < min) {
                min = cost;
                for (int i = 0; i < mincost.last; i++) if (mincost.fl[i] == 1){
                    int q = mincost.src[i] - 3;
                    int w = mincost.dst[i] - (3 + n);
                    if (q >= 0 && q < n) {
                        res[q] = w;
                    }
                }
            }
        }
        out.println(min);
        for (int i = 0; i < n; i++) {
            out.print(res[i] + 1 + " ");
        }
        out.println();
    }

    public class Mincost {


        void init(int n, int m) {
            m *= 2;
            this.n = n;
            this.m = m;
            last = 0;
            head = new int[n];
            nx = new int[m];
            dst = new int[m];
            src = new int[m];
            cp = new int[m];
            ct = new long[m];
            fl = new int[m];
            prev = new int[n];
            heap = new int[n];
            heapRev = new int[n];
            d = new long[n];
            bestDist = new long[n];
            for (int i = 0; i < n; i++) {
                heap[i] = i;
                heapRev[i] = i;
            }
            Arrays.fill(head, -1);
        }

        void addEdge(int x, int y, int capacity, int cost) {
            nx[last] = head[x];
            src[last] = x;
            dst[last] = y;
            cp[last] = capacity;
            ct[last] = cost;
            head[x] = last;
            last++;
            nx[last] = head[y];
            src[last] = y;
            dst[last] = x;
            cp[last] = 0;
            ct[last] = -cost;
            head[y] = last;
            last++;
        }

        // Returns the total cost. Max flow value will be in field maxFlow.
        long minCostMaxFlow(int s, int t) {
            for (int i = 0; i < n; i++) {
                d[i] = INF;
            }
            d[s] = 0;
            boolean ok = false;
            while (!ok) {
                ok = true;
                for (int j = 0; j < m; j++)
                    if (fl[j] < cp[j]) {
                        int x = src[j];
                        int y = dst[j];
                        if (d[x] < INF) {
                            if (d[y] > d[x] + ct[j]) {
                                d[y] = d[x] + ct[j];
                                ok = false;
                            }
                        }
                    }
            }
            long res = 0;
            maxFlow = 0;
            while (true) {
                dijkstra(s);
                if (bestDist[t] == INF) break;
                {
                    int i = t;
                    int f = Integer.MAX_VALUE;
                    while (i != s) {
                        int e = prev[i];
                        f = Math.min(f, cp[e] - fl[e]);
                        i = src[e];
                    }
                    if (f < 0) throw new RuntimeException();
                    maxFlow += f;
                    i = t;
                    while (i != s) {
                        int e = prev[i];
                        fl[e] += f;
                        fl[e ^ 1] -= f;
                        if (fl[e] > cp[e]) throw new RuntimeException();
                        res += ct[e] * f;
                        i = src[e];
                    }
                }
                for (int i = 0; i < n; i++) {
                    d[i] += bestDist[i];
                }
            }
            return res;
        }

        private static final long INF = Long.MAX_VALUE;

        int n, m;
        int[] head;
        int[] nx;
        int[] src;
        int[] dst;
        int[] cp;
        long[] ct;
        int[] fl;
        int last;

        long[] d;
        long[] bestDist;
        int[] prev;
        int[] heap;
        int[] heapRev;
        int heapSize;
        long maxFlow;

        private void dijkstra(int start) {
            Arrays.fill(bestDist, INF);
            heapSize = n;
            bestDist[start] = 0;
            siftUp(heapRev[start]);
            for (int i = 0; i < n; i++) {
                int x = removeMin();
                if (bestDist[x] == INF) {
                    break;
                }
                int j = head[x];
                while (j >= 0) {
                    if (fl[j] < cp[j]) {
                        int y = dst[j];
                        long d = ct[j] + this.d[x] - this.d[y];
                        if (d < 0) {
                            throw new AssertionError("negative edge");
                        }
                        long ll = bestDist[x] + d;
                        if (bestDist[y] > ll) {
                            prev[y] = j;
                            bestDist[y] = ll;
                            siftUp(heapRev[y]);
                        }
                    }
                    j = nx[j];
                }
            }
        }

        private void siftUp(int i) {
            while (i > 0 && bestDist[heap[(i - 1) / 2]] > bestDist[heap[i]]) {
                swap(i, (i - 1) / 2);
                i = (i - 1) / 2;
            }
        }

        private int removeMin() {
            int res = heap[0];
            swap(0, heapSize - 1);
            heapSize--;
            int i = 0;
            while (2 * i + 1 < heapSize) {
                int j = i;
                if (bestDist[heap[2 * i + 1]] < bestDist[heap[j]]) {
                    j = 2 * i + 1;
                }
                if (2 * i + 2 < heapSize && bestDist[heap[2 * i + 2]] < bestDist[heap[j]]) {
                    j = 2 * i + 2;
                }
                if (i == j) break;
                swap(i, j);
                i = j;
            }
            return res;
        }

        private void swap(int i, int j) {
            int t = heap[i];
            heap[i] = heap[j];
            heap[j] = t;
            heapRev[heap[i]] = i;
            heapRev[heap[j]] = j;
        }
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
        new P5().run();
    }

    private void run() throws FileNotFoundException {
        br = new BufferedReader(new FileReader("input.txt"));
        out = new PrintWriter("output.txt");
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}