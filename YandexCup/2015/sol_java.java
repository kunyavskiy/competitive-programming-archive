import java.io.*;
import java.lang.*;
import java.util.*;

public class sol_java
{

    void reverse(char str[], int i, int j) {
      while (i < j) {
	char c = str[i];
	str[i] = str[j];
	str[j] = c;
	i++;
	j--;
      }
    }

    int compare(char a[], char b[]){
      for (int i = 0; i < a.length; i++)
	  if (a[i] != b[i])
	      return a[i] - b[i];
      return 0;
    }

    void solve() throws IOException {
        char str[] = nextToken().toCharArray();
	char hstr[] = null;
        int n = str.length;
	out.println(n);
        int cnt[] = new int[256];
        for (int i = 0; i < n; i++)
            cnt[str[i] - 'a']++;
        int p = 0;
        int nstart = -1;
        for (int i = 0; i < n; i++) {
            while (cnt[p] == 0)
                p++;
            if ((str[i] - 'a') != p) {
                nstart = i;
                break;
            }
            cnt[str[i] - 'a']--;
        }

        if (nstart == -1) {
            out.println(str);
            return;
        }

        int i = n - 1;
        while (i >= nstart) {
            int j = i - 1, k = i;
            while (j >= nstart) {
                if (str[j] == str[k]) {
                    j--;
                    k--;
                    continue;
                }
                if (str[j] > str[k]) {
                    j--;
                    k = i;
                    continue;
                }
                break;
            }
            if (j < nstart) {
		hstr = str.clone();
                out.println(new String(hstr) + " " + i + " " + j);
		reverse(hstr, i + 1, j);
                out.println(new String(hstr));
		while (i >= k) {
                    i -= k - j;
                }
		reverse(str, i + 1, j);
                break;
            } else {
                while (i >= k) {
                    i -= k - j;
                }    
            }
        }

        if (compare(str, hstr) > 0)
            str = hstr;

        out.println(new String(str));
    }

    public static void main(String[] args) throws IOException{
        new sol_java().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {                               
            Reader reader = new InputStreamReader(System.in);
            Writer writer = new OutputStreamWriter(System.out);
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
