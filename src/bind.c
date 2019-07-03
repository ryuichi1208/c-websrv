#include "main.h"

typedef struct {
	char *str;  // token string
	int type;   // token type
	int val;    // number
} token_t;

const char* get_token_type(int type);
