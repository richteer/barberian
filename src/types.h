#ifndef _types_h_
#define _types_h_

typedef struct {
	int number;
	int proctime;
	int maxwait;
} barb_t;

typedef struct {
	int number;
	int variance;
	int delay;
} cust_t;

#endif
