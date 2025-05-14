// Set <Project5.cpp>
// ECE 312 Project 5 submission by
// <Your Name Here> Swajal Padhi
// <Your EID> skp2628
// Slip days used: <0>
// Fall 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int right = self->len-1;
    int left = 0; 

    while(right >= left){
        int middle = left + (right - left) / 2;
        if(self->elements[middle] == x){
            return true;
        }
        else if(x > self->elements[middle]){
            left = middle + 1;
        }
        else{
            right = middle - 1;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */


void insertSet(Set* self, int x) {
    if (self->len == 0) {
        self->elements = (int*) realloc(self->elements, sizeof(int));
        self->elements[0] = x;
        self->len++;
        return;
    }

    int right = self->len - 1;
    int left = 0;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (self->elements[middle] == x) {
            return;
        } else if (x > self->elements[middle]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    self->elements = (int*) realloc(self->elements, (self->len + 1) * sizeof(int));

    if (x > self->elements[self->len - 1]) {
        self->elements[self->len] = x;
    } else if (x < self->elements[0]) {
        for (int i = self->len; i > 0; i--) {
            self->elements[i] = self->elements[i - 1];
        }
        self->elements[0] = x;
    } else {
        for (int i = self->len; i > left; i--) {
            self->elements[i] = self->elements[i - 1];
        }
        self->elements[left] = x;
    }
    self->len++;
}



/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if (self->len == 0) return; 

    bool removed = false;
    int* newArr = (int*) malloc(self->len * sizeof(int));
    int index = 0;

    for (int i = 0; i < self->len; i++) {
        if (self->elements[i] == x) {
            removed = true;
            continue;
        }
        newArr[index++] = self->elements[i];
    }

    if (!removed) {
        free(newArr);
        return;
    }

    free(self->elements);
    self->elements = (int*) realloc(newArr, index * sizeof(int));
    self->len = index;
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len == other->len){
        for(int i = 0; i < self->len; i++){
            if(self->elements[i] != other->elements[i]) 
                return false;
        }
        return true;
    }
    return false;
            
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    
    if(self->len == 0){ return true; }
    if(other->len == 0) { return false; }

    int j = 0;
    for(int i = 0; i < other->len; i++){
        if(other->elements[i] == self->elements[j]){
            j++;
            if(j == self->len) 
                {break;}
        }
    }

    return j == self->len;
   }

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
      int* newElements = (int*) malloc(self->len * sizeof(int));

    int ind = 0, bid = 0, out = 0;

    while (ind < self->len && bid < other->len) {
        if (self->elements[ind] < other->elements[bid]) {
            ind++;
        } else if (self->elements[ind] > other->elements[bid]) {
            bid++; 
        } else {
            newElements[out++] = self->elements[ind]; 
            ind++;
            bid++;
        }
    }

    free(self->elements);
    self->elements = newElements;
    self->len = out;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    int* newElements = (int*) malloc(self->len * sizeof(int));

    int currentSelfIndex = 0, currentOtherIndex = 0, newElementIndex = 0;

    while (currentSelfIndex < self->len && currentOtherIndex < other->len) {
        if (self->elements[currentSelfIndex] < other->elements[currentOtherIndex]) {
            newElements[newElementIndex++] = self->elements[currentSelfIndex++];
        } else if (self->elements[currentSelfIndex] > other->elements[currentOtherIndex]) {
            currentOtherIndex++; 
        } else {
            currentSelfIndex++; 
            currentOtherIndex++;
        }
    }

    while (currentSelfIndex < self->len) {
        newElements[newElementIndex++] = self->elements[currentSelfIndex++];
    }

    free(self->elements);
    self->elements = newElements;
    self->len = newElementIndex;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    int* newElements = (int*) malloc((self->len + other->len) * sizeof(int));
    int a = 0, b = 0, c = 0;

    while (a < self->len && b < other->len) {
        if (self->elements[a] < other->elements[b]) {
            newElements[c++] = self->elements[a++];
        } else if (self->elements[a] > other->elements[b]) {
            newElements[c++] = other->elements[b++];
        } else { 
            newElements[c++] = self->elements[a++];
            b++;
        }
    }
    while (a < self->len) {
        newElements[c++] = self->elements[a++];
    }

    while (b < other->len) {
        newElements[c++] = other->elements[b++];
    }

    free(self->elements);
    self->elements = newElements;
    self->len = c;
}

 