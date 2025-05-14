#include "Recursion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

/* Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and
 * use an "n-1" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums1(int x[], int n, int *calls) {
  *calls += 1;
  // TODO: Your code here
  return 0;
}

/*
 * Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and
 * use an "n/2" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums2(int x[], int n, int *calls) {
  if (*calls == n - 1) return x[0];
  int val = x[n - 1 - *calls];
  *calls += 1;
  return val + x[(n - 1) - *calls];
}

/*
 * Write a recursive function that reverses a positive n-digit integer x.
 * For example, if x = 12345, the function should return 54321.
 */
int reverse(int x, int n, int *calls) {
    *calls += 1;
    if (x < 10) return x;
    return pow(10, n - 1) * (x % 10) + reverse(x / 10, n - 1, calls);
}

/*
 * Given a linked list, remove all nodes that contain the character val
 * Don't forget to free memory for any nodes you remove
*/  
Node* remove_nodes(Node* head, char val, int* calls) {  
  *calls += 1;
  if (head == NULL) return head; 
  else if (head->data == val){ 
    Node* temp = head->next;
    free(head);
    return remove_nodes(temp, val, calls);
  }
  head->next = remove_nodes(head->next, val, calls); 
  return head;
}

/* You are given a list of item weights that represent the weight of the ith
 * index item You are also given a maximum weight that your bag can hold.
 * Return the total weight of the subset of items that maximize the total weight
 * of the bag without going over the maximum weight
 */
int knapsack(int weights[], int n, int max_weight, int *calls) {   
    *calls += 1;
    
    if (max_weight == 0 || n == 0) return 0;
    if (weights[n - 1] > max_weight) return knapsack(weights, n - 1, max_weight, calls);
    int exclude = knapsack(weights, n - 1, max_weight, calls);
    int include = weights[n - 1] + knapsack(weights, n - 1, max_weight - weights[n - 1], calls);
    return (include > exclude) ? include : exclude;
}

// Given a binary tree, return the weight of the least weight path (the path with the smallest sum of node values)
int least_weight_path(BinaryNode* root, int* calls) { 
  *calls += 1;
  if (root == NULL) return INT_MAX;   
  else if (root->left == NULL && root->right == NULL) return root->data;

  int left = least_weight_path(root->left, calls);
  int right = least_weight_path(root->right, calls);

  return root->data + ((left < right) ? left : right);
}

bool is_win(char board[3][3], char player) {
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
  }

  for (int i = 0; i < 3; i++) {
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player)   ||
          (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
      }
   return false;
}


/*
 * Given a tic-tac-toe board, return a Record struct that contains the number of
 * ways that X can win, the number of ways that O can win, and the number of
 * draws from the current board position.
 */
Record tic_tac_toe(char board[3][3], bool is_x_turn, int* calls) {
  *calls += 1;

  Record result = {0, 0, 0};
  
  if (is_win(board, 'X')) {
    result.x_wins = 1;
    return result;
  }
  if (is_win(board, 'O')) {
    result.o_wins = 1;
    return result;
  }
  
  bool has_empty = false;
  int row = -1, col = -1;
  for (int i = 0; i < 3 && !has_empty; i++) {
    for (int j = 0; j < 3 && !has_empty; j++) {
      if (board[i][j] == ' ') {
        has_empty = true;
           row = i;
         col = j;
      }
    }
  }

  if (!has_empty) {result.draws = 1; return result;}


  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = is_x_turn ? 'X' : 'O';

          Record temp_result = tic_tac_toe(board, !is_x_turn, calls);
        board[i][j] = ' ';

        result.x_wins += temp_result.x_wins;
         result.o_wins += temp_result.o_wins;

        result.draws += temp_result.draws;
      }
    }
  }



  return result;
} 

