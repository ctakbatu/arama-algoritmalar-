
//ikili agac araması

#include <stdio.h>
#include <stdlib.h>

// dügüm yapısını tanımlayan struct
typedef struct Node {
    int data; // dügümün verisi
    struct Node* left; // dügümün sol kolu
    struct Node* right; // dügümün sag kolu
} Node;

// yeni bir dügüm olusturan fonksiyon
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // bellekten yer ayir
    if (newNode == NULL) { // yer ayrılmazsa hata ver
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    newNode->data = data; // dügümün verisini ata
    newNode->left = NULL; // dügümün sol kolunu bos yap
    newNode->right = NULL; // dügümün sag kolunu bos yap

    return newNode; // dügümü döndür
}

// ikili arama agacina veri ekleyen fonksiyon
Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data); // kök boşsa yeni dügüm olusur

    if (data < root->data) // veri kökten küçükse
        root->left = insert(root->left, data); // sol kola ekle

    else if (data > root->data) // veri kökten büyükse
        root->right = insert(root->right, data); // sagkola ekle

   return root; // kökü döndür
}

// ikili arama agacından veri silen fonksiyon
Node* delete(Node* root, int data) {
    if (root == NULL) return NULL; // kök bossa NULL döndür

    if (data < root->data) // veri kökten küçükse
        root->left = delete(root->left, data); // sol koldan sil

    else if (data > root->data) // veri kökten büyükse
        root->right = delete(root->right, data); // sag koldan sil

    else { // veri kökte ise
        if (root->left == NULL) { // sol kol bossa
            Node* temp = root->right; // sag kolu geçici degiskene ata
            free(root); // kökü sil
            return temp; // sað kolu döndür
        }
        else if (root->right == NULL) { // sag kol boşsa
            Node* temp = root->left; // sol kolu geçici degiskene ata
            free(root); // kökü sil
            return temp; // sol kolu döndür
        }
        else { // her iki kol da doluysa
            Node* temp = root->right; // sag kolu geçici degiskene ata
            while (temp->left != NULL) // sol kolu bos olan ilk dügümü bul
                temp = temp->left;
            root->data = temp->data; // kökün verisini bu dügümün verisiyle degistir
            root->right = delete(root->right, temp->data); // sag koldan bu dügümü sil
        }
    }
    return root; // kökü döndür
}

// ikili arama agacında veri arayan fonksiyon
Node* search(Node* root, int data) {
    if (root == NULL) return NULL; // kök bossa NULL döndür

    if (data == root->data) // veri kökte ise
        return root; // kökü döndür

    else if (data < root->data) // veri kökten küçükse
        return search(root->left, data); // sol kolda ara

    else // veri kökten büyükse
        return search(root->right, data); // sag kolda ara
}

// ikili arama agacını inorder şkilde yazdıran fonksiyon
void inorder(Node* root) {
   if (root != NULL) { // kök boş deðilse
      inorder(root->left); // sol kolu yazdır
      printf("%d ", root->data); // kökü yazdır
      inorder(root->right); // sag kolu yazdır
   }
}

int main() {
   Node *root = createNode(5); // kök düðümü oluþtur

   insert(root, 3); // 3 verisini ekle
   insert(root, 8); // 8 verisini ekle
   insert(root, 2); // 2 verisini ekle
   insert(root, 4); // 4 verisini ekle
   insert(root, 6); // 6 verisini ekle
   insert(root, 9); // 9 verisini ekle

   inorder(root); // agaca yazdir
   printf("\n");

   delete(root, 5); // 5 verisini sil
   inorder(root); // agaca yazdir
   printf("\n");

   Node* result = search(root, 6); // 6 verisini ara
   if (result != NULL) // sonuç NULL deðilse
      printf("Veri bulundu: %d\n", result->data); // veriyi yazdır
   else // sonuç NULL ise
      printf("Veri bulunamadi\n"); // hata mesajı yazdır

   return 0;
}
