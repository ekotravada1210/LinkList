#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    char data;
    struct node *nextKiri, *nextKanan;
} *root = NULL, *current = NULL, *tracking = NULL;

char trackPath(char *path);
void pushData(char a, char *path);
void inOrderTraversal(struct node *node) ;
void printTree(struct node *node, char *prefix, bool isLeft);
void tampilkanTree();
void clearInputBuffer();

void pushData(char a, char *path) {
    current = (struct node*)malloc(sizeof(struct node));
    current->data = a;
    current->nextKiri = NULL;
    current->nextKanan = NULL;

    if (root == NULL) {
        root = current;
    } else {
        char lokasi = trackPath(path);
        if (lokasi == 'L') {
            tracking->nextKiri = current;
        } else if (lokasi == 'R') {
            tracking->nextKanan = current;
        } else {
            printf("Path tidak valid atau node sudah ada\n");
            free(current);
        }
    }
}

char trackPath(char *lintasan) {
    tracking = root;
    while (*lintasan != '\0') {
        if (*lintasan == 'L') {
            if (tracking->nextKiri != NULL) {
                tracking = tracking->nextKiri;
            } else {
                return 'L';
            }
        } else if (*lintasan == 'R') {
            if (tracking->nextKanan != NULL) {
                tracking = tracking->nextKanan;
            } else {
                return 'R';
            }
        } else {
            return *lintasan; // karakter invalid
        }
        lintasan++;
    }
    return '\0'; // path lengkap
}

void inOrderTraversal(struct node *node) 
{
    if (node == NULL) return;
    
    inOrderTraversal(node->nextKiri);  // Kunjungi subtree kiri
    printf("%c ", node->data);         // Cetak node saat ini
    inOrderTraversal(node->nextKanan); // Kunjungi subtree kanan
}

// Fungsi untuk menampilkan tree
void printTree(struct node *node, char *prefix, bool isLeft) {
    if (node == NULL) return;
    
    printf("%s", prefix);
    printf(isLeft ? "R-" : "L-");
    printf("%c\n", node->data);
    
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "|   " : "    ");
    
    // Tampilkan anak kanan dulu (bisa disesuaikan)
    printTree(node->nextKanan, newPrefix, true);
    printTree(node->nextKiri, newPrefix, false);
}


void tampilkanTree() {
    printf("\nStruktur Tree:\n");
    if (root != NULL) {
        printf("%c\n", root->data);
        char prefix[256] = "";
        printTree(root->nextKanan, prefix, true);
        printTree(root->nextKiri, prefix, false);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main() {
    char karakter;
    char lokasi[20];
    
    while (1)
    {
        printf("Entry karakter (exit=x/X) : ");
        scanf(" %c",&karakter);
        clearInputBuffer();

        if(karakter == 'x' || karakter == 'X') {
            printf("\nProgram selesai\n");
            break;
        }
        printf("Lokasi (max=19) : ");
        scanf(" %19s",&lokasi);
        clearInputBuffer();
        pushData(karakter,lokasi);
        printf("Traversal In-Order: ");
        inOrderTraversal(root);
        printf("\n");
        tampilkanTree();
    }
}