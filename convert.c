#include <stdint.h>
#include <string.h>
#include <stdio.h>


void div_convert(uint32_t n, int base, char *out){ //algorithm: Repeatedly divide by base, collecting remainders

    char temp [65]; // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Extract digits from right to left
    while (n > 0){
        int remainder = n % base;
        n = n / base;

        // Convert digit to character
        if (remainder < 10)
            temp [pos++] = '0' + remainder;
        else
            temp [pos++] = 'A' + (remainder - 10);
    }

    //reverse temp into out
    for(int i = 0; i < pos; i++)
        out[i] = temp[pos - 1 - i];

    out[pos] = '\0';

    //printf("%s\n", out);
}


void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];   // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    //Find the biggest power of base <= n without overflow
    uint32_t power = 1;
    while (power <= n / (uint32_t)base) {
        power *= (uint32_t)base;
    }

    // Extract digits left to right
    while (power > 0) {
        int digit = 0;

        // Subtract power until n is smaller
        while (n >= power) {
            n -= power;
            digit++;
        }

        // Convert digit to character
        if (digit < 10)
            temp[pos++] = '0' + digit;
        else
            temp[pos++] = 'A' + (digit - 10);

        power /= base;
    }

    // Null terminate
    temp[pos] = '\0';

    // Copy to out
    strcpy(out, temp);

    //printf("%s\n", out);
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    // Original number
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, n, hex);

    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, masked, hex);
}

void oct_to_bin(const char *oct, char *out) {
    static const char *tbl[8] = {"000","001","010","011","100","101","110","111"};
    int pos = 0;
    for (const char *p = oct; *p; p++) {
        if (*p < '0' || *p > '7') continue;
        const char *m = tbl[*p - '0'];
        out[pos++] = m[0];
        out[pos++] = m[1];
        out[pos++] = m[2];
    }
    if (pos == 0) { out[0] = '0'; out[1] = '0'; out[2] = '0'; out[3] = '\0'; }
    else out[pos] = '\0';
}

void hex_to_bin(const char *hex, char *out) {
    int pos = 0;
    for (const char *p = hex; *p; p++) {
        char c = *p;
        int v = (c >= '0' && c <= '9') ? (c - '0') :
                (c >= 'A' && c <= 'F') ? (10 + c - 'A') :
                (c >= 'a' && c <= 'f') ? (10 + c - 'a') : -1;
        if (v < 0) continue;
        out[pos++] = (v & 8) ? '1' : '0';
        out[pos++] = (v & 4) ? '1' : '0';
        out[pos++] = (v & 2) ? '1' : '0';
        out[pos++] = (v & 1) ? '1' : '0';
    }
    if (pos == 0) { out[0] = '0'; out[1] = '0'; out[2] = '0'; out[3] = '0'; out[4] = '\0'; }
    else out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out) {
    //  Build binary 3 bit mapping no leading zeros
    char bin[256];  // big temp buffer
    oct_to_bin(oct, bin);

    // left pad to multiple of 4
    int len = (int)strlen(bin);
    if (len == 1 && bin[0] == '0') { out[0] = '0'; out[1] = '\0'; return; }

    int rem = len % 4;
    int pad = (rem == 0) ? 0 : (4 - rem);

    char padded[260];
    int p = 0;
    for (int i = 0; i < pad; i++) padded[p++] = '0';
    for (int i = 0; i < len;  i++) padded[p++] = bin[i];
    padded[p] = '\0';

    // 3) Convert each 4-bit group to hex
    int pos = 0;
    for (int i = 0; padded[i]; i += 4) {
        int v = (padded[i]   - '0') << 3
              | (padded[i+1] - '0') << 2
              | (padded[i+2] - '0') << 1
              | (padded[i+3] - '0');
        out[pos++] = (v < 10) ? ('0' + v) : ('A' + (v - 10));
    }
    out[pos] = '\0';
}


void to_sign_magnitude(int32_t n, char *out) {
    uint32_t mag;
    int sign = (n < 0);

    if (!sign) {
        mag = (uint32_t)n & 0x7FFFFFFFu;
    } else {
        // magnitude of |n| limited to 31 bits
        uint32_t absn = (uint32_t)(-(int64_t)n); // safe abs
        mag = absn & 0x7FFFFFFFu;
    }

    // write sign bit
    out[0] = sign ? '1' : '0';

    // Write 31 magnitude bits
    for (int i = 30; i >= 0; i--) {
        out[31 - i] = ((mag >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_ones_complement(int32_t n, char *out) {
    uint32_t bits;

    if (n >= 0) {
        bits = (uint32_t)n;
    } else {
        uint32_t pos = (uint32_t)(-(int64_t)n); // |n|
        bits = ~pos; // flip all bits
    }

    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((bits >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_twos_complement(int32_t n, char *out) {
    uint32_t bits = (uint32_t)n; // twos complement is native C int layout
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((bits >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}