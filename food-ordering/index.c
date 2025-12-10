#include <stdio.h>
#include <string.h>

struct Food {
    char name[50];
    float price;
};
typedef struct Food Food;

void displayMenu(Food menu[], int size) {
    printf("\n================== MENU ==================\n");
    for (int i = 0; i < size; i++) {
        printf("%2d. %-20s  %.2f\n", i + 1, menu[i].name, menu[i].price);
    }
    printf("==========================================\n");
}

float calculateTotal(Food menu[], int order[], int size) {
    float total = 0;
    for (int i = 0; i < size; i++) {
        total += menu[i].price * order[i];
    }
    return total;
}

void printBill(Food menu[], int order[], int size, float total, float gst, float discount) {
    printf("\n================= BILL ====================\n");
    printf("Item                Qty     Price     Subtotal\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        if (order[i] > 0) {
            printf("%-20s %-6d %-8.2f %.2f\n",
                   menu[i].name,
                   order[i],
                   menu[i].price,
                   menu[i].price * order[i]);
        }
    }

    printf("----------------------------------------------\n");
    printf("Subtotal:                         %.2f\n", total);
    if (discount > 0)
        printf("Discount (10%%):                  -%.2f\n", discount);

    printf("GST (5%%):                         %.2f\n", gst);
    printf("----------------------------------------------\n");
    printf("Grand Total:                      %.2f\n", total - discount + gst);
    printf("==============================================\n");
}

void placeOrder(Food menu[], int size, int order[]) {
    int choice, quantity;
    char confirm;
    float total, gst, discount = 0;

    do {
        displayMenu(menu, size);

        printf("Enter item number: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > size) {
            printf("Invalid choice! Try again.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if (quantity <= 0) {
            printf("Quantity must be greater than 0!\n");
            continue;
        }

        order[choice - 1] += quantity;

        printf("Add more items? (y/n): ");
        scanf(" %c", &confirm);

    } while (confirm == 'y' || confirm == 'Y');

    total = calculateTotal(menu, order, size);
    gst = total * 0.05;

    printf("\nApply 10%% discount? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        discount = total * 0.10;
    }

    printBill(menu, order, size, total, gst, discount);
}

int main() {
    Food menu[10];
    int order[10] = {0};

    strcpy(menu[0].name, "Pizza");         menu[0].price = 9.99;
    strcpy(menu[1].name, "Burger");        menu[1].price = 5.99;
    strcpy(menu[2].name, "Momos");         menu[2].price = 3.99;
    strcpy(menu[3].name, "French Fries");  menu[3].price = 2.99;
    strcpy(menu[4].name, "Ice Cream");     menu[4].price = 4.99;
    strcpy(menu[5].name, "Cold Coffee");   menu[5].price = 50.55;
    strcpy(menu[6].name, "Samosa");        menu[6].price = 5.00;
    strcpy(menu[7].name, "Kullhad Chai");  menu[7].price = 20.50;
    strcpy(menu[8].name, "Paneer Roll");   menu[8].price = 30.55;
    strcpy(menu[9].name, "Pani Puri");     menu[9].price = 20.00;

    placeOrder(menu, 10, order);

    return 0;
}
