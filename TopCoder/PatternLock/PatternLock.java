import java.io.*;
import java.util.*;

public class PatternLock {
	public int solve(int n, int MOD) {
		int[][] dp = new int[n+1][n+1];
		dp[0][0] = 1;
		int[] count = new int[n+1];
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (dp[i][j] == 0) continue;
				int dt = dp[i][j] << 1;
				if (dt >= MOD)
					dt -= MOD;
				dp[i][j+1] += dt;
				if (dp[i][j+1] >= MOD)
					dp[i][j+1] -= MOD;
				if (j+1 != n) {
					dp[i+1][j+1] += (long) dp[i][j] * (n-j) % MOD;
					if (dp[i+1][j+1] >= MOD)
						dp[i+1][j+1] -= MOD;
				} else {
					count[i+1] += (long) dp[i][j] * (n-j) % MOD;
					if (count[i+1] >= MOD)
						count[i+1] -= MOD;
				}
			}
		}
		int ret = 0;
		for (int i = 1; i <= n; ++ i) {
			ret += (long) count[i] * count[i] % MOD;
			if (ret >= MOD)
				ret -= MOD;
			if (i != 1) {
				ret += (long) count[i] * count[i-1] % MOD;
				if (ret >= MOD)
					ret -= MOD;
			}
		}
		ret <<= 1;
		if (ret >= MOD)
			ret -= MOD;
		return ret;
	}

	void debug(Object... o) {
		System.err.println(Arrays.deepToString(o));
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("PatternLock (900 Points)");
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
			int MOD = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(N, MOD, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1419341457;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int MOD, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		PatternLock instance = new PatternLock();
		int __result = 0;
		try {
			__result = instance.solve(N, MOD);
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
		private static final String dataFileName = "PatternLock.sample";
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
