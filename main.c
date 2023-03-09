#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TVA 1.24
#define MAX_PRODUCTS 100
#define MAX_TITLE_LENGTH 50

typedef struct {
    char title[MAX_TITLE_LENGTH];
    float price;
    int quantity;
} Product;

void print_product(Product* product) {
    printf("Titre : %s\nPrix : %.2f\nQuantite : %d\n", product->title, product->price, product->quantity);
}

void print_products(Product* products[], int productCount) {
    printf("Liste des produits :\n");
    for (int i = 0; i < productCount; i++) {
        printf("Produit %d :\n", i+1);
        print_product(products[i]);
        printf("\n");
    }
}

float calculate_total(Product* product) { return product->price * product->quantity; }

float calculate_total_ttc(Product* product) { return calculate_total(product) * TVA; }

void add_product(Product* product, Product* products[], int* product_count, float* total_ttc) {
    if (*product_count < MAX_PRODUCTS) products[(*product_count)++] = product, *total_ttc += calculate_total_ttc(product);
}

bool is_number(char* str) { for (int i = 0; str[i] != '\0'; i++) if (!isdigit(str[i]) && str[i] != '.') return false; return true; }

bool is_valid_price(char* str) { return is_number(str) && atof(str) > 0; }

bool is_valid_quantity(char* str) { return is_number(str) && atoi(str) > 0; }

void clear_input_buffer() { while (getchar() != '\n'); }

bool get_yes_no_input(char* message) { char input; do printf("%s (O/N) : ", message), scanf(" %c", &input), clear_input_buffer(); while (toupper(input) != 'O' && toupper(input) != 'N'); return toupper(input) == 'O'; }

int main() {
    Product* products[MAX_PRODUCTS];
    int productCount = 0;
    float totalTTC = 0;

    do {
        char title[MAX_TITLE_LENGTH], priceStr[20], quantityStr[10];

        printf("Entrez le titre : ");
        fgets(title, MAX_TITLE_LENGTH, stdin);
        title[strcspn(title, "\n")] = '\0';

        do printf("Entrez le prix : "), fgets(priceStr, 20, stdin), priceStr[strcspn(priceStr, "\n")] = '\0'; while (!is_valid_price(priceStr));

        do printf("Entrez la quantite : "), fgets(quantityStr, 10, stdin), quantityStr[strcspn(quantityStr, "\n")] = '\0'; while (!is_valid_quantity(quantityStr));

        Product* product = malloc(sizeof(Product));
        strncpy(product->title, title, MAX_TITLE_LENGTH);
        product->price = atof(priceStr);
        product->quantity = atoi(quantityStr);

        add_product(product, products, &productCount, &totalTTC);
    } while (get_yes_no_input("Voulez-vous ajouter un autre produit ?"));

    print_products(products, productCount);
    printf("Total TTC : %.2f\n", totalTTC);

    for (int i = 0; i < productCount; i++) free(products[i]);

    system("pause");
    return 0;
}
