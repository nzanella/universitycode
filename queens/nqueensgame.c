/* plays n-queens game with user */

#include <stdio.h>
#include <ctype.h>

#define N 38 /* maximum number of chessboard rows/columns */
#define QUEEN 'Q'
#define BAD_SPOT 'X'
#define TRUE 1
#define FALSE 0

typedef int Bool;

int n;
int col[N + 1];
Bool vert_enemy[N + 1];
Bool diag1_enemy[(2 * N - 1) + 1];
Bool diag2_enemy[(2 * N - 1) + 1];
Bool cheat;

void get_n(void);
char get_answer(const char question[]);
char get_task(void);
Bool get_position(int *r, int *c);
void describe_game(void);
void print_chessboard(void);

main()
{
   int queens_placed;

   for(;;) {
      describe_game();
      get_n();
      printf("\nCheaters' version of the game helps you solve it by marking\n\n");
      printf("all threatened chessboard positions with the \" %c \" sign.\n", BAD_SPOT);
      switch (get_answer("Play cheaters' version? (y/n) ")) {
         case 'y': cheat = TRUE;
                   break;
         case 'n': cheat = FALSE;
                   break;
      }

      /* perform initializations each time user wishes to play/replay */

      {
         int i;
         queens_placed = 0;
         for (i = 1; i <= n; i++) {
            col[i] = 0;
            vert_enemy[i] = FALSE;
         }
         for (i = 1; i <= 2 * n - 1; i++) {
            diag1_enemy[i] = FALSE;
            diag2_enemy[i] = FALSE;
         }
      }

      for(;;) {
         char task;
         Bool bad_pos = FALSE;
         int row, temp_col;

         print_chessboard();
 
         task = get_task();

         /* begin carrying out specified task */

         if (task == 'p' || task == 'r') {
            if (!get_position(&row, &temp_col))
               continue;
         }
         else if (task == 'n')
            if (get_answer("Abandon current game and start a new one? (y/n) ") == 'y')
               break;
            else
               continue;
         else if (task == 'q')
            if (get_answer("Really quit? (y/n) ") == 'y') {
               printf("\n");
               return 0;
            }
            else
               continue;

         /* warn user of the impossibility of placing or removing */
         /* a queen at the specified position if such is the case */

         if (task == 'p') {
            if (temp_col == col[row]) {
               printf("\nSorry, can't fit two queens in the same spot. ");
               bad_pos = TRUE;
            }
            else if (col[row] != 0) {
               printf("\nCannot place; there's a queen in that row. ");
               bad_pos = TRUE;
            }
            else if (vert_enemy[temp_col]) {
               printf("\nCannot place; there's a queen in that column. ");
               bad_pos = TRUE;
            }
            else if (diag1_enemy[row + temp_col - 1] || diag2_enemy[row - temp_col + n]) {
               printf("\nCannot place; a queen can also attack diagonally. ");
               bad_pos = TRUE;
            }
         }
         else if (task == 'r')
            if (temp_col != col[row]) {
               printf("\nThere are no queens there. ");
               bad_pos = TRUE;
            }
         if (bad_pos) {
            printf("( <enter> to continue ) ");
            while (getchar() != '\n')
               ;
            continue;
         }

         /* place or remove queen, keep track of enemies */
         /* and ask whether user wants to play another   */
         /* game in case of victory                      */

         if (task == 'p') {
            col[row] = temp_col;
            ++queens_placed;
            vert_enemy[col[row]] = TRUE;
            diag1_enemy[row + col[row] - 1] = TRUE;
            diag2_enemy[row - col[row] + n] = TRUE;
            if (queens_placed == n) {
               print_chessboard();
               printf("\n");
               printf("Congra\atula\ations! You so\alved it!!!!\n");
               if (get_answer("Play again? (y/n) ") == 'n') {
                  printf("\n");
                  return 0;
               }
               else
                  break;
            }
         }
         else {
            col[row] = 0;
            --queens_placed;
            vert_enemy[temp_col] = FALSE;
            diag1_enemy[row + temp_col - 1] = FALSE;
            diag2_enemy[row - temp_col + n] = FALSE;
         }
      }
   }
}

/**********************************************************
 * describe_game: describes the n-queens game by printing *
 *                a messgae on the screen.                *
 **********************************************************/

void describe_game(void)
{
   printf("\nGame Description:\n\n");
   printf("Place n queens on an nxn chessboard so that no\n\n");
   printf("two queens attack each other. (that is, so that no\n\n");
   printf("two queens are on the same row, column, or diagonal)\n");
}

/**********************************************************
 * get_n: prompt user for number of chessboard            *
 *        rows/columns. Read all characters entered by    *
 *        user up to the newline character. Repeat if     *
 *        either meaningless data or an illegal number of *
 *        rows/columns is entered.                        *
 **********************************************************/

void get_n(void)
{
   Bool invalid_int_val;
   char next_char;

   for (;;) {
      invalid_int_val = FALSE;
      printf("\n");
      printf("Enter the number n: ");
      scanf("%d", &n);
      for(;;) {
         if ((next_char = getchar()) == '\n')
            break; 
         else if (next_char != ' ' && next_char != '\t') {
            invalid_int_val = TRUE;
            for(; getchar() != '\n';)
               ;
            break;
         }
      }
      if (invalid_int_val || n < 1 || n > N) {
         printf("\n");
         printf("The number n must be an integer between 1 and %d.\n", N);
      }
      else
         break;
   }
}

