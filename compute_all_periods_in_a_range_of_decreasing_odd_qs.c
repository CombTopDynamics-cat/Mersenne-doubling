#include <stdio.h>
#include <stdlib.h> // For the exit and strtoul functions
#include <string.h>
#include <stdbool.h>

void Help(char * progname) { 
  fprintf (stderr, "\nUsage: %s q_ini q_end\n\nThis program works only for periods larger than 16.\nThus, q_ini, q_end > 16.\n\n\n", progname); 
  exit(1);
}
bool IsAllDigits (char * s) { 
  while (*s) { if (*s > 57 || *s < 48) return false; s++; }
  return true;
}

short floor_log2(unsigned long int x) {
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
}

int main (int argc, char *argv[]) {
    if ( argc != 3 || 
         !strlen(argv[1]) || !IsAllDigits(argv[1]) ||
         !strlen(argv[2]) || !IsAllDigits(argv[2]) ) Help(argv[0]);
    
    register unsigned long int q      = strtoul(argv[1], NULL, 10);
             unsigned long int q_last = strtoul(argv[2], NULL, 10);
             
    if (q < q_last) { unsigned long int swap = q; q = q_last; q_last = swap; }
    if (q_last < 17) Help(argv[0]);
    
    if ((q_last & 1UL)) q_last--; // q_last is odd
    if (!(q & 1UL)) q--;          // q is even
    if (q < q_last) Help(argv[0]);

/* To business */
    while (q > q_last) {
      fprintf(stdout, "q = %15lu period = %15lu\n", q, period(q)); fflush(stdout);
      q -= 2;
    }

    return 0;
}
