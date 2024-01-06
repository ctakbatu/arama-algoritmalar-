//lineer arama
#include <stdio.h>

int main() {
    int arr[] = {4, 6, 12, 8, 5, 15, 25, 34};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 34;
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == x) {
            printf("%d index icinde bulundu %d\n", x, i);
            break;
        }
    }
    if (i == n) {
        printf("%d bulunamadi\n", x);
    }
    return 0;
}
