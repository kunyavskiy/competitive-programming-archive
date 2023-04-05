import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

public class P7 {

    class Rg {
        String s;
        char top;

        Pattern p;

        public Rg(String s, char top) {
            this.s = s;
            this.top = top;
        }
    }

    private void solve() throws IOException {
        List<Rg> r[] = new List[16];
        r[0] = new ArrayList<>();
        r[1] = new ArrayList<>();
        r[1].add(new Rg("a", '.'));
        r[1].add(new Rg("t", '.'));
        r[1].add(new Rg("c", '.'));
        r[1].add(new Rg("g", '.'));
        for (int i = 2; i < r.length; i++) {
            r[i] = new ArrayList<>();
            for (int j = 1; j < i - 2; j++) {
                for (Rg s1 : r[j]) {
                    for (Rg s2 : r[i - 2 - j]) {
                        if (s2.top != '+')
                            r[i].add(new Rg("(" + s1.s + s2.s + ")", '+'));
                    }
                }
            }
            for (int j = 1; j < i - 3; j++) {
                for (Rg s1 : r[j]) {
                    for (Rg s2 : r[i - 3 - j]) {
                        if (s1.s.compareTo(s2.s) < 0 && s2.top != '|')
                            r[i].add(new Rg("(" + s1.s + "|" + s2.s + ")", '|'));
                    }
                }
            }
            if (i >= 3) {
                for (Rg s1 : r[i - 3]) {
                    if (s1.top != '*')
                        r[i].add(new Rg("(" + s1.s + "*)", '*'));
                }
            }
//            out.println(i + " " + r[i].size());
        }

        for (List<Rg> rgs : r) {
            for (Rg rg : rgs) {
                rg.p = Pattern.compile(rg.s);
            }
        }

        int n = nextInt();
        for (int i = 0; i < n; i++) {
            int m = nextInt();
            String[] s = new String[m];
            for (int j = 0; j < m; j++) {
                int k = nextInt();
                s[j] = k == 0 ? "" : next();
            }
            boolean found = false;
            for (int l = 1; l < r.length; l++) {
                for (Rg rg : r[l]) {
                    boolean ok = true;
                    for (int j = 0; j < m; j++) {
//                        try {
                            if (!rg.p.matcher(s[j]).matches()) {
                                ok = false;
                                break;
                            }
//                        } catch (Throwable e) {
//                            out.println(rg.s);
//                            throw e;
//                        }
//                        if (!s[j].matches(rg.s)) ok = false;
                    }
                    if (ok) {
                        out.println(rg.s);
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (!found) {
                out.println("(((a|c)|(t|g))*)");
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
        new P7().run();
//        Thread thread = new Thread() {
//            @Override
//            public void run() {
//                try {
//                    new P7().run();
//                } catch (FileNotFoundException e) {
//                    e.printStackTrace();
//                }
//            }
//        };


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