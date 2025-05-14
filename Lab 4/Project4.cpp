/*
 * EE312 Simple CRM Project
 * Swajal Padhi
 * SKP2628 
 * No Skips Used
 */

#include "Invent.h"
#include "MyString.h"
#include <stdio.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0, num; 

String type, name;

int diceInv = 0, figInv = 0;
int towInv = 0, bookInv = 0;
int cusIndex = -1;

void reset(void);
void processSummarize();
void processPurchase();
void processReturn();
void processInventory();
int* getType(Customer* c1, String* itemType);
void parse(String* name, String* type, int* num);
int indexInDatabase();
int itemBought(Customer* c1); 
Customer* categoryHigh(String* product_type); 

void reset(void) {  
    for(int i = 0; i < num_customers; i++) {
        StringDestroy(&customers[i].name);
    } 
    num_customers = 0;
    diceInv = figInv = towInv = bookInv = 0;
}

void processSummarize() {
    printf("There are %d Books %d Dice %d Figures and %d Towers in inventory\n", 
           bookInv, diceInv, figInv, towInv);
    printf("we have had a total of %d different customers\n", num_customers);
    
    String t1 = StringCreate("Books");   
    Customer* topBooks = categoryHigh(&t1);
    if (topBooks) {
        StringPrint(&topBooks->name);
        printf(" has purchased the most Books (%d)\n", topBooks->books);
    } else {
        printf("no one has purchased any Books\n");
    }

    String t2 = StringCreate("Dice");
    Customer* topDice = categoryHigh(&t2);
    if (topDice) {
        StringPrint(&topDice->name);
        printf(" has purchased the most Dice (%d)\n", topDice->dice);
    } else {
        printf("no one has purchased any Dice\n");
    }

    String t3 = StringCreate("Figures");   
    Customer* topFigures = categoryHigh(&t3);
    if (topFigures) {
        StringPrint(&topFigures->name);
        printf(" has purchased the most Figures (%d)\n", topFigures->figures);
    } else {
        printf("no one has purchased any Figures\n");
    }

    String t4 = StringCreate("Towers");
    Customer* topTowers = categoryHigh(&t4);
    if (topTowers) {
        StringPrint(&topTowers->name);
        printf(" has purchased the most Towers (%d)\n", topTowers->towers);
    } else {
        printf("no one has purchased any Towers\n");
    }

    StringDestroy(&t1);
    StringDestroy(&t2); 
    StringDestroy(&t3);
    StringDestroy(&t4);
}

void processPurchase() {
    parse(&name, &type, &num);
    
    if(num <= 0) {
        StringDestroy(&name);  
        StringDestroy(&type);
        return;
    }
    
    cusIndex = indexInDatabase();
    if (cusIndex == -1) { 
        Customer c1;
        c1.name = StringDup(&name); 
        c1.books = 0; c1.dice = 0; c1.figures = 0; c1.towers = 0; 
        if (itemBought(&c1)) {  
            customers[num_customers] = c1;
            cusIndex = num_customers;
            num_customers++;
        }
        else {
            StringDestroy(&c1.name);
        }
    } else {
        itemBought(&customers[cusIndex]);
    }

    StringDestroy(&name);
    StringDestroy(&type);
}

void processReturn() {
    parse(&name, &type, &num); 
    
    if (num <= 0) {
        StringDestroy(&name);
        StringDestroy(&type);
        return;
    }

    cusIndex = indexInDatabase();
    if (cusIndex == -1) {
        printf("Sorry ");
        StringPrint(&name);
        printf(", we do not have you in our database\n");
    } else {
        Customer* c1 = &customers[cusIndex];
        int* typePointer = getType(c1, &type);   
        if (typePointer && *typePointer >= num) {
            *typePointer -= num;
            if (typePointer == &c1->books) bookInv += num;
            if (typePointer == &c1->dice) diceInv += num;
            if (typePointer == &c1->towers) towInv += num;
            if (typePointer == &c1->figures) figInv += num;
        } else {
            StringPrint(&name);
            printf(", you do not have %d ", num);
            StringPrint(&type);
            printf("\n");
        }
    }
    StringDestroy(&name); 
    StringDestroy(&type);
}  

void processInventory() { 
    String itemType;       
    int quantity;          
    
    readString(&itemType);
    readNum(&quantity);

    String s1 = StringCreate("Books");
    String s2 = StringCreate("Dice");
    String s3 = StringCreate("Towers"); 
    String s4 = StringCreate("Figures");

    if (StringIsEqualTo(&itemType, &s1)) {
        bookInv += quantity;
    }
    else if (StringIsEqualTo(&itemType, &s2)) {
        diceInv += quantity;
    }
    else if (StringIsEqualTo(&itemType, &s3)) {
        towInv += quantity;
    }
    else if (StringIsEqualTo(&itemType, &s4)) {
        figInv += quantity;
    }
    
    StringDestroy(&s1);
    StringDestroy(&s2); 
    StringDestroy(&s3);
    StringDestroy(&s4);
    StringDestroy(&itemType); 
}   

int* getType(Customer* c1, String* itemType) {
    String s1 = StringCreate("Books");
    String s2 = StringCreate("Dice");
    String s3 = StringCreate("Towers");
    String s4 = StringCreate("Figures");

    int* result = NULL;

    if (StringIsEqualTo(itemType, &s1)) {
        result = &c1->books;
    } else if (StringIsEqualTo(itemType, &s2)) {
        result = &c1->dice;
    } else if (StringIsEqualTo(itemType, &s3)) {
        result = &c1->towers;
    } else if (StringIsEqualTo(itemType, &s4)) {
        result = &c1->figures;
    }

    StringDestroy(&s1);
    StringDestroy(&s2);
    StringDestroy(&s3);
    StringDestroy(&s4);

    return result;
}

Customer* categoryHigh(String* product_type) {
    int high = -1;
    Customer* highCustomer = NULL;
    for(int i = 0; i < num_customers; i++) {
        int curr = *getType(&customers[i], product_type); 
        if(curr > high) {
            highCustomer = &customers[i]; 
            high = curr;
        }
    }
    return (high > 0) ? highCustomer : NULL; 
}

void parse(String* name, String* type, int* num) {
    readString(name);
    readString(type);  
    readNum(num);
}

int indexInDatabase() {
    for (int i = 0; i < num_customers; i++) {
        if (StringIsEqualTo(&customers[i].name, &name))
            return i;   
    } 
    return -1;
} 

int itemBought(Customer* c1) {  
    int* typePointer = getType(c1, &type);
    if (!typePointer) return 0;

    int* invPointer = NULL;
    if (typePointer == &c1->books) invPointer = &bookInv;
    if (typePointer == &c1->dice) invPointer = &diceInv;
    if (typePointer == &c1->towers) invPointer = &towInv;
    if (typePointer == &c1->figures) invPointer = &figInv;

    if (*invPointer >= num) {
        *typePointer += num;
        *invPointer -= num;
        return 1;
    } else {
        printf("Sorry ");
        StringPrint(&c1->name); 
        printf(", we only have %d ", *invPointer);
        StringPrint(&type);
        printf("\n");
    }
    return 0;
}
 
