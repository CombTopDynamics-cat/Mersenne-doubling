#include <stdio.h>
#include <stdlib.h> // For the exit and strtoul functions
#include <string.h>
#include <stdbool.h>

#include <time.h>
double TiMeOrIgIn_AS_A_GLOBAL_VARIABLE;
double norm_gettime (struct timespec tp) { return (tp.tv_sec + ((double) tp.tv_nsec)/1.0e+9); }
void   clock_reset  (void) { struct timespec tp; clock_gettime(CLOCK_REALTIME, &tp); TiMeOrIgIn_AS_A_GLOBAL_VARIABLE = norm_gettime(tp); }
double time_elapsed (void) { struct timespec tp; clock_gettime(CLOCK_REALTIME, &tp); return (norm_gettime(tp) - TiMeOrIgIn_AS_A_GLOBAL_VARIABLE); }

void Help(char * progname) {
  fprintf (stderr, "\nUsage: %s q_ini q_end\n\nThis program works only for odd Qs larger than 16.\nThus, q_ini and q_end must be larger than 16.\n\n\n", progname);
  exit(1);
}

bool      IsAllDigits (char *);
short int floor_log2(unsigned long int);

#define kappa 4
unsigned long int period (unsigned long int q) { // For large q's. In fact q > 2^{kappa} = 16
   unsigned short int ft, sigmaq = floor_log2(q);

   unsigned long int qh         = (q-1) >> 1,
                     r_boundary = (1UL << (sigmaq - kappa + 1));

   unsigned long int a      = (1UL << sigmaq),
                     r      = a - (q-a),
                     period = sigmaq + 1;

   while (r != 1) {
     if (r < r_boundary) {
        ft = floor_log2( (q - 1) / r );
        a = (r << ft);
     } else { ft = 0; a = r; while (a <= qh) { a += a; ft++; } }

     r = a - (q - a);
     period += (ft + 1);
   }
   return period;
} /* End of function period */

int main (int argc, char *argv[]) {
    if ( argc != 3 ||
         !strlen(argv[1]) || !IsAllDigits(argv[1]) ||
         !strlen(argv[2]) || !IsAllDigits(argv[2]) ) Help(argv[0]);

    unsigned long int q_ini = strtoul(argv[1], NULL, 10);
    unsigned long int q_end = strtoul(argv[2], NULL, 10);
    if (q_ini < 17 || q_end < 17) Help(argv[0]);

    if (q_ini <= q_end) { q_end++;
       register unsigned long int q = q_ini + (((q_ini & 1UL) == 0) ? 1 : 0);
       while (q < q_end) { clock_reset();
             unsigned long int p = period(q);
             double T = time_elapsed();
             fprintf(stdout, "q = %20lu period = %20lu  Computime = %14g\n", q, p, T); fflush(stdout);
             q += 2;
       }
   } else { q_end--;
       register unsigned long int q = q_ini - (((q_ini & 1UL) == 0) ? 1 : 0);
       while (q > q_end) { clock_reset();
             unsigned long int p = period(q);
             double T = time_elapsed();
             fprintf(stdout, "q = %20lu period = %20lu  Computime = %14g\n", q, p, T); fflush(stdout);
             q -= 2;
       }
   }

   return 0;
}

/*******************************************************************************************************
 **************************************    Thecnical functions    **************************************
 *******************************************************************************************************/
bool IsAllDigits (char * s) {
  while (*s) { if (*s > 57 || *s < 48) return false; s++; }
  return true;
}

short int floor_log2(unsigned long int x) {
  static const unsigned char table[] = { 0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
                                         6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
                                         7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
                                         7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
                                         8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                                         8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                                         8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                                         8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
  };

  unsigned char a;
  unsigned int low = x, high = x >> 32;

  a = ((high) ? ((high <= 0xffff) ? ((high <= 0xff) ? 32 : 40) : ((high <= 0xffffff) ?  48 : 56)) :
                ((low  <= 0xffff) ? ((low  <= 0xff) ?  0 :  8) : ((low  <= 0xffffff) ?  16 : 24)));

  return table[x >> a] + a - 1;
}
