//İKİLİ LİSTE

#include <stdio.h>

int ikiliArama(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Eğer ortadaki eleman aranan sayıya eşitse, bulduk.
        if (arr[mid] == key)
            return mid;

        // Eğer ortadaki eleman aranan sayıdan küçükse, sağ tarafı ara.
        if (arr[mid] < key)
            low = mid + 1;

        // Eğer ortadaki eleman aranan sayıdan büyükse, sol tarafı ara.
        else
            high = mid - 1;
    }

    // Sayı bulunamadıysa -1 döndür.
    return -1;
}

int main() {
    int a[10] = {2, 3, 5, 6, 9, 12, 32, 54, 74, 111};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Aranacak sayiyi giriniz: ");
    int key;
    scanf("%d", &key);

    int result = ikiliArama(a, 0, n - 1, key);

    if (result == -1)
        printf("Aranan sayi bulunamadi.\n");
    else
        printf("Aranan sayi dizinin %d. indisinde bulundu.\n", result);

    return 0;
}
