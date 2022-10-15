import java.io.*;
import java.lang.*;
import java.util.*;
import java.awt.geom.*;

public class p1215
{

    void solve() throws IOException{
        Path2D.Double a = new Path2D.Double();

        int x = nextInt(),y=nextInt();

        int n = nextInt();
        int firstx = nextInt(),firsty = nextInt();
        int lastx = firstx, lasty = firsty;

        a.moveTo(firstx,firsty);
        
        double ans = 1e100;

        for (int i = 1; i < n; i++){
            int nx = nextInt(),ny = nextInt();
            a.lineTo(nx,ny);
            ans = Math.min(ans,Line2D.ptSegDist(lastx,lasty,nx,ny,x,y));
            lastx = nx;
            lasty = ny;
        }
        ans = Math.min(ans,Line2D.ptSegDist(lastx,lasty,firstx,firsty,x,y));
        a.lineTo(firstx,firsty);
        if (a.contains(x,y))
            out.println("0.000\n");
        else
            out.printf(Locale.US, "%.3f\n", ans*2);
    }

    public static void main(String[] args) throws IOException{
        new p1215().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {                               
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            in.close();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }       
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        return tokenizer.nextToken();
    }

}                                    
