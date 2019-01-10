/* lists either all combinations or all permutations of */
/* r elements taken from a set of n elements            */

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define N 20 /* maximum number of array elements */

typedef int Bool;

int a[N + 1], n;
int k[N + 1], r;
int b[N + 1];
Bool only_combinations;
int p;
Bool move_right;

/* functions used in computing and outputing combinations */
void next_subscript(int m, int j);
void print_combination(void);

/*functions used in computing and outputing permutations */
void next_move(void);
void next_permutation(int q);
void print_permutation(void);

/* miscellaneous functions used in main */
void get_answer(void);
int get_int(char name[], int lower_bound, int upper_bound);
void initialize_a(void);
void copy_elements(void);

main()
{
   n = get_int("n", 0, N);
   r = get_int("r", 0, n);
   initialize_a();
   get_answer();

   /* take care of rare special case whenever r = 0 */
   if (r == 0) {
      if (only_combinations)
         printf("\n{ }\n\n");
      else
         printf("\n( )\n\n");
      return 0;
   }

   next_subscript(1, 1);

   return 0;
}

/**********************************************************
 * next_subscript: recursive function determining value   *
 *                 of subscript k[m] of mth element of a  *
 *                 to be included in a combination. If    *
 *                 all r subscripts have been determined  *
 *                 then corresponding array elements are  *
 *                 printed otherwise next_subscript calls *
 *                 itself.                                *
 **********************************************************/

void next_subscript(int m, int j)
{
   int i;

   for (i = j; i <= n - r + m; i++) {
      k[m] = i;
      if (m < r)
         next_subscript(m + 1, i + 1);
      else {
         if (only_combinations)
            print_combination();
         else {
            copy_elements();
            p = 0;
            move_right = TRUE;
            next_move();
         }
      }
   }
}

/**********************************************************
 * next_move: recursive function used to compute the      *
 *            values of p and q to be used in calls of    *
 *            next_permutation. The variables p and q     *
 *            themselves act as special subscripts to the *
 *            array elements of b.                        *
 **********************************************************/

void next_move(void)
{
   int q;

   for (;;) {
      if (move_right) {
         ++p;
         q = r;
         if (p == r - 1) {
            print_permutation();
            next_permutation(q);
            print_permutation();
            move_right = FALSE;
            break;
         }
         else if (p < r - 1)
            next_move();
         else {
             /* take care of rare special case when r equals 1 */
            print_permutation();
            break;
         }
      }
      else {
         --p;
         if (p < q) {
            next_permutation(q);
            --q;
            move_right = TRUE;
            next_move();
         }
         else
            break;
      }
   }
}

/**********************************************************
 * next_permutation: replaces the whole array by a new    *
 *                   one representing a new permutation.  *  
 **********************************************************/

void next_permutation(int q)
{
   int i;
   int temp[N + 1];
   int top = p;

   temp[top] = b[q];
   ++top;

   for (i = r; i > q; top++, i--)
      temp[top] = b[i];

   temp[top] = b[p];
   ++top;

   for (i = q - 1; i > p; top++, i--)
      temp[top] = b[i];

   for (i = p; i <= r; i++)
      b[i] = temp[i];
}

/**********************************************************
 * print_combination: prints a combination of r elements  *
 *                    of a.                               *
 **********************************************************/

void print_combination(void)
{
   int i;

   printf("\n");
   printf("{ %2d", a[k[1]]);
   for (i = 2; i <= r; i++)
      printf(", %2d", a[k[i]]);
   printf(" }\n\n");
}

/**********************************************************
 * print_permutation: prints a permutation of r elements  *
 *                    of b.                               *
 **********************************************************/

void print_permutation(void)
{
   int i;

   printf("\n");
   printf("( %2d", b[1]);
   for (i = 2; i <= r; i++)
      printf(", %2d", b[i]);
   printf(" )\n\n");
}

/**********************************************************
 * get_int: prompt user for an int value. Read all        *
 *          characters entered by user up to the newline  *
 *          character. Repeat if either invalid data or   *
 *          an int value failing to fall within specified *    
 *          range is entered.                             *
 **********************************************************/

int get_int(char name[], int lower_bound, int upper_bound)
{
   int int_value;
   char test_valid;
   Bool valid;
 
   for (;;) {
      valid = TRUE;
      printf("\n");
      printf("Enter %s: ", name);
      scanf("%d", &int_value);
      while ((test_valid = getchar()) != '\n')
         if (test_valid != ' ' && test_valid != '\t')
            valid = FALSE;
      if (valid && (int_value < lower_bound || int_value > upper_bound))
         valid = FALSE;
      if (!valid) {
         printf("\n");
         printf("%s must be an integer between %d and %d.\n",
                name, lower_bound, upper_bound);
      }
      else
         break;
   }

   return int_value;
}

/**********************************************************
 * initialize_a: initializes array a.                     *
 **********************************************************/

void initialize_a(void)
{
   int i;

   for (i = 1; i <= n; i++)
      a[i] = i;
}


/**********************************************************
 * get answer: Ask user whether combinations only or      *
 *             permutations also should be listed by the  *
 *             program. Repeat until a satisfactory       *
 *             is provided.                               *
 **********************************************************/

void get_answer(void)
{
   char answer;

   for(;;) {
      printf("\n");
      printf("Combine only or permute too? (c/p) ");
      answer = getchar();
      while (getchar() != '\n')
         ;
      if (answer == 'c' || answer == 'C') {
         only_combinations = TRUE;
         break;
      }
      if (answer == 'p' || answer == 'P') {
         only_combinations = FALSE;
         break;
      }
   }
}

/**********************************************************
 * copy_elements: copies a selected sequence of r         *
 *                elements of array a to the first r      *
 *                elements of array b.                    *
 **********************************************************/

void copy_elements(void)
{
   int i;

   for (i = 1; i <= r; i++)
      b[i] = a[k[i]];
}