/**********************************************************
 * get_answer: prompt user with a message and return 'y'  *
 *             or 'n' according to user's response.       *
 **********************************************************/

char get_answer(const char question[])
{
   char ch;
   char next_char;
   Bool ask_again;

   do {
      ask_again = FALSE;
      printf("\n");
      printf("%s", question);
      while ((ch = getchar()) == ' ' || ch == '\t')
         ;
      if (ch == '\n')
         ask_again = TRUE;
      else {
         ch = tolower(ch);
         if (ch != 'y' && ch != 'n') {
            while (getchar() != '\n')
               ;
            ask_again = TRUE;
         }
         else
            while ((next_char = getchar()) != '\n')
               if (next_char != ' ' && next_char != '\t') {
                  while (getchar() != '\n')
                     ;
                  ask_again = TRUE;
                  break;
               }
      }
      if (ask_again) {
         printf("\n");
         printf("You must enter \" y \" for yes or \" n \" for no.\n");
      }
   } while (ask_again);

   return ch;
}

/**********************************************************
 * get_task: prompt user for a task and return character  *
 *           corresponding to the specified task.         *
 **********************************************************/

char get_task(void)
{
   char ch;
   char next_char;
   Bool prompt_again;

   do {
      prompt_again = FALSE;
      printf("\n");
      printf("p: place   r: remove   n: new game   q: quit   ?? ");
      while ((ch = getchar()) == ' ' || ch == '\t')
         ;
      if (ch == '\n')
         prompt_again = TRUE;
      else {
         ch = tolower(ch);
         if (ch != 'p' && ch != 'r' && ch != 'n' && ch != 'q') {
            while (getchar() != '\n')
               ;
            prompt_again = TRUE;
         }
         else
            while ((next_char = getchar()) != '\n')
               if (next_char != ' ' && next_char != '\t') {
                  while (getchar() != '\n')
                     ;
                  prompt_again = TRUE;
                  break;
               }
      }
      if (prompt_again) {
         printf("\nYou must first enter one of \" p \", \" r \", \" n \", or \" q \". ");
         printf("( <enter> to continue ) ");
         while (getchar() != '\n')
            ;
         print_chessboard();
      }
   } while (prompt_again);
   
   return ch;
}

/**********************************************************
 * get_position: tries to obtain valid row and column     *
 *               numbers from user. Returns TRUE if       *
 *               attempt is successful and FALSE if       *
 *               attempt fails.                           *
 **********************************************************/

Bool get_position(int *r, int *c)
{
   int number;
   Bool invalid_int_val;
   char next_char;
   int coord_num;

   printf("\n");
   for (coord_num = 1; coord_num <= 2; coord_num++) {
      for (;;) {
         invalid_int_val = FALSE;
         switch (coord_num) {
            case 1: printf("row number: ");
                    break;
            case 2: printf("column number: ");
                    break;
         }
         scanf("%d", &number);
         for(;;) {
            if ((next_char = getchar()) == '\n')
               break; 
            else if (next_char != ' ' && next_char != '\t') {
               invalid_int_val = TRUE;
               for(; getchar() != '\n';)
                  ;
               break;
            }
         }
         if (invalid_int_val || number < 1 || number > n) {
            printf("\n");
            printf("You must enter an integer between 1 and %d. ", n);
            printf("( <enter> to continue ) ");
            while (getchar() != '\n')
               ;
            return FALSE;
         }
         else
            break;
      }
      switch (coord_num) {
         case 1: *r = number;
                 break;
         case 2: *c = number;
                 break;
      }
   }
   return TRUE;
}

/**********************************************************
 * print_chessboard: prints nxn chessboard, queens, and   *
 *                   danger signs if cheaters' version of *
 *                   game was requested.                  *
 **********************************************************/

void print_chessboard(void)
{
   int i, j;
   int k, l;

   putchar('\n');

   /* print top row of digits if necessary */

   if (n > 9) {
      printf("   ");
      printf(" ");
      for (k = 1; k <= 9; k++)
         printf("  ");
      for (k = 10; k <= n; k++)
         printf("%d ", k / 10);
      printf("\n");
   }

   /* print bottom row of digits */

   printf("   ");
   printf(" ");
   for (k = 1, l = 1; k <= n; k++, l++) {
      printf("%d ", l);
      if (l == 9)
         l -= 10;
   }

   /* print digits on the left, chessboard, queens, and */
   /* danger signs if cheaters' version was requested   */

   printf("\n");
   printf("   ");
   printf(",");
   for (j = 1; j <= n; j++)
      printf("_,");
   printf("\n");
   for (i = 1; i <= n; i++) {
      printf("%2d ", i);
      printf("|");
      for (j = 1; j <= n; j++)
         if (j == col[i])
            printf("%c|", QUEEN);
         else if (cheat) {
            if (col[i] != 0 || vert_enemy[j] ||
                diag1_enemy[i + j - 1] || diag2_enemy[i - j + n])
               printf("%c|", BAD_SPOT);
            else
               printf("_|");
         }
         else printf("_|");
      printf("\n");
   }
   printf("\n");
}
