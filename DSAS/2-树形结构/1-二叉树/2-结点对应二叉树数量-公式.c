#include <stdio.h>

int factorial(int n){
    long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("%d", factorial(2*n) / (factorial(n) * factorial(n + 1)));
}