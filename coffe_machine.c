#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Defining the constants for the coffee machine
//Espresso
#define e_cb 8 
#define e_w 30
#define e_m  0
#define e_cs 0
float e_price = 3.5;

//Mocha
#define m_cb 8
#define m_w 39
#define m_m  160
#define m_cs 30
float m_price = 5.5;

//Cappuccino
#define c_cb 8
#define c_w 30
#define c_m  70
#define c_cs 0
float c_price = 4.5;

#define AD_PW "1029384756"
float t_amt = 0;

//Threshold Values
float threshhold_cb = 200;
float threshhold_w = 200;
float threshhold_m = 200; 
float threshhold_cs = 200;

//Functions used
int Order();
int Payment(float amount);
int AdminMode();
void displayIngredientsAndSales();
void replenishIngredients();
void changeCoffeePrice();

//Main Function
int main(){
    int choice;
    while (1){
        printf("\n\n*MENU*\n");
        printf("1. Order Coffee\n");
        printf("2. Admin Mode\n");
        printf("3. Exit\n");
        printf("Enter 1, 2 or 3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Order();
                break;
            case 2:
                AdminMode();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid input\n");
        }
    }
}

//Order Function
int Order(){
    int coffee_choice;
    printf("Choose your coffee\n");
    printf("1. Espresso\n");
    printf("2. Cappuccino\n");
    printf("3. Mocha\n");
    printf("Enter your choice: ");
    scanf("%d",&coffee_choice);

    switch (coffee_choice) {
        case 1:
            printf("Choice of coffee: Espresso\n");
            printf("The price is %.1f dhs\n",e_price);
            if (e_cb <= threshhold_cb && e_w <= threshhold_w){
                printf("Your coffee is ready!\n");
                Payment(e_price);

                //Changing Available Values
                threshhold_cb -= e_cb;
                threshhold_w -= e_w;
            }
            else{
                printf("Unable to process your order due to insufficient ingredients.\n");
            }
            break;
        case 2:
            printf("Choice of coffee: Cappuccino\n");
            printf("The price is %.1f dhs\n",c_price);
            if (c_cb <= threshhold_cb && c_w <= threshhold_w && c_m <= threshhold_m){
                printf("Your coffee is ready!\n");
                Payment(c_price);

                //Changing Available Values
                threshhold_cb -= c_cb;
                threshhold_m -= c_m;
                threshhold_w -= c_w;
            }
            else{
                printf("Unable to process your order due to insufficient ingredients.\n");
            }
            break;
        case 3:
            printf("Choice of coffee: Mocha\n");
            printf("The price is %.1f dhs\n",m_price);
            if (m_cb <= threshhold_cb && m_w <= threshhold_w && m_m <= threshhold_m && m_cs <= threshhold_cs){
                printf("Your coffee is ready!\n");
                Payment(m_price);

                //Changing Available Values
                threshhold_cb -= m_cb;
                threshhold_m -= m_m;
                threshhold_cs -= m_cs;
                threshhold_w -= m_w;
            }
            else{
                printf("Unable to process your order due to insufficient ingredients.\n");
            }
            break;
        default:
            printf("Invalid Input\n");
    }
    return 0;
}

//Payment Function
int Payment(float amount){
    float pay = 0;
    int amt;  // Changing to int for coin choices
    while (pay < amount){
        printf("Enter 1 to insert 1 dhs and 2 to insert 0.5 dhs: ");
        scanf("%d", &amt);  // Change to %d for integer input
        if (amt == 1){
            pay += 1;
        }
        else if (amt == 2){
            pay += 0.5;
        }
        else{
            printf("Invalid coin\n");
        }
        printf("Current amount inserted: %.1f dhs\n", pay);
    }
    if (pay > amount){
        float change = pay - amount;
        printf("Your change is %.1f dhs\n", change);
    }
    t_amt += amount;
    printf("Thank you!!\n\n");
    return 0;
}

