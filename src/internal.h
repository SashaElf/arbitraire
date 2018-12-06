#ifndef ARBITRAIRE_INTERNAL_H
#define ARBITRAIRE_INTERNAL_H

#ifndef _ARB_DEBUG
#define _ARB_DEBUG 0
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

/* defines */
#define ARBT	int16_t
#define UARBT	uint8_t
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))

/* structures */
typedef struct {		// fxdpnt fixed point type
	UARBT *number;		// The actual number
	char sign;		// Sign
	size_t lp;		// Length left of radix
	size_t len;		// Length of number (count of digits / limbs)
	size_t allocated;	// Length of allocated memory
} fxdpnt;

/* globals */
extern fxdpnt *zero;
extern fxdpnt *p5;
extern fxdpnt *one;
extern fxdpnt *two;
extern fxdpnt *ten;

/* function prototypes */
/* arithmetic */
fxdpnt *arb_mul(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
size_t arb_mul_core(UARBT *, size_t, UARBT *, size_t, UARBT *, int);
fxdpnt *arb_karatsuba_mul(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
fxdpnt *arb_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_sub(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *arb_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
UARBT arb_place(fxdpnt *, fxdpnt *, size_t *, size_t);
fxdpnt *arb_newtonian_div(fxdpnt *, fxdpnt *, fxdpnt *, int, int);
fxdpnt *arb_div(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
int _long_sub(UARBT *, size_t, UARBT *, size_t, int);
int _long_add(UARBT *, size_t, UARBT *, size_t, int);
/* modulus */
fxdpnt *arb_mod(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
/* logical shift */
fxdpnt *arb_rightshift(fxdpnt *, size_t, int);
fxdpnt *arb_leftshift(fxdpnt *, size_t, int);
void rightshift_core(UARBT *, size_t, size_t);
/* general */
void arb_reverse(fxdpnt *);
void arb_flipsign(fxdpnt *);
void arb_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
/* io */
void arb_print(fxdpnt *);
void arb_debug(fxdpnt *, char *);
void arb_printtrue(fxdpnt *);
void _print_core(FILE *, UARBT *, size_t, size_t, size_t);
fxdpnt *arb_str2fxdpnt(const char *);
fxdpnt *arb_parse_str(fxdpnt *, const char *);
int arb_highbase(int);
/* comparison */
int arb_compare(fxdpnt *, fxdpnt *, int);
/* copying */
void _arb_copy_core(UARBT *, UARBT *, size_t);
void *arb_copy(fxdpnt *, fxdpnt *);
void *arb_copyreverse(fxdpnt *, fxdpnt *);
void _arb_copyreverse_core(UARBT *, UARBT *, size_t);
/* sqrt */
fxdpnt *nsqrt(fxdpnt *, int, size_t);
fxdpnt *long_sqrt(fxdpnt *, int, size_t);
/* general */
void arb_init(fxdpnt *);
void arb_error(char *);
/* allocation */
fxdpnt *arb_alloc(size_t);
fxdpnt *arb_expand(fxdpnt *, size_t);
void *arb_malloc(size_t);
void *arb_realloc(void *, size_t);
void *arb_calloc(size_t, size_t);
void arb_free(fxdpnt *);
/* to hardware and back */
fxdpnt *hrdware2arb(size_t);
size_t fxd2sizet(fxdpnt *, int);
/* general */
fxdpnt *remove_leading_zeros(fxdpnt *);
size_t rr(fxdpnt*);
int iszero(fxdpnt*);
/* exp */
fxdpnt *arb_exp(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);
/* novelties */
fxdpnt *old_div(fxdpnt *, fxdpnt *, fxdpnt *, int, size_t);

size_t arb_size(fxdpnt *);
size_t arb_allocated(fxdpnt *);
char arb_sign(fxdpnt *);
size_t arb_left(fxdpnt *);


char *make_bignum(size_t, int, int);

/* function wrappers for simpler math handling */
void incr(fxdpnt **, int, char *);
void decr(fxdpnt **, int, char *);
void sub(fxdpnt *, fxdpnt *, fxdpnt **, int, char *);
void add(fxdpnt *, fxdpnt *, fxdpnt **, int, char *);
void mul(fxdpnt *, fxdpnt *, fxdpnt **, int, size_t, char *);
void divv(fxdpnt *, fxdpnt *, fxdpnt **, int, size_t, char *);

/* oddity */
int oddity(size_t);

/* */
void *_arb_memset(void *, int, size_t);


#define _internal_debug if (_ARB_DEBUG && m) { \
fprintf(stderr, __func__); \
fprintf(stderr, "()  %s", m); \
}
#define _internal_debug_end if (_ARB_DEBUG && m) \
arb_printtrue(*c);

#endif

