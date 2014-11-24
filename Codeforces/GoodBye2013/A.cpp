#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
int main() {
        int a,b,left = 0;
        cin >> a >> b;
        int ans = 0;
        while (a) {
                ans += a;
                a +=left;
                left = a%b;
                a /= b;
        }
        cout << ans << endl;
        return 0;
}