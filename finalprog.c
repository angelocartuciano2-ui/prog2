#include <stdio.h>

// STORES
char *softDrinks[5] = {"Coke", "Sprite", "Royal", "Pepsi", "Mountain Dew"};
float softPrices[5] = {25, 25, 25, 25, 25};
int softStock[5] = {10, 10, 10, 10, 10};

char *junkFoods[5] = {"Chips", "Cheetos", "Piattos", "Nova", "Pringles"};
float junkPrices[5] = {15, 20, 18, 22, 35};
int junkStock[5] = {10, 10, 10, 10, 10};

char *waterStore[5] = {"Bottled Water", "Mineral Water", "Distilled Water", "Sparkling Water", "Purified Water"};
float waterPrices[5] = {10, 12, 15, 20, 18};
int waterStock[5] = {10, 10, 10, 10, 10};

char *liquorStore[5] = {"San Miguel Beer", "Red Horse", "Alfonso", "The Bar", "Tanduay Select"};
float liquorPrices[5] = {150, 150, 200, 250, 120};
int liquorStock[5] = {10, 10, 10, 10, 10};

// CART
char *cartItem[200];
int cartQty[200];
float cartPrice[200];
int cartCount = 0;

void addToCart(char *name, int qty, float price) {
    cartItem[cartCount] = name;
    cartQty[cartCount] = qty;
    cartPrice[cartCount] = price;
    cartCount++;
}

void showReceipt() {
    float total = 0;

    printf("\n=========== RECEIPT ===========\n");

    for (int i = 0; i < cartCount; i++) {
        float sub = cartQty[i] * cartPrice[i];
        printf("%s x%d = PHP %.2f\n", cartItem[i], cartQty[i], sub);
        total += sub;
    }

    printf("--------------------------------\n");
    printf("TOTAL: PHP %.2f\n", total);
    printf("================================\n");
}

// EDIT STOCK (SEPARATE FUNCTION)
void editStockMenu() {
    int store, idx, newStock;

    printf("\n=========== EDIT STOCK ===========\n");
    printf("1. Soft Drinks\n");
    printf("2. Junk Foods\n");
    printf("3. Water\n");
    printf("4. Liquor Store\n");
    printf("0. Back\n");
    printf("==================================\n");

    printf("Choose store: ");
    scanf("%d", &store);

    if (store == 0) return;

    printf("Enter product number (1-5): ");
    scanf("%d", &idx);

    printf("Enter new stock: ");
    scanf("%d", &newStock);

    if (idx < 1 || idx > 5) {
        printf("Invalid product!\n");
        return;
    }

    if (store == 1) softStock[idx - 1] = newStock;
    else if (store == 2) junkStock[idx - 1] = newStock;
    else if (store == 3) waterStock[idx - 1] = newStock;
    else if (store == 4) liquorStock[idx - 1] = newStock;
    else {
        printf("Invalid store!\n");
        return;
    }

    printf("Stock updated successfully!\n");
}

// STORE MENU
void displayStores() {
    printf("\n=================================\n");
    printf("        MAIN MENU              \n");
    printf("=================================\n");
    printf("1. Soft Drinks\n");
    printf("2. Junk Foods\n");
    printf("3. Water\n");
    printf("4. Liquor Store\n");
    printf("5. View Receipt\n");
    printf("6. Edit Stock (ADMIN)\n");
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

        if (store == 6) {
            editStockMenu();   // ✅ SEPARATE STOCK MENU
            continue;
        }

        char **items;
        float *prices;
        int *stock;

        if (store == 1) {
            items = softDrinks;
            prices = softPrices;
            stock = softStock;
        } 
        else if (store == 2) {
            items = junkFoods;
            prices = junkPrices;
            stock = junkStock;
        } 
        else if (store == 3) {
            items = waterStore;
            prices = waterPrices;
            stock = waterStock;
        } 
        else if (store == 4) {
            items = liquorStore;
            prices = liquorPrices;
            stock = liquorStock;
        } 
        else {
            printf("Invalid store!\n");
            continue;
        }

        while (1) {
            int choice, qty;
            char confirm;

            printf("\n=================================\n");
            printf(" PRODUCTS (0 = BACK, 7 = CHECKOUT)\n");
            printf("=================================\n");

            for (int i = 0; i < 5; i++) {
                printf("%d. %s - PHP %.2f | STOCK: %d\n",
                       i + 1, items[i], prices[i], stock[i]);
            }

            printf("7. CHECKOUT\n");
            printf("0. BACK\n");
            printf("=================================\n");

            printf("Select: ");
            scanf("%d", &choice);

            if (choice == 0) break;

            if (choice == 7) {
                showReceipt();
                printf("\nCheckout complete!\n");
                break;
            }

            if (choice < 1 || choice > 5) {
                printf("Invalid product!\n");
                continue;
            }

            if (stock[choice - 1] <= 0) {
                printf("Out of stock!\n");
                continue;
            }

            printf("Enter quantity: ");
            scanf("%d", &qty);

            if (qty > stock[choice - 1]) {
                printf("Not enough stock!\n");
                continue;
            }

            printf("Purchase? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                stock[choice - 1] -= qty;
                addToCart(items[choice - 1], qty, prices[choice - 1]);
                printf("Purchased!\n");
            } else {
                printf("Cancelled.\n");
            }
        }
    }

    return 0;
}