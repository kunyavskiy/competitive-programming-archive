import java.io.*;
import java.math.BigInteger;
import java.util.*;

import static java.lang.System.exit;

/**
 * Created with IntelliJ IDEA.
 * User: user11
 * Date: 25.01.13
 * Time: 13:40
 * To change this template use File | Settings | File Templates.
 */
public class p1951 {

    static Scanner in;
    PrintWriter out;

    private class rational
    {
        public BigInteger num, den;
        rational ()
        {
            this.num = BigInteger.ZERO;
            this.den = BigInteger.ONE;
        }
        rational (BigInteger num, BigInteger den)
        {
            this.num=num;
            this.den=den;
            this.norm();
        }
        rational (BigInteger num)
        {
            this.num=num;
            this.den=BigInteger.ONE;
            this.norm();
        }

        void norm ()
        {
            BigInteger d=num.abs().gcd(den.abs());
            if (d.equals(BigInteger.ZERO)) {
                num=BigInteger.ZERO;
                den=BigInteger.ONE;
                return;
            }
            num=num.divide(d); den=den.divide(d);
            if (den.compareTo(BigInteger.ZERO)<0) {
                den=den.negate(); num=num.negate();
            }
        }
        rational multiply (rational a)
        {
            rational ret = new rational(num.multiply(a.num),den.multiply(a.den));
            ret.norm();
            return ret;
        }
        rational divide (rational a)
        {
            rational ret = new rational(num.multiply(a.den),den.multiply(a.num));
            ret.norm();
            return ret;
        }
        rational add (rational a)
        {
            rational ret = new rational(num.multiply(a.den).add(a.num.multiply(den)),den.multiply(a.den));
            ret.norm();
            return ret;
        }
        rational subtract (rational a)
        {
            rational ret = new rational(num.multiply(a.den).subtract(a.num.multiply(den)),den.multiply(a.den));
            ret.norm();
            return ret;
        }
        rational negate ()
        {
            return new rational(num.negate(),den);
        }
        boolean equals (rational a)
        {
            return num.equals(a.num) && den.equals(a.den);
        }

        public String out() {
            return "("+num.toString()+"/"+den.toString()+")";
        }
    }

    private class complex
    {
        rational re, im;
        complex ()
        {
            re= new rational();
            im = new rational();
        }
        complex(rational a, rational b)
        {
            re=a;
            im=b;
        }
        rational abs ()
        {
            return re.multiply(re).add(im.multiply(im));
        }
        complex inv ()
        {
            rational a = abs();
            complex ret = new complex(re.divide(a),im.negate().divide(a));
            return ret;
        }
        complex multiply (complex a)
        {
            return new complex(re.multiply(a.re).subtract(im.multiply(a.im)),im.multiply(a.re).add(re.multiply(a.im)));
        }
        complex divide (complex a)
        {
            return this.multiply(a.inv());
        }
        void read ()
        {
            re= new rational(BigInteger.valueOf(in.nextLong()));
            im = new rational(BigInteger.valueOf(in.nextLong()));
        }
        boolean equals (complex a)
        {
            return re.equals(a.re) && im.equals(a.im);
        }
        String out ()
        {
            return "re = "+re.out() + "  im=" + im.out();
        }
    }

    void solve(){
            in = new Scanner(System.in);
            out = new PrintWriter(System.out);
        complex xn = new complex();
        complex xm = new complex();
        xn.read();
        int n=in.nextInt();
        xm.read();
        int m=in.nextInt();
        gen(n,xn,m,xm);
        out.close();
    }

    private void gen(int n, complex xn, int m, complex xm) {
       // System.out.println(n+" "+xn.out()+" "+m+"  "+xm.out()+"  xm.inv()=  "+xm.inv().out()+"  xm.abs()= "+xm.abs().out());
        if (n==m)
        {
            if (xn.equals(xm))
            {
                out.println(n);
            } else {
                out.println(0);
            }
            return;
        }
        if (n<m) {
            gen(m,xm,n,xn);
            return;
        }
        gen(n-m,xn.divide(xm),m,xm);
    }

    public static void p1951(String[] args) {
        try {
            new p1951().solve();
        } catch (Exception e) {
            exit(1);
        }
    }
}
