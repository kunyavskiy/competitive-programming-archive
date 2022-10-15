import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;
import java.util.regex.*;

public class p1074
{

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    void solve() throws IOException{
        while (true){
           try {
              String s = in.readLine();             
              //System.err.println(s);
              if (s.equals("#"))
                break;
              int len = Integer.parseInt(in.readLine());

              if (!Pattern.compile("[\\+\\-]?([0-9]*\\.)?[0-9]+(([eE][\\+\\-]?)?[0-9]+)?").matcher(s).matches()){
                throw new NumberFormatException();
              }

              BigDecimal bd;

              try {
                 bd = new BigDecimal(s);
              }
              catch (NumberFormatException e){
                 bd = new BigDecimal(0);
              }         
              String _str = String.format(Locale.US,"%.1000f", bd);
              char[] str = _str.toCharArray();
              StringBuilder sb = new StringBuilder();
              int pos = -1000000;
              boolean any = false;
              for (int i = 0; i < _str.length(); i++){
                pos++;
                if (str[i] == '.')
                    pos = 0;
                if (pos > len || (pos == 0 && len == 0))
                    break;
                if ('1' <= str[i] && str[i] <= '9')
                    any = true;
                sb.append(str[i]);
              } 
              String res = sb.toString();
              if (res.charAt(0) == '-' && !any){
                res = res.substring(1);
              }

              String sign = "";

              if (res.charAt(0) == '-'){
                sign = "-";
                res = res.substring(1);
              }

              while (res.length() != 0 && (res.charAt(0) == '0'))
                res = res.substring(1);

              if (res.length() == 0 || res.charAt(0) == '.')
                res = "0"+res;

              out.println(sign+res);
           } catch (Exception e){
               //if (!oj) e.printStackTrace();
               out.println("Not a floating point number");
           }
        }
    }

    public static void main(String[] args) throws IOException{
        new p1074().run();
    }

    boolean oj;
                     
    public void run() throws IOException
    {
        try {                               
            oj = System.getProperty("ONLINE_JUDGE") != null;
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
