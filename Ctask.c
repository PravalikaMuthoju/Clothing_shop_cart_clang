#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_CART_ITEMS 20

struct Product {
    int id;
    char name[30];
    float price;
};

struct CartItem {
    struct Product product;
    int quantity;
};

// Men products
struct Product menProducts[MAX_PRODUCTS] = {
    {101, "Men T-Shirt", 0},
    {102, "Men Jeans", 0},
    {103, "Men Jacket", 0},
    {104, "Men Shoes", 0},
    {105, "Men Hat", 0}
};

// Women products
struct Product womenProducts[MAX_PRODUCTS] = {
    {201, "Women Dress", 0},
    {202, "Women Skirt", 0},
    {203, "Women Blouse", 0},
    {204, "Women Heels", 0},
    {205, "Women Bag", 0}
};

// Kids Boys products
struct Product boysProducts[MAX_PRODUCTS] = {
    {301, "Boys T-Shirt", 0},
    {302, "Boys Shorts", 0},
    {303, "Boys Jacket", 0},
    {304, "Boys Shoes", 0},
    {305, "Boys Cap", 0}
};

// Kids Girls products
struct Product girlsProducts[MAX_PRODUCTS] = {
    {401, "Girls Dress", 0},
    {402, "Girls Skirt", 0},
    {403, "Girls Blouse", 0},
    {404, "Girls Shoes", 0},
    {405, "Girls Hat", 0}
};

void inputPrices(struct Product products[], int size, char categoryName[]) {
    printf("Enter prices for %s products:\n", categoryName);
    for (int i = 0; i < size; i++) {
        printf("Price of %s: $", products[i].name);
        scanf("%f", &products[i].price);

        if (products[i].price < 0) {
            printf("Price can't be negative. Please enter again.\n");
            i--; // repeat current product input
        }
    }
}

void showCategoryProducts(struct Product products[], int size) {
    printf("ID\tProduct Name\t\tPrice\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%-20s $%.2f\n", products[i].id, products[i].name, products[i].price);
    }
}

int findProductIndex(struct Product products[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (products[i].id == id)
            return i;
    }
    return -1;
}

void addToCart(struct CartItem cart[], int* cartCount, struct Product p, int qty) {
    for (int i = 0; i < *cartCount; i++) {
        if (cart[i].product.id == p.id) {
            cart[i].quantity += qty;
            return;
        }
    }
    if (*cartCount < MAX_CART_ITEMS) {
        cart[*cartCount].product = p;
        cart[*cartCount].quantity = qty;
        (*cartCount)++;
    } else {
        printf("Cart is full! Cannot add more items.\n");
    }
}

void showCart(struct CartItem cart[], int cartCount) {
    if (cartCount == 0) {
        printf("Your cart is empty.\n");
        return;
    }
    printf("\nYour Shopping Cart:\n");
    printf("ID\tProduct\t\tQuantity\tPrice\tTotal\n");
    float totalAmount = 0;
    for (int i = 0; i < cartCount; i++) {
        float totalPrice = cart[i].quantity * cart[i].product.price;
        printf("%d\t%-15s %d\t\t$%.2f\t$%.2f\n",
               cart[i].product.id,
               cart[i].product.name,
               cart[i].quantity,
               cart[i].product.price,
               totalPrice);
        totalAmount += totalPrice;
    }
    printf("Total amount: $%.2f\n\n", totalAmount);
}

int main() {
    struct CartItem cart[MAX_CART_ITEMS];
    int cartCount = 0;
    int categoryChoice, productId, qty;

    // Manager inputs prices first
    printf("=== Manager: Enter product prices ===\n");
    inputPrices(menProducts, MAX_PRODUCTS, "Men");
    inputPrices(womenProducts, MAX_PRODUCTS, "Women");
    inputPrices(boysProducts, MAX_PRODUCTS, "Kids Boys");
    inputPrices(girlsProducts, MAX_PRODUCTS, "Kids Girls");

    while (1) {
        printf("\nWelcome to Clothes Shop!\n");
        printf("Choose a category:\n");
        printf("1. Men\n2. Women\n3. Kids Boys\n4. Kids Girls\n5. View Cart\n6. Checkout\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &categoryChoice);

        struct Product selectedProduct;
        int productIndex = -1;

        switch (categoryChoice) {
            case 1:
                printf("\nMen's Clothing:\n");
                showCategoryProducts(menProducts, MAX_PRODUCTS);
                printf("Enter Product ID to add to cart (0 to cancel): ");
                scanf("%d", &productId);
                if (productId == 0) break;
                productIndex = findProductIndex(menProducts, MAX_PRODUCTS, productId);
                if (productIndex == -1) {
                    printf("Invalid Product ID.\n");
                    break;
                }
                selectedProduct = menProducts[productIndex];
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0) {
                    printf("Quantity must be positive.\n");
                    break;
                }
                addToCart(cart, &cartCount, selectedProduct, qty);
                printf("%d %s(s) added to cart. Total amount for these items: $%.2f\n",
                       qty, selectedProduct.name, qty * selectedProduct.price);
                break;

            case 2:
                printf("\nWomen's Clothing:\n");
                showCategoryProducts(womenProducts, MAX_PRODUCTS);
                printf("Enter Product ID to add to cart (0 to cancel): ");
                scanf("%d", &productId);
                if (productId == 0) break;
                productIndex = findProductIndex(womenProducts, MAX_PRODUCTS, productId);
                if (productIndex == -1) {
                    printf("Invalid Product ID.\n");
                    break;
                }
                selectedProduct = womenProducts[productIndex];
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0) {
                    printf("Quantity must be positive.\n");
                    break;
                }
                addToCart(cart, &cartCount, selectedProduct, qty);
                printf("%d %s(s) added to cart. Total amount for these items: $%.2f\n",
                       qty, selectedProduct.name, qty * selectedProduct.price);
                break;

            case 3:
                printf("\nKids Boys Clothing:\n");
                showCategoryProducts(boysProducts, MAX_PRODUCTS);
                printf("Enter Product ID to add to cart (0 to cancel): ");
                scanf("%d", &productId);
                if (productId == 0) break;
                productIndex = findProductIndex(boysProducts, MAX_PRODUCTS, productId);
                if (productIndex == -1) {
                    printf("Invalid Product ID.\n");
                    break;
                }
                selectedProduct = boysProducts[productIndex];
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0) {
                    printf("Quantity must be positive.\n");
                    break;
                }
                addToCart(cart, &cartCount, selectedProduct, qty);
                printf("%d %s(s) added to cart. Total amount for these items: $%.2f\n",
                       qty, selectedProduct.name, qty * selectedProduct.price);
                break;

            case 4:
                printf("\nKids Girls Clothing:\n");
                showCategoryProducts(girlsProducts, MAX_PRODUCTS);
                printf("Enter Product ID to add to cart (0 to cancel): ");
                scanf("%d", &productId);
                if (productId == 0) break;
                productIndex = findProductIndex(girlsProducts, MAX_PRODUCTS, productId);
                if (productIndex == -1) {
                    printf("Invalid Product ID.\n");
                    break;
                }
                selectedProduct = girlsProducts[productIndex];
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0) {
                    printf("Quantity must be positive.\n");
                    break;
                }
                addToCart(cart, &cartCount, selectedProduct, qty);
                printf("%d %s(s) added to cart. Total amount for these items: $%.2f\n",
                       qty, selectedProduct.name, qty * selectedProduct.price);
                break;

            case 5:
                showCart(cart, cartCount);
                break;

            case 6:
                if (cartCount == 0) {
                    printf("Your cart is empty. Add some products first.\n");
                } else {
                    showCart(cart, cartCount);
                    printf("Proceed to checkout? (1 = Yes, 0 = No): ");
                    int proceed;
                    scanf("%d", &proceed);
                    if (proceed == 1) {
                        printf("Thank you for shopping! Your order has been placed.\n");
                        printf("Thanks for shopping, visit again!\n");
                        cartCount = 0; // Empty the cart
                    } else {
                        printf("Checkout canceled.\n");
                    }
                }
                break;

            case 7:
                printf("Thank you for visiting! Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
