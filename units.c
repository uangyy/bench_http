#include <stdio.h>
#include <string.h>

#include "units.h"

struct units number_units = {
    .scale = 1000,
    .base = "",
    .units = {"K", "M", "G", "T", "P", NULL}
};

struct units binary_units = {
    .scale = 1024,
    .base = "",
    .units = {"K", "M", "G", "T", "P", NULL},
};

struct units time_units_s = {
    .scale = 60,
    .base = "s",
    .units = {"m", "h", NULL}
};

static int scan_units(char *ptr, uint64_t *n, struct units *units)
{
    uint64_t scale = 1, base;
    char unit[3] = {0};
    int i, c;
    if ((c = sscanf(ptr, "%"SCNu64"%2s", &base, unit)) < 1) return -1;

    if (c == 2 && strncasecmp(unit, units->base, 3))
    {
        for (i = 0; units->units[i] != NULL; ++i)
        {
            scale *= units->scale;
            if (!strncasecmp(unit, units->units[i], 3))
                break;
        }
        if (units->units[i] == NULL)
            return -1;
    }
    
    *n = base * scale;
    return 0;
}

int scan_number(char *ptr, uint64_t *n)
{
    return scan_units(ptr, n, &number_units);
}

int scan_time(char *ptr, uint64_t *n)
{
    return scan_units(ptr, n, &time_units_s);
}
