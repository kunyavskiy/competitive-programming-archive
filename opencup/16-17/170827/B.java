import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Created by pavel on 27.08.17.
 */
public class B {
    private Scanner in;
    private PrintWriter out;
    private int r;

    public static void main(String[] args) {
//        for (int a = 0; a <= 2; a++) {
//            for (int b = 0; b <= 2; b++) {
//                for (int c = 0; c <= 2; c++) {
//                    for (int d = 0; d <= 2; d++) {
//                        for (int e = 0; e <= 2; e++) {
//                            secret[0] = a;
//                            secret[1] = b;
//                            secret[2] = c;
//                            secret[3] = d;
//                            secret[4] = e;
//                            new B().run();
//                        }
//                    }
//                }
//            }
//        }
        new B().run();
    }

    private void run() {
        in = new Scanner(System.in);
        out = new PrintWriter(System.out);


        int d = in.nextInt();
        r = in.nextInt();
        int len = r + 1;
        int[] x = new int[d];
        for (int i = 0; i < d; i++) {
            x[i] = 0;
        }
        while (len > 2) {
//            System.out.println(len + " " + Arrays.toString(x));
            int[] xx = new int[d];
            if (len % 2 == 1) {
                for (int i = 0; i < d; i++) {
                    int[] q = new int[d];
                    for (int j = 0; j < d; j++) {
                        q[j] = x[j] + (len / 2);
                    }
                    q[i] = x[i];
                    ask(q);
                    q[i] = x[i] + len - 1;
                    if (ask(q)) {
                        xx[i] = x[i] + len / 2;
                    } else {
                        xx[i] = x[i];
                    }
                }
                len = len / 2 + 1;
            } else {
                for (int i = 0; i < d; i++) {
                    int[] q = new int[d];
                    for (int j = 0; j < d; j++) {
                        q[j] = x[j] + (len / 2);
                    }
                    q[i] = x[i];
                    ask(q);
                    q[i] = x[i] + len - 1;
                    if (ask(q)) {
                        xx[i] = x[i] + len / 2 - 1;
                    } else {
                        xx[i] = x[i];
                    }
                }
                len = len / 2 + 1;
            }
            x = xx;
        }
//        System.out.println(" " + Arrays.toString(x));
        int[] c = new int[d];
        for (int i = 0; i < d; i++) {
            if (x[i] > 0) {
                c[i] = x[i];
            } else {
                c[i] = x[i] + 1;
            }
        }
        boolean all = true;
        int[] res = new int[d];
        for (int i = 0; i < d; i++) {
            int[] q = c.clone();
            int dd = 0;
            if (c[i] == x[i]) {
                dd = -1;
            } else {
                dd = 1;
            }
            q[i] += dd;
            ask(q);
            q[i] -= dd;
            if (ask(q)) {
                res[i] = c[i] - dd;
            } else {
                res[i] = c[i];
                all = false;
            }
        }
        if (all) {
            int[] q = c.clone();
            for (int i = 0; i < d; i++) {
                if (c[i] == x[i]) {
                    q[i]++;
                } else {
                    q[i]--;
                }
            }
            ask(c);
            if (ask(q)) {
                res = q;
            } else {
                res = c;
            }
        }
        out.print("! ");
        for (int i : res) {
            out.print(i + " ");
        }
        out.println();
        out.flush();
    }

    int lastd = Integer.MAX_VALUE;
    static int[] secret = {0, 2, 0, 2, 0};

    boolean first = true;

    private boolean ask(int[] q) {
        for (int i : q) {
            if (i < 0 || i > r) {
                throw new RuntimeException();
            }
        }
//        int d = 0;
//        for (int i = 0; i < q.length; i++) {
//            d = Math.max(d, Math.abs(q[i] - secret[i]));
//        }
////        System.out.println(Arrays.toString(q) + " " + d);
//        if (d < lastd) {
//            lastd = d;
//            return true;
//        } else {
//            lastd = d;
//            return false;
//        }
        out.print("? ");
        for (int i : q) {
            out.print(i + " ");
        }
        out.println();
        out.flush();
        String s = in.next();
        return s.equals("hotter");
    }
}
