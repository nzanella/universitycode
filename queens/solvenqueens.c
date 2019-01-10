/* find all solutions to the n-queens problem for a specified value of n */

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define N 100 /* maximum number of chessboard rows/columns */

typedef int Bool;
int n;
int row, col[N + 1];
Bool north_enemy[N + 1] = {FALSE}, 
     neast_enemy[2 * N] = {FALSE}, 
     nwest_enemy[2 * N] = {FALSE};
/* since array subscripts must start at zero an extra array element 
   is accounted for in each of the above array declarations */
Bool condensed;
long int count = 0;

void get_n(void);
Bool condensed_output(void);
void place(void);
void print_solution(Bool condensed);

main()
{
   get_n();
   condensed = condensed_output();

   row = 1;
   place();

   printf("\n");
   printf("There are %d solutions to the %d-queens problem.", count, n);
   printf("\n\n");

   return 0;
}

/**********************************************************
 * place: recursive function used to find all solutions   *
 *        an n-queens problem.                            *
 **********************************************************/

void place(void)
{
   int k;

   for (k = 1; k <= n; k++) {
      if (!north_enemy[k] && !neast_enemy[row + k - 1] && !nwest_enemy[row - k + n]) {
         col[row] = k;
         if (row == n) {
            ++count;
            print_solution(condensed);
            break;
         }
         else {
            north_enemy[k] = TRUE;
            neast_enemy[row + k - 1] = TRUE;
            nwest_enemy[row - k + n] = TRUE;
            ++row;
            place();
         }
      }
   }
   --row;
   north_enemy[col[row]] = FALSE;
   neast_enemy[row + col[row] - 1] = FALSE;
   nwest_enemy[row - col[row] + n] = FALSE;
}

/**********************************************************
 * get_n: prompt user for the number n of rows/columns.   *
 *        Read all characters entered by user up to the   *
 *        newline character. Repeat if either invalid     *
 *        data has been entered or n fails to fall within *
 *        right range.                                    *
 **********************************************************/

void get_n(void)
{
   Bool invalid_data;
   char check_character;

   do {
      do {
         invalid_data = FALSE;

         printf("\n");
         printf("Enter n: ");
         scanf("%d", &n);

         do {
            scanf("%c", &check_character);
            if (check_character != ' ' && check_character != '\t'
                && check_character != '\n')
               invalid_data = TRUE;
         } while (check_character != '\n');
         if (invalid_data) {
            printf("\n");
            printf("You have entered invalid data. Try again.\n");
         }
      } while (invalid_data);

      if (n < 1) {
         printf("\n");
         printf("I was expecting a positive n. Try again.\n");
      }
      if (n > N) {
         printf("\n");
         printf("Sorry, n may not exceed %d. Try again.\n", N);
      }
   } while (n < 1 || n > N);
}

/**********************************************************
 * condensed_output: ask user whether condensed output is *
 *                   preferable and return a boolean      *
 *                   value. If usatisfactory answer is    *
 *                   given then read remaining garbage    *
 *                   and ask again.                       *
 **********************************************************/

Bool condensed_output(void)
{
   Bool ask_again;
   char answer;
   char garbage;

   do {
      ask_again = FALSE;
      printf("\n");
      printf("Request condensed output? (y/n) ");
      scanf(" %c", &answer);
      if (answer == 'y' || answer == 'Y')
         condensed = TRUE;
      else if (answer == 'n' || answer == 'N')
         condensed = FALSE;
      else {
         printf("\n");
         printf("I am having trouble interpreting your answer. Try again.\n");
         do {
            scanf("%c", &garbage);
         } while (garbage != '\n');
         ask_again = TRUE;
      }
   } while (ask_again);
   return condensed;
}

/**********************************************************
 * print_solution: prints a solution to the n-queens      *
 *                 problem.                               *
 **********************************************************/

void print_solution(Bool condensed)
{
   int i, j;
   char queen = 'Q';

   printf("\n");
   if (condensed) {
      printf("( %d", col[1]);
      for (i = 2; i <= n; i++)
         printf(", %d", col[i]);
      printf(" )");
      printf("\n");
   }
   else {
      printf(",");
      for (j = 1; j <= n; j++)
         printf("_,");
      printf("\n");
      for (i = 1; i <= n; i++) {
         printf("|");
         for (j = 1; j <= n; j++)
            if (j == col[i])
               printf("%c|", queen);
            else
               printf("_|");
         printf("\n");
      }
   }
   printf("\n");
}
