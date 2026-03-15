#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "Error opening file %s: %s\n",
                filename, strerror(errno));
        return 1;
    }

    uint8_t buffer[BUF_SIZE];
    size_t n;
    unsigned long long total = 0;

    while ((n = fread(buffer, 1, BUF_SIZE, f)) > 0) {
        for (size_t i = 0; i < n; i++) {
            uint8_t b = buffer[i];

            // ВРЕМЕННЫЙ НАИВНЫЙ ПОДСЧЁТ (для проверки логики)
            for (int bit = 0; bit < 8; bit++) {
                if (b & (1u << bit)) {
                    total++;
                }
            }
        }
    }

    fclose(f);

    printf("file %s contains %llu ones.\n", filename, total);
    return 0;
}
