import java.io.*;
import java.util.*;

public class WaitingForBus {
	public double whenWillBusArrive(int[] time, int[] prob, int s) {
		int n = time.length;
		int mx = 0;
		for (int i = 0; i < n; ++ i) {
			mx = Math.max(mx,time[i]);
		}
		double[] dp = new double[s+mx+1];
		dp[0] = 1.;
		for (int i = 1; i < dp.length; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (i-time[j] < 0) continue;
				if (i-time[j] >= s) continue;
				dp[i] += dp[i-time[j]] * (double)prob[j] / 100;
			}
		}
		double ret = 0;
		for (int i = s; i < dp.length; ++ i)
			ret += (i-s) * dp[i];
		return ret;
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("WaitingForBus (250 Points)");
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

            int[] time = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < time.length; ++i)
                time[i] = Integer.parseInt(Reader.nextLine());
            int[] prob = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < prob.length; ++i)
                prob[i] = Integer.parseInt(Reader.nextLine());
            int s = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            double __answer = Double.parseDouble(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(time, prob, s, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1418781775;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] time, int[] prob, int s, double __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		WaitingForBus instance = new WaitingForBus();
		double __result = 0.0;
		try {
			__result = instance.whenWillBusArrive(time, prob, s);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (doubleEquals(__expected, __result)) {
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

	static boolean doubleEquals(double a, double b) {
	    return !Double.isNaN(a) && !Double.isNaN(b) && Math.abs(b - a) <= 1e-9 * Math.max(1.0, Math.abs(a) );
	}

	static class Reader {
        private static final String dataFileName = "WaitingForBus.sample";
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
