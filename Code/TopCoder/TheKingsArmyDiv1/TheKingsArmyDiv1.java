import java.io.*;
import java.util.*;

public class TheKingsArmyDiv1 {
	public int getNumber(String[] state) {
		int n = state[0].length();
		char[][] mat = new char[2][n];
		mat[0] = state[0].toCharArray();
		mat[1] = state[1].toCharArray();
		{
			boolean flag = false;
			for (int i = 0; i < 2; ++ i) {
				for (int j = 0; j < n; ++ j) {
					if (mat[i][j] == 'H')
						flag = true;
				}
			}
			if (!flag) return -1;
		}
		int[][][] dp = new int[n][n][3];
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				for (int k = 0; k < 3; ++ k) {
					dp[i][j][k] = INF;
				}
			}
		}
		for (int i = 0; i < 2; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (mat[i][j] == 'H')
					dp[j][j][i] = 0;
				if (mat[i][j] == 'H' && mat[i^1][j] == 'H')
					dp[j][j][2] = 0;
			}
		}
		for (int length = 2; length <= n; ++ length) {
			for (int i = 0; i+length-1 < n; ++ i) {
				int j = i+length-1;
				for (int k = i; k < j; ++ k) {
					for (int r = 0; r < 3; ++ r) {
						dp[i][j][r] = Math.min(
								dp[i][j][r],
								dp[i][k][r]+dp[k+1][j][r]);
					}
				}
				for (int r = 0; r < 2; ++ r) {
					{
						int dt = dp[i+1][j][r];
						if (mat[r][i] == 'S')
							dt ++;
						dp[i][j][r] = Math.min(dp[i][j][r],
								dt);
					}
					{
						int dt = dp[i][j-1][r];
						if (mat[r][j] == 'S')
							dt ++;
						dp[i][j][r] = Math.min(dp[i][j][r],
								dt);
					}
				}
				dp[i][j][2] = Math.min(dp[i][j][2],
						Math.min(dp[i+1][j][2],dp[i][j-1][2])+1);
				dp[i][j][2] = Math.min(dp[i][j][2],
						Math.min(dp[i][j][0],dp[i][j][1])+1);
				dp[i][j][0] = Math.min(dp[i][j][2],
						dp[i][j][0]);
				dp[i][j][1] = Math.min(dp[i][j][2],
						dp[i][j][1]);
			}
		}
		return dp[0][n-1][2];
	}

	static final int INF = 0x3f3f3f3f;

	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("TheKingsArmyDiv1 (500 Points)");
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

			String[] state = new String[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < state.length; ++i)
				state[i] = Reader.nextLine();
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(state, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1419700415;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(String[] state, int __expected) {
		for (int i = 0; i < state.length; i++) {
			state[i] = new String(state[i]);
		}
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TheKingsArmyDiv1 instance = new TheKingsArmyDiv1();
		int __result = 0;
		try {
			__result = instance.getNumber(state);
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
		private static final String dataFileName = "TheKingsArmyDiv1.sample";
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
