
import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
import java.util.StringTokenizer;

public class P3 {

    private static final double EPS = 1e-10;
    private Scanner in;

    final static boolean DEBUG = false;

    public static void main(String[] args) throws FileNotFoundException {
        if (DEBUG) {
            Random random = new Random(12312312312231L);
            while (true) {
                P3 p3 = new P3();
                for (int i = 0; i < 3; i++) {
                    p3.xx[i] = random.nextInt(2001) - 1000;
                    p3.yy[i] = random.nextInt(2001) - 1000;
                }
                p3.run();
                for (int i = 0; i < 3; i++) {
                    if(!p3.printed[i]) {
                        System.out.println(Arrays.toString(p3.xx) + " " + Arrays.toString(p3.yy));
                        throw new AssertionError();
                    }
                }
            }
        } else {
            new P3().run();
        }
    }

    private void run() throws FileNotFoundException {
        in = new Scanner(System.in);

        int x1 = binsearch(1, 0);
        int x2 = -binsearch(-1, 0);
        int y1 = binsearch(0, 1);
        int y2 = -binsearch(0, -1);

        if (request(1, 1, x1 + y1 + 1)) {
        } else if (request(-1, -1, -x2 -y2 + 1)) {
            mx = my = -1;
        } else if (request(1, -1, x1 - y2 + 1)) {
            my = -1;
        } else {
            mx = -1;
        }

        if (mx == -1) {
            int t = x1; x1 = -x2; x2 = -t;
        }
        if (my == -1) {
            int t = y1; y1 = -y2; y2 = -t;
        }

        if (request(-1, -1, -x2 -y2 + 1)) {
            // ZHOPA!!!

            {
                int a = y1 - y2;
                int b = x2 - x1;
                int c = x1 * a + y1 * b;
                if (request(a, b, c)) {
                    // niz
                    swap = true;
                    int t = x1;
                    x1 = y1;
                    y1 = t;
                    t = x2;
                    x2 = y2;
                    y2 = t;
                }
            }
            double xp, yp;
            {
                double l = x1, r = x2;
                for (int i = 0; i < 60; i++) {
                    double m = (l + r) * 0.5;
                    double a = y2 - y1;
                    double b = x1 - m;
                    double c = a * x1 + b * y1;
                    if (request(a, b, c)) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
                xp = l;
            }
            {
                double l = y1, r = y2;
                for (int i = 0; i < 60; i++) {
                    double m = (l + r) * 0.5;
                    double a = y2 - m;
                    double b = x1 - x2;
                    double c = a * x2 + b * y2;
                    if (request(a, b, c)) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
                yp = l;
            }
            double a1 = y2 - y1;
            double b1 = x1 - xp;
            double c1 = a1 * x1 + b1 * y1;
            double a2 = y2 - yp;
            double b2 = x1 - x2;
            double c2 = a2 * x2 + b2 * y2;

            double dx = c1 * b2 - c2 * b1;
            double dy = a1 * c2 - a2 * c1;
            double d = a1 * b2 - a2 * b1;

            double x = dx / d;
            double y = dy / d;

            if (DEBUG) {
                System.out.println("FIRST CASE");
                System.out.println(a1 * x + b1 * y - c1);
                System.out.println(a2 * x + b2 * y - c2);
                if (Math.abs(a1 * x + b1 * y - c1) > 1e-7) {
                    throw new AssertionError("Bad line 1: " + Math.abs(a1 * x + b1 * y - c1));
                }
                if (Math.abs(a2 * x + b2 * y - c2) > 1e-7) {
                    throw new AssertionError("Bad line 2: " + Math.abs(a2 * x + b2 * y - c2));
                }
            }


            System.out.print("! ");
            print(x1, y1);
            print(x2, y2);
            print(x, y);
            System.out.println();
        } else {
            if (DEBUG) {
                System.out.println("SECOND CASE");
            }
            int[] resx = new int[3];
            int[] resy = new int[3];
            resx[0] = x1;
            resy[0] = y1;
            {
                int l = x1;
                int r = x2 + 1;
                while (r > l + 1) {
                    int m = (l + r) / 2;
                    int a = y2 - y1;
                    int b = x1 - m;
                    int c = a * x1 + b * y1;
                    if (request(a, b, c)) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
                resx[1] = l;
                resy[1] = y2;
            }
            {
                int l = y1;
                int r = y2 + 1;
                while (r > l + 1) {
                    int m = (l + r) / 2;
                    int a = y1 - m;
                    int b = x2 - x1;
                    int c = a * x1 + b * y1;
                    if (request(a, b, c)) {
                        r = m;
                    } else {
                        l = m;
                    }
                }
                resx[2] = x2;
                resy[2] = l;
            }
            System.out.print("! ");
            for (int i = 0; i < 3; i++) {
                print(resx[i], resy[i]);
            }
            System.out.println();
        }
    }

    private void print(double x, double y) {
        if (swap) {
            double t = x; x = y; y = t;
        }
        x *= mx;
        y *= my;
        int xx = (int) Math.round(x);
        int yy = (int) Math.round(y);
        if (DEBUG) {
            for (int i = 0;i < 3; i++) {
                if (this.xx[i] == xx && this.yy[i] == yy) printed[i] = true;
            }
        }
        System.out.print(Math.round(x) + " " + Math.round(y) + " ");
    }

    int mx = 1;
    int my = 1;
    boolean swap = false;

    private int binsearch(int a, int b) {
        int l = -1000;
        int r = 1001;
        while (r > l + 1) {
            int m = (l + r) / 2;
            if (request(a, b, m)) {
                r = m;
            } else {
                l = m;
            }
        }
        return l;
    }

    int[] xx = new int[]{0, 10, 7};
    int[] yy = new int[]{0, 10, 5};
    boolean[] printed = new boolean[3];

    private boolean request(double a, double b, double c) {
        if (swap) {
            double t = a; a = b; b = t;
        }
        a *= mx;
        b *= my;
        double d = Math.hypot(a, b);
        a /= d;
        b /= d;
        c /= d;
        if (DEBUG) {
            for (int i = 0; i < 3; i++) {
                if (xx[i] * a + yy[i] * b < c - EPS) return true;
            }
            return false;
        } else {
            System.out.printf("? %.15f %.15f %.15f\n", a, b, c);
            System.out.flush();
            double p = in.nextDouble();
            double q = in.nextDouble();
            return p > EPS;
        }
//        System.out.println(a + " " + b + " " + c);
//        if (!(Math.abs(a) <= 2000 && Math.abs(b) <= 2000 && Math.abs(c) <= 4000000 && a * a + b * b <= 4000000)) {
//            throw new AssertionError();
//        }
    }

}