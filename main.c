#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : "a2_test.txt";
    FILE *f = fopen(path, "r");
    if (!f) { printf("Error: Could not open %s\n", path); return 1; }

    char line[256];
    int test_num = 1;

    while (fgets(line, sizeof(line), f)) {
        // skip comments and empty
        if (line[0] == '#' || line[0] == '\n') continue;

        // handle tests
        char func[32], in[128], expected[256], actual[256];
        if (sscanf(line, "%31s %127s %255s", func, in, expected) != 3) {

            continue;
        }

        if (strcmp(func, "oct_to_bin") == 0) {
            oct_to_bin(in, actual);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            oct_to_hex(in, actual);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(in, actual);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            long v = strtol(in, NULL, 10);
            to_sign_magnitude((int32_t)v, actual);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            long v = strtol(in, NULL, 10);
            to_ones_complement((int32_t)v, actual);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            long v = strtol(in, NULL, 10);
            to_twos_complement((int32_t)v, actual);
        } else {
            // ignore unknown function
            continue;
        }

        if (strcmp(actual, expected) == 0) {
            printf("Test %d: %s %s -> %s [PASS]\n",
                   test_num, func, in, actual);
        } else {
            printf("Test %d: %s %s -> got %s, expected %s [FAIL]\n",
                   test_num, func, in, actual, expected);
        }
        test_num++;
    }

    fclose(f);
    return 0;
}
