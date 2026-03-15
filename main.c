#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 4096

// Таблица popcount для всех 256 возможных байтов
static uint8_t POPCOUNT_TABLE[256];

// Инициализация таблицы
static void init_popcount_table(void) {
    for (int i = 0; i < 256; i++) {
        uint8_t v = (uint8_t)i;
        uint8_t count = 0;
        while (v) {
            count += v & 1u;
            v >>= 1;
        }
        POPCOUNT_TABLE[i] = count;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *f = fopen(filename, "rb");  // бинарный режим
    if (!f) {
        fprintf(stderr, "Error opening file %s: %s\n",
                filename, strerror(errno));
        return 1;
    }

    init_popcount_table();

    uint8_t buffer[BUF_SIZE];
    size_t n;
    unsigned long long total = 0;

    while ((n = fread(buffer, 1, BUF_SIZE, f)) > 0) {
        for (size_t i = 0; i < n; i++) {
            total += POPCOUNT_TABLE[buffer[i]];
        }
    }

    fclose(f);

    printf("file %s contains %llu ones.\n", filename, total);
    return 0;
}
