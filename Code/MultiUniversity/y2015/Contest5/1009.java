import java.math.*;
import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    void run() {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        BigInteger F[] = new BigInteger[1000 + 1];
        F[0] = BigInteger.ZERO;
        F[1] = BigInteger.ONE;
        for (int i = 2; i < F.length; ++ i) {
            F[i] = F[i - 1].add(F[i - 2]);
        }
        int cas = in.nextInt();
        while (cas-- > 0) {
            int n = in.nextInt();
            BigInteger m = in.nextBigInteger();
            if (m.compareTo(BigInteger.valueOf(2)) <= 0) {
                out.println(0);
                out.flush();
                continue;
            }
            if (m.equals(BigInteger.valueOf(3))) {
                out.println(1);
                out.flush();
                continue;
            }
            int x = 0;
            while (x < 1000 && F[x + 1].compareTo(m) <= 0) ++ x;
            if (F[x].equals(m)) {
                out.println(F[x - 2].mod(MOD));
                out.flush();
                continue;
            }
            if (F[x + 1].equals(m.add(BigInteger.ONE))) {
                out.println(F[x - 1].subtract(BigInteger.ONE).mod(MOD));
                out.flush();
                continue;
            } else {
                out.println(m.subtract(F[x]).add(F[x - 2]).mod(MOD));
                out.flush();
                continue;
            }
            /*
            if ((m.subtract(F[x])).compareTo(F[x - 3].add(BigInteger.ONE)) <= 0) {
                out.println("FUCK");
                out.println(F[x - 2].add(m).subtract(F[x]));//.mod(MOD));
                out.flush();
                continue;
            }
            out.println("x = " + x + " F[x] = " + F[x]);
            out.println(m.subtract(F[x]));//.mod(MOD));
            out.flush();
            */
        }
        in.close();
        out.close();
    }

    final BigInteger MOD = BigInteger.valueOf(258280327);
}
