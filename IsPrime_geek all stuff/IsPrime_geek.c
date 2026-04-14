#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For access()
#include <math.h>

void Help(char * progname) {
  fprintf (stderr, "\nUsage: %s [-h] [--help] file_name field_number\n", progname);
  fputs ("\nPARAMETERS:\n\
    file_name    is the full path of a file containing a column of \n\
                 non-negative integers to be checked for primality.\n\
                 The filename must not begin with the '-' character.\n\
                 Column separators are strings composed of any\n\
                 number of spaces or tabs.\n\
                 Lines that start with the character '#' or without\n\
                 a field 'field_number' or with a non-numeric field\n\
                 'field_number' will be considered comment lines\n\n\
    field_number is a positive integer that specifies the number of the\n\
                 column to be read, to check the primality of its\n\
                 elements.\n\n\n", stderr);
  exit(1);
}

#define MAX_NUM_COL_IN_FILE 32768
#define NUM_PRIMES_IN_TABLE 49999999
#define LAST_PRIME_IN_TABLE 982451653
#define SQUARE_OF_LAST_PRIME_IN_TABLE 965211250482432409

#include "THE50millionprimes_array.c"

int IsPrime_geek (const unsigned long int p) {
    if (p < 3) { if (p == 2) return 1; else return 0; }
    if ((p & 1UL) == 0 && p != 2) return 0;

/* First filter: Primality by Binary search */
    if (p <= LAST_PRIME_IN_TABLE) {
       if (p == the_primes_list[0] || p == LAST_PRIME_IN_TABLE) return 1;
       register unsigned int start=0U, afterend=NUM_PRIMES_IN_TABLE, middle, try;
       int isprime = 0;
       while (afterend > start){
             middle = start + ((afterend-start-1)>>1); try = the_primes_list[middle];
             if (p == try) { isprime = 1; break; }
             else if ( p > try ) start = middle + 1; else afterend = middle;
       }
       return isprime;
    }

/* Second filter: finding a divisor.
 * We are not confident on floor(sqrt(.)).
 * The strange formula for usqrtp is to be sure that
 *     sqrt(p) = LAST_PRIME_IN_TABLE  for every p >= SQUARE_OF_LAST_PRIME_IN_TABLE.
 * In particular, sqrt(SQUARE_OF_LAST_PRIME_IN_TABLE) = LAST_PRIME_IN_TABLE */
    unsigned int usqrtp = floor(sqrt((double) p) + 1);
    usqrtp = (((p < SQUARE_OF_LAST_PRIME_IN_TABLE) && (usqrtp < LAST_PRIME_IN_TABLE)) ?  usqrtp : LAST_PRIME_IN_TABLE);
    int isprime = 1;
    for (unsigned i=0; i < NUM_PRIMES_IN_TABLE && the_primes_list[i] <= usqrtp ; i++) {
        if ((p % the_primes_list[i]) == 0) { isprime = 0; break; }
    }

    if (isprime == 0) return 0;
    if (p > SQUARE_OF_LAST_PRIME_IN_TABLE) return -1;
    return 1;
} /* End of function IsPrime_geek */

int IsAllDigits (char * s) {
  while (*s) { if (*s > 57 || *s < 48) return 0; s++; }
  return 1;
}

int main (int argc, char *argv[]) {
    if ( argc != 3 ||
         !strlen(argv[1]) || argv[1][0] == '-' ||
         !strlen(argv[2]) || argv[2][0] == '-' || !IsAllDigits(argv[2]) ) Help(argv[0]);
    unsigned long int colnum = strtoul(argv[2], NULL, 10);
    if (colnum == 0 || colnum > MAX_NUM_COL_IN_FILE) Help(argv[0]);

    FILE * fin;
    if (access(argv[1], R_OK) || (fin = fopen (argv[1], "r")) == NULL) {
       fprintf (stderr, "\nERROR: The task file '%s' containing the presumed prime numbers does not exist or is unreadable.\nAborting ...\n\n\n", argv[1]);
       exit(6);
    }

    FILE * fpout = stdout;
    ssize_t len_line_input;
    char *line_input = NULL; size_t linlen = 0;
    while ((len_line_input = getline(&line_input, &linlen, fin)) > 0) {
          if (line_input[len_line_input-1] == '\n') { len_line_input--; line_input[len_line_input] = 0; }
          if (*line_input == '#' || len_line_input == 0) { fprintf (fpout, "%s\n", line_input); continue; }

          fputs (line_input, fpout);

          char * field = strtok (line_input, " \t");
          for (int i = 1; i < colnum; i++) field = strtok (NULL, " \t");
          if (field == NULL || !IsAllDigits(field)) { fputs ("\n", fpout); continue; }

          unsigned long int period = strtoul(field, NULL, 10);
          if (period < 3)      { fputs ("  --  Impossible period\n", fpout); continue; }
          if (!(period & 1UL)) { fputs ("  --  Even period. It cannot be prime\n", fpout); continue; }

          int res = IsPrime_geek(period);
          if (res == 1)      fputs ("  --  Is prime\n", fpout);
          else if (res == 0) fputs ("  --  Is NOT prime\n", fpout);
          else fputs ("  --  Impossible to determine the primality of the period with this algorithm\n", fpout);
    }
    free(line_input);

    fclose(fin);

    return 0;
}
