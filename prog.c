#include <stdio.h>

// STORES
char *softDrinks[5] = {"Coke", "Sprite", "Royal", "Pepsi", "Mountain Dew"};
float softPrices[5] = {25, 25, 25, 25, 25};

char *junkFoods[5] = {"Chips", "Cheetos", "Piattos", "Nova", "Pringles"};
float junkPrices[5] = {15, 20, 18, 22, 35};

char *waterStore[5] = {"Bottled Water", "Mineral Water", "Distilled Water", "Sparkling Water", "Purified Water"};
float waterPrices[5] = {10, 12, 15, 20, 18};

char *liquorStore[5] = {"San Miguel Beer", "Red Horse", "Alfonso", "The Bar", "Tanduay Select"};
float liquorPrices[5] = {150, 150, 200, 250, 120};

// CART
char *cartItem[200];
int cartQty[200];
float cartPrice[200];
int cartCount = 0;

// ADD ITEM
void addToCart(char *name, int qty, float price) {
    cartItem[cartCount] = name;
    cartQty[cartCount] = qty;
    cartPrice[cartCount] = price;
    cartCount++;
}

// RECEIPT
void showReceipt() {
    float total = 0;

    printf("\n=========== RECEIPT ===========\n");

    if (cartCount == 0) {
        printf("No items purchased.\n");
        return;
    }

    for (int i = 0; i < cartCount; i++) {
        float sub = cartQty[i] * cartPrice[i];
        printf("%s x%d = PHP %.2f\n", cartItem[i], cartQty[i], sub);
        total += sub;
    }

    printf("--------------------------------\n");
    printf("TOTAL: PHP %.2f\n", total);
    printf("================================\n");
}

// STORE MENU
void displayStores() {
    printf("\n=================================\n");
    printf("        SELECT STORE            \n");
    printf("=================================\n");
    printf("1. Soft Drinks\n");
    printf("2. Junk Foods\n");
    printf("3. Water\n");
    printf("4. Liquor Store\n");
    printf("5. View Receipt\n");
    printf("0. Exit\n");
    printf("=================================\n");
}

int main() {
    int store;

    while (1) {
        displayStores();
        printf("Enter choice: ");
        scanf("%d", &store);

        if (store == 0) {
            showReceipt();
            break;
        }

        if (store == 5) {
            showReceipt();
            continue;
        }

        char **items;
        float *prices;

        if (store == 1) {
            items = softDrinks;
            prices = softPrices;
        } 
        else if (store == 2) {
            items = junkFoods;
            prices = junkPrices;
        } 
        else if (store == 3) {
            items = waterStore;
            prices = waterPrices;
        } 
        else if (store == 4) {
            items = liquorStore;
            prices = liquorPrices;
        } 
        else {
            printf("Invalid store!\n");
            continue;
        }

        while (1) {
            int choice, qty;
            char confirm;

            printf("\n=================================\n");
            printf(" PRODUCTS (0 = BACK, 6 = CHECKOUT)\n");
            printf("=================================\n");

            for (int i = 0; i < 5; i++) {
                printf("%d. %s - PHP %.2f\n", i + 1, items[i], prices[i]);
            }

            printf("6. CHECKOUT\n");
            printf("0. BACK\n");
            printf("=================================\n");

            printf("Select: ");
            scanf("%d", &choice);

            if (choice == 0) break;

            // ✅ CHECKOUT INSIDE PRODUCT MENU
            if (choice == 6) {
                showReceipt();
                printf("\nCheckout complete!\n");
                break;
            }

            if (choice < 1 || choice > 5) {
                printf("Invalid product!\n");
                continue;
            }

            printf("Enter quantity: ");
            scanf("%d", &qty);

            printf("Purchase this item? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                addToCart(items[choice - 1], qty, prices[choice - 1]);
                printf("Added to cart!\n");
            } else {
                printf("Cancelled.\n");
            }
        }
    }

    return 0;
}