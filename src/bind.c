#include "main.h"

typedef struct {
	char *str;  // token string
	int type;   // token type
	int val;    // number
} token_t;

const char* get_token_type(int type);

static inline int parity(unsigned int x)
{
	x ^= x >> 1;
	x ^= x >> 2;
	x = (x & 0x11111111U) * 0x11111111U;
	return (x >> 28) & 1;
}
