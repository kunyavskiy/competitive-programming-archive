
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class A {

    List<Square> all = new ArrayList<>();
    Square empty = new Square();

    class Square {
        boolean full;
        Square a, b, c, d;
        List<Square> nb = new ArrayList<>();
        public boolean visited;

        public Square() {
            all.add(this);
        }
    }

    private void solve() throws IOException {
        empty.a = empty.b = empty.c = empty.d = empty;
        Square root = parse();
        process(root, empty, empty, empty, empty);
        int res = 0;
        for (Square square : all) {
            if (square.full) {
                if (!square.visited) {
                    res++;
                    dfs(square);
                }
            }
        }
        out.println(res);
    }

    private void dfs(Square x) {
        if (x.visited) return;
        x.visited = true;
        for (Square y : x.nb) {
            dfs(y);
        }
    }

    private void process(Square x, Square l, Square r, Square t, Square b) {
        if (x == empty) return;
        if (x.full) {
            for (Square y : new Square[]{l, r, t, b}) {
                if (y.full) {
                    y.nb.add(x);
                    x.nb.add(y);
                }
            }
        } else {
            process(x.a, l.b, x.b, t.c, x.c);
            process(x.b, x.a, r.a, t.d, x.d);
            process(x.c, l.d, x.d, x.a, b.a);
            process(x.d, x.c, r.c, x.b, b.b);
        }
    }

    private Square parse() throws IOException {
        int x = nextInt();
        if (x == 0) {
            return empty;
        } else if (x == 1) {
            Square res = new Square();
            res.full = true;
            res.a = res.b = res.c = res.d = res;
            return res;
        } else {
            Square res = new Square();
            res.a = parse();
            res.b = parse();
            res.d = parse();
            res.c = parse();
            return res;
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