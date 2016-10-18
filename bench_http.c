#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "bench_http.h"
#include "main.h"

static struct config{
    uint32_t threads;
    uint32_t duration;
    uint32_t connections;
    char *host;
}cfg;

static void usage()
{
    fprintf(stderr, "Usage: bench_http <option> <url>              \n"
            "  Options:                                            \n"
            "    -c, --connections <N>  Connections to keep open   \n"
            "    -d, --duration    <T>  Duration of test           \n"
            "    -t, --threads     <N>  Number of threads to use   \n"
            "                                                      \n"
            "                                                      \n");
}

int main(int argc, char **argv)
{
    char *url;
    struct http_parser_url parts;
    if (parse_args(argc, argv, &cfg, &url, &parts) == -1)
    {
        usage();
        exit(1);
    }
    return 0;
}

static struct option longopts[] = {
    { "connections", required_argument, NULL, 'c' },
    { "duration",    required_argument, NULL, 'd' },
    { "threads",     required_argument, NULL, 't' },
    { NULL,          0,                 NULL,  0  }
};

static int parse_args(int argc, char **argv, struct config *cfg, char **url, struct http_parser_url *parts)
{
    char c;

    memset(cfg, 0, sizeof(*cfg));
    cfg->threads = 1;
    cfg->connections = 10;
    cfg->duration = 100;

    while ((c = getopt_long(argc, argv, "c:t:d:", longopts, NULL)) != -1)
    {
        switch(c)
        {
            case 't':
                if ((cfg->threads = atoi(optarg)) == -1) return -1;
                break;
            case 'c':
                if ((cfg->connections = atoi(optarg)) == -1) return -1;
                break;
            case 'd':
                if ((cfg->duration = atoi(optarg)) == -1) return -1;
                break;
            case ':':
            case '?':
            default:
                return -1;
        }
    }

    if (optind == argc || !cfg->threads || !cfg->duration) return -1;
    if (!cfg->connections || cfg->connections < cfg->threads)
    {
        fprintf(stderr, "conenctions must >= threads\n");
        return -1;
    }

    if (http_parser_parse_url(argv[optind], strlen(argv[optind]), 0, parts))
    {
        fprintf(stderr, "invalid URL:%s\n", argv[optind]);
        return -1;
    }

    *url = argv[optind];
    return 0;
}
