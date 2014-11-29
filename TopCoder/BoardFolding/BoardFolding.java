import java.io.*;
import java.util.*;

public class BoardFolding {
	public int howMany(int n, int m, String[] compressedPaper) {
		boolean[][] mat = new boolean[n][m];
		boolean[][] tmat = new boolean[m][n];
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
					mat[i][j] = tmat[j][i] = (toNumber(compressedPaper[i].charAt(j/6))>>(j%6)&1)==1;
		return calc(n,m,mat) * calc(m,n,tmat);
	}

	int toNumber(char c) {
		if (c>='0' && c<='9') return c-'0';
		if (c>='a' && c<='z') return c-'a'+10;
		if (c>='A' && c<='Z') return c-'A'+36;
		if (c == '#') return 62;
		if (c == '@') return 63;
		return -1;
	}

	int calc(int n,int m,boolean[][] mat) {
		int[] diameter = new int[n];
		for (int i = 0; i < n; ++ i) {
			int p = 0,tp = 1;
			while (i+1-tp>=0 && i+tp<n) {
				boolean ok = true;
				for (int j = 0; j < m; ++ j)
					if (mat[i+1-tp][j] != mat[i+tp][j])
						ok = false;
				if (ok == false) break;
				p = tp ++;
			}
			diameter[i] = p;
		}
		boolean[][] dp = new boolean[n][n];
		dp[0][n-1] = true;
		for (int len = n; len >= 1; -- len) {
			for (int i = 0; i+len-1 < n; ++ i) {
				if (dp[i][i+len-1] == false) continue;
				for (int j = i; j < i+len-1; ++ j) {
					if (j-i+1<=i+len-1-j && diameter[j]>=j-i+1)
						dp[j+1][i+len-1] = true;
					if (j-i+1>=i+len-1-j && diameter[j]>=i+len-1-j)
						dp[i][j] = true;
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = i; j < n; ++ j)
				if (dp[i][j])
					ret ++;
		return ret;
	}

	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("BoardFolding (500 Points)");
		System.err.println();
		HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
        runTest(cases);
	}

	static void runTest(HashSet<Integer> caseSet) {
	    int cases = 0, passed = 0;
	    while (true) {
	    	String label = Reader.nextLine();
	    	if (label == null || !label.startsWith("--"))
	    		break;

            int N = Integer.parseInt(Reader.nextLine());
            int M = Integer.parseInt(Reader.nextLine());
            String[] compressedPaper = new String[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < compressedPaper.length; ++i)
                compressedPaper[i] = Reader.nextLine();
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, M, compressedPaper, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1417190421;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int M, String[] compressedPaper, int __expected) {
		for (int i = 0; i < compressedPaper.length; i++) {
			compressedPaper[i] = new String(compressedPaper[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		BoardFolding instance = new BoardFolding();
		int __result = 0;
		try {
			__result = instance.howMany(N, M, compressedPaper);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "BoardFolding.sample";
	    private static BufferedReader reader;

	    public static String nextLine() {
	        try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
	        }
	        catch (IOException e) {
	            System.err.println("FATAL!! IOException");
	            e.printStackTrace();
	            System.exit(1);
	        }
	        return "";
	    }
	}
// CUT end
}
