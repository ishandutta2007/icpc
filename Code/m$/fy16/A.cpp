#include <bits/stdc++.h>

char str[20000 + 5];
int n;

void work() {
    bool first = true;
    int count = 0;
    bool was = false;
    for (int i = 0; str[i]; ++ i) {
        if (str[i] == ' ') {
            count ++;
            continue;
        }
        if (str[i] == '.') {
            count = 0;
            first = true;
        }
        if (str[i] == ',') {
            count = 0;
        }
        if (isalpha(str[i])) {
            str[i] = tolower(str[i]);
            if (first) {
                first = false;
                count = 0;
                str[i] = toupper(str[i]);
                if (was) {
                    putchar(' ');
                }
                was = true;
            }
        }
        if (count) {
            putchar(' ');
            count = 0;
        }
        putchar(str[i]);
        if (str[i] == ',') {
            count = 1;
        }
        continue;
    }
    puts("");
}

int main() {
    while (gets(str) != NULL) {
        work();
    }
}
