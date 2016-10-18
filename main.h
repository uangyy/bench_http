#include <getopt.h>

#include "http_parser.h"

struct config;

static int parse_args(int argc, char **argv, struct config *cfg, char **url, struct http_parser_url *parts);
