#include <bits/stdc++.h>

int main() {
    system("G_gen.exe");
    system("G.exe");
    system("G_brute.exe");
    FILE *fa = fopen("G_brute.out","r");
    FILE *fb = fopen("G.out","r");
    int a,b;
    while (fscanf(fa,"%d",&a) == 1) {
        fscanf(fb,"%d",&b);
        if (a != b) {
            puts("fuck");
            break;
        }
    }
    fclose(fa);
    fclose(fb);
}
