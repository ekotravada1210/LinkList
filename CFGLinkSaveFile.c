#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH_LENGTH 100

struct node {
    char data;
    struct node *firstChild;
    struct node *nextSibling;
} *root = NULL;

// Prototipe fungsi
void pushData(char a, char *path);
struct node* trackPath(char *path, bool createPath);
void printTree(struct node *node, char *prefix, bool isLast);
void tampilkanTree();
void clearInputBuffer();
void saveTreeToFile(const char *filename);
void loadTreeFromFile(const char *filename);
void deleteTree(struct node *node);
int validatePath(const char *path);

// Fungsi validasi path
int validatePath(const char *path) {
    for (int i = 0; path[i] != '\0'; i++) {
        if (!isdigit(path[i])) {
            printf("Error: Path harus berupa angka (0-9)\n");
            return 0;
        }
    }
    return 1;
}

void deleteTree(struct node *current) {
    if (current == NULL) return;
    deleteTree(current->firstChild);
    deleteTree(current->nextSibling);
    free(current);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi untuk menyimpan tree ke file
static void saveNode(struct node *current, char *currentPath, FILE *file) {
    if (!current) return;
    
    // Simpan node saat ini
    fprintf(file, "[%s]%c\n", currentPath, current->data);
    
    // Simpan anak-anak
    struct node *child = current->firstChild;
    int idx = 0;
    while (child) {
        char childPath[MAX_PATH_LENGTH];
        snprintf(childPath, sizeof(childPath), "%s%d", currentPath, idx);
        saveNode(child, childPath, file);
        child = child->nextSibling;
        idx++;
    }
}

void saveTreeToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    saveNode(root, "", file);
    fclose(file);
    printf("Tree berhasil disimpan ke %s\n", filename);
}

void loadTreeFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File %s tidak ditemukan\n", filename);
        return;
    }

    // Hapus tree existing
    deleteTree(root);
    root = NULL;

    char line[256];
    bool rootLoaded = false;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Hapus newline
        char path[MAX_PATH_LENGTH] = {0};
        char data = '\0';
        
        line[strcspn(line, "\n")] = '\0';
        printf("%s\n", line); 
     
        char *end_bracket = strchr(line, ']');
        if (end_bracket != NULL && end_bracket[1] != '\0') {
            // Ambil path (bagian di dalam [])
            strncpy(path, line + 1, end_bracket - line - 1);
            path[end_bracket - line - 1] = '\0';
            // Ambil data (karakter setelah ])
            data = end_bracket[1];

            if (strlen(path) == 0) {
                printf("Data: %c\n", data);
            } else {
                printf("Path: %s, Data: %c\n", path, data);
            }
        } else {
            printf("Format tidak valid: %s\n", line);
        }
    
        // Validasi panjang path
        if (strlen(path) >= MAX_PATH_LENGTH) {
            printf("Path terlalu panjang: %s\n", path);
            continue;
        }
        // Handle root node
        if (strlen(path) == 0) {
            if (!rootLoaded) {
                pushData(data, "");
                rootLoaded = true;
            }
        } else {
            if (!rootLoaded) {
                printf("ERROR: Root harus didefinisikan pertama!\n");
                break;
            }
            pushData(data, path);
        }
    }

    fclose(file);
    printf("Tree berhasil dimuat dari %s\n", filename);
}

struct node* trackPath(char *path, bool createPath) {
    if (!root || strlen(path) == 0) return root;

    struct node *currentNode = root;
    
    for (int i = 0; path[i] != '\0'; i++) {
        int idx = path[i] - '0';
        struct node **childPtr = &(currentNode->firstChild);
        
        // Navigasi ke child yang sesuai
        for (int j = 0; j < idx; j++) {
            if (*childPtr == NULL && createPath) {
                *childPtr = (struct node*)calloc(1, sizeof(struct node));
                (*childPtr)->data = '-';
            }
            if (*childPtr == NULL) return NULL;
            childPtr = &((*childPtr)->nextSibling);
        }
        
        if (*childPtr == NULL && createPath) {
            *childPtr = (struct node*)calloc(1, sizeof(struct node));
            (*childPtr)->data = '-';
        }
        
        if (*childPtr == NULL) return NULL;
        currentNode = *childPtr;
    }
    return currentNode;
}

void pushData(char a, char *path) {
    if (!validatePath(path)) return;

    if (strlen(path) == 0) {
        if (root == NULL) {
            root = (struct node*)calloc(1, sizeof(struct node));
            root->data = a;
            printf("Root node '%c' berhasil dibuat\n", a);
        } else {
            printf("Root sudah ada\n");
        }
        return;
    }

    if (root == NULL) {
        printf("ERROR: Root belum ada! Buat root dulu!\n");
        return;
    }

    struct node *parent = trackPath(path, true);
    if (parent == NULL) {
        printf("Gagal membuat path\n");
        return;
    }
    
    if (parent->data == '-') {
        parent->data = a;
        printf("Node '%c' berhasil ditambahkan di path: %s\n", a, path);
    } else {
        printf("Node pada path %s sudah ada (data: %c)\n", path, parent->data);
    }
}

void printTree(struct node *node, char *prefix, bool isLast) {
    if (node == NULL) return;
    
    printf("%s", prefix);
    printf(isLast ? "-- " : "|-- ");
    printf("%c\n", node->data);
    
    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "|   ");
    
    struct node *child = node->firstChild;
    while (child != NULL) {
        struct node *next = child->nextSibling;
        printTree(child, newPrefix, next == NULL);
        child = next;
    }
}

void tampilkanTree() {
    printf("\nStruktur Tree:\n");
    if (root != NULL) {
        printTree(root, "", true);
    }
    printf("\n");
}

int main() {
    int choice;
    char filename[50];
    char path[MAX_PATH_LENGTH];
    char data;

    printf("===== Tree Manager untuk CFG =====\n");
    
    while (1) {
        printf("\nMenu Utama:\n");
        printf("1. Tambah Node\n");
        printf("2. Tampilkan Tree\n");
        printf("3. Simpan ke File\n");
        printf("4. Muat dari File\n");
        printf("5. Exit\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                printf("Masukkan karakter: ");
                scanf("%c", &data);
                clearInputBuffer();
                printf("Masukkan path: ");
                fgets(path, MAX_PATH_LENGTH, stdin);
                path[strcspn(path, "\n")] = '\0';
                pushData(data, path);
                break;
            
            case 2:
                tampilkanTree();
                break;
            
            case 3:
                printf("Nama file untuk disimpan: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveTreeToFile(filename);
                break;
            
            case 4:
                printf("Nama file untuk dimuat: ");
                fgets(filename, 50, stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadTreeFromFile(filename);
                break;
            
            case 5:
                deleteTree(root);
                printf("Program selesai\n");
                exit(0);
            
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}