//Admin Mode Function
int AdminMode() {
    int admin_choice;
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, AD_PW) != 0) {
        printf("Incorrect password. Exiting Admin Mode.\n");
        return 0;
    }
    while (1) {
        printf("\n\n*ADMIN MENU*\n");
        printf("1: Display the quantity of each ingredient in the machine and the total sale amount\n");
        printf("2: Replenish ingredients in the machine\n");
        printf("3: Change coffee price\n");
        printf("0: Exit Admin Mode\n");
        printf("Enter your choice: ");
        scanf("%d", &admin_choice);

        switch (admin_choice) {
            case 1:
                displayIngredientsAndSales();
                break;
            case 2:
                replenishIngredients();
                break;
            case 3:
                changeCoffeePrice();
                break;
            case 0:
                printf("Exiting\n");
                return 0;
            default:
                printf("Invalid input\n");
        }
    }
}

void displayIngredientsAndSales() {
    printf("Current ingredient levels:\n");
    printf("Coffee beans: %.1f\n", threshhold_cb);
    printf("Water: %.1f\n", threshhold_w);
    printf("Milk: %.1f\n", threshhold_m);
    printf("Chocolate syrup: %.1f\n", threshhold_cs);
    printf("Total sales amount: %.1f dhs\n", t_amt);

    char reset_choice;
    printf("Would you like to reset the total sales amount to zero? (y/n): ");
    scanf(" %c", &reset_choice);
    if (reset_choice == 'y' || reset_choice == 'Y') {
        t_amt = 0;
        printf("Total sales amount has been reset to zero. Please collect the money from the machine.\n");
    }
}

void replenishIngredients() {
    int k= 1;
    srand(time(0));
    int replenish_choice;
    while (k==1)
    {   
        printf("Choose the ingredient to replenish:\n");
        printf("1. Coffee beans\n");
        printf("2. Water\n");
        printf("3. Milk\n");
        printf("4. Chocolate syrup\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &replenish_choice);

        switch (replenish_choice) {
        case 1:
            threshhold_cb = (rand() % 101) + 100; // Random value between 100 and 200
            printf("Coffee beans have been replenished.\n");
            break;
        case 2:
            threshhold_w = (rand() % 101) + 100; 
            printf("Water has been replenished.\n");
            break;
        case 3:
            threshhold_m = (rand() % 101) + 100; 
            printf("Milk has been replenished.\n");
            break;
        case 4:
            threshhold_cs = (rand() % 101) + 100; 
            printf("Chocolate syrup has been replenished.\n");
            break;
        case 5:
            printf("Exiting\n");
            k=0;
            break;
        default:
            printf("Invalid input\n");
        }
    }
    
}

void changeCoffeePrice() {
    int coffee_choice;
    float new_price;
    printf("Choose the coffee type to change the price:\n");
    printf("1. Espresso\n");
    printf("2. Cappuccino\n");
    printf("3. Mocha\n");
    printf("Enter your choice: ");
    scanf("%d", &coffee_choice);

    switch (coffee_choice) {
        case 1:
            printf("Current price of Espresso: %.1f dhs\n", e_price);
            printf("Enter new price: ");
            scanf("%f", &new_price);
            e_price = new_price;
            printf("New price of Espresso: %.1f dhs\n", e_price);
            break;
        case 2:
            printf("Current price of Cappuccino: %.1f dhs\n", c_price);
            printf("Enter new price: ");
            scanf("%f", &new_price);
            c_price = new_price;
            printf("New price of Cappuccino: %.1f dhs\n", c_price);
            break;
        case 3:
            printf("Current price of Mocha: %.1f dhs\n", m_price);
            printf("Enter new price: ");
            scanf("%f", &new_price);
            m_price = new_price;
            printf("New price of Mocha: %.1f dhs\n", m_price);
            break;
        default:
            printf("Invalid input\n");
    }
}

