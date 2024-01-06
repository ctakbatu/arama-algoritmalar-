//İNTERPOLASYON

#include <stdio.h>

int interpolation_arama(int arr[], int n, int x) {
    int low = 0; // dizinin ilk indeksi
    int high = n - 1; // dizinin son indeksi

    while (low <= high && x >= arr[low] && x <= arr[high]) {
        // aranacak degerin olası konumunu tahmin et
        int pos = low + ((x - arr[low]) * (high - low)) / (arr[high] - arr[low]);

        if (arr[pos] == x)
            return pos; // değer bulunursa indeksini döndür
        else if (arr[pos] < x)
            low = pos + 1; // değer tahminden büyükse alt yarıda ara
        else
            high = pos - 1; // değer tahminden küçükse üst yarıda ara
    }

    return -1; // değer bulunamazsa -1 döndür
}

int main() {
    int arr[] = {1, 3, 4, 5, 6, 8, 9, 11, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Aranacak sayiyi giriniz: ");
    int x;
    scanf("%d", &x);

    int result = interpolation_arama(arr, n, x);

    if (result == -1)
        printf("Deger bulunamadi\n");
    else
        printf("Deger %d. indekste bulundu\n", result);

    return 0;
}
