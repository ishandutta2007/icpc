import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    void run() {
        BigDecimal answer[] = new BigDecimal[50];

        long dp[][][] = new long[51 + 1][2][52 * 51 / 2 + 1];
        dp[0][0][0] = 1;
        for (int prev = 0; prev < 51; ++ prev) {
            for (int parity = 0; parity < 2; ++ parity) {
                for (int has = 0; has <= (prev + 1) * prev / 2; ++ has) {
                    if (dp[prev][parity][has] == 0) continue;
                    for (int next = prev + 1; next <= 51; ++ next) {
                        dp[next][parity ^ 1][has + (next - prev) * (next - 1 - prev) / 2]
                            += dp[prev][parity][has];
                    }
                }
            }
        }

        for (int n = 1; n <= 50; ++ n) {
            answer[n - 1] = BigDecimal.ZERO;
            for (int parity = 0; parity < 2; ++ parity) {
                for (int has = 0; has < (n + 1) * n / 2; ++ has) {
                    BigDecimal tmp = BigDecimal.ONE.divide(BigDecimal.ONE.subtract(BigDecimal.valueOf(has).divide(BigDecimal.valueOf(
                                        (n + 1) * n / 2),50,BigDecimal.ROUND_HALF_EVEN)),50,
                            BigDecimal.ROUND_HALF_EVEN).multiply(BigDecimal.valueOf(dp[n + 1][parity ^ 1][has]));
                    if (parity == 0)
                        answer[n - 1] = answer[n - 1].subtract(tmp);
                    else
                        answer[n - 1] = answer[n - 1].add(tmp);
                }
            }
        }

        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int cas = in.nextInt();
        for (int ca = 1; ca <= cas; ++ ca) {
            int n = in.nextInt();
            out.println(String.format("%.15f",answer[n - 1]));
        }
        in.close();
        out.close();
    }

}
