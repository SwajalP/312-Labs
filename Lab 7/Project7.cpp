/*
 * Name:
 * EID:
 * PA7
 * Santacruz, Fall 2023
 */

#include "Customer.h"
#include "CustomerDB.h"
#include "UTString.h"
#include <iostream>
#include <stdio.h>

void readString(UTString &);
void readNum(int &);

CustomerDB database;

int num_books = 0;
int num_dice = 0;
int num_figures = 0;
int num_towers = 0;

void reset(void) {
  database.clear();
  num_books = 0;
  num_dice = 0;
  num_figures = 0;
  num_towers = 0;
}

int *selectInventItem(UTString word) {
  if (word == "Books") {
    return &num_books;
  } else if (word == "Dice") {
    return &num_dice;
  } else if (word == "Figures") {
    return &num_figures;
  } else if (word == "Towers") {
    return &num_towers;
  }

  /* NOT REACHED */
  return 0;
}

int *selectInventItem(UTString word, Customer &cust) {
  if (word == "Books") {
    return &cust.books;
  } else if (word == "Dice") {
    return &cust.dice;
  } else if (word == "Figures") {
    return &cust.figures;
  } else if (word == "Towers") {
    return &cust.towers;
  }

  /* NOT REACHED */
  return 0;
}

Customer *findMax(UTString type) {
  Customer *result = 0;
  int max = 0;
  for (int k = 0; k < database.size(); k += 1) {
    Customer &cust = database[k];
    int *p = selectInventItem(type, cust);
    if (*p > max) {
      max = *p;
      result = &cust;
    }
  }

  return result;
}

void processPurchase() {
  UTString name; readString(name);
  UTString s1; readString(s1);
  int quantity; readNum(quantity);
  

  if(*selectInventItem(s1) >= quantity){
    Customer& c = database[name]; 


    *selectInventItem(s1,c) += quantity;
    *selectInventItem(s1) -= quantity;
    
  } else {
    std::cout << "Sorry " << name.c_str() << ", we only have " << *selectInventItem(s1) << " " << s1.c_str() << "\n";
  }
}

void processReturn() {
  UTString name; readString(name);
  UTString s1; readString(s1);
  int quantity; readNum(quantity);

  if (!database.isMember(name)) {
    std::cout << "Sorry " << name.c_str() << ", we do not have you in our database\n";
    return;
  }

  Customer& c = database[name];
  if(*selectInventItem(s1,c) >= quantity){
    *selectInventItem(s1) += quantity;
    *selectInventItem(s1,c) -= quantity;
  } else {
    std::cout << name.c_str() << ", you do not have " << quantity << " " << s1.c_str() << "\n";
  }
}

void processInventory() {

  
  UTString s1; readString(s1);
  int quantity; readNum(quantity);
  *selectInventItem(s1) += quantity;
}

void processSummarize() {
  std::cout << "There are " << num_books << " Books " << num_dice << " Dice " << num_figures << " Figures and " << num_towers << " Towers in inventory\n";
  std::cout << "we have had a total of " << database.size() << " different customers\n";

  Customer *maxBooksCust = findMax("Books");
  Customer *maxDiceCust = findMax("Dice");
  Customer *maxFiguresCust = findMax("Figures");
  Customer *maxTowersCust = findMax("Towers");
 
  if (maxBooksCust) {
    std::cout << maxBooksCust->name.c_str() << " has purchased the most Books (" << maxBooksCust->books << ")\n";
  } else {
    std::cout << "no one has purchased any Books\n";
  }

  if (maxDiceCust) {
    std::cout << maxDiceCust->name.c_str() << " has purchased the most Dice (" << maxDiceCust->dice << ")\n";
  } else {
    std::cout << "no one has purchased any Dice\n";
  }

  if (maxFiguresCust) {
    std::cout << maxFiguresCust->name.c_str() << " has purchased the most Figures (" << maxFiguresCust->figures << ")\n";
  } else {
    std::cout << "no one has purchased any Figures\n";
  }

  if (maxTowersCust) {
    std::cout << maxTowersCust->name.c_str() << " has purchased the most Towers (" << maxTowersCust->towers << ")\n";
  } else {
    std::cout << "no one has purchased any Towers\n";
  }
}