#include <inttypes.h>

struct units
{
    int scale;
    char *base;
    char *units[];
};

int scan_number(char *, uint64_t *);
int scan_time(char *, uint64_t *);
