# CS 3503 Assignment 2 

## Author
Noah Vincent

## Description
My implementation of Owl Tech’s number base conversion utility.

## Build Instructions
```bash
gcc -o convert convert.c main.c
./convert
```

## Test Results
[58/60 tests passed]
```bash
Test 1: oct_to_bin 725 -> 111010101 [PASS]
Test 2: oct_to_bin 345 -> 011100101 [PASS]
Test 3: oct_to_bin 777 -> 111111111 [PASS]
Test 4: oct_to_bin 0 -> 000 [PASS]
Test 5: oct_to_bin 1 -> 001 [PASS]
Test 6: oct_to_bin 7 -> 111 [PASS]
Test 7: oct_to_bin 10 -> 001000 [PASS]
Test 8: oct_to_bin 100 -> 001000000 [PASS]
Test 9: oct_to_bin 377 -> 011111111 [PASS]
Test 10: oct_to_hex 345 -> got 0E5, expected E5 [FAIL]
Test 11: oct_to_hex 777 -> 1FF [PASS]
Test 12: oct_to_hex 100 -> got 040, expected 40 [FAIL]
Test 13: oct_to_hex 0 -> 0 [PASS]
Test 14: oct_to_hex 1 -> 1 [PASS]
Test 15: oct_to_hex 7 -> 7 [PASS]
Test 16: oct_to_hex 1234 -> 29C [PASS]
Test 17: oct_to_hex 7654 -> FAC [PASS]
Test 18: hex_to_bin A3 -> 10100011 [PASS]
Test 19: hex_to_bin FF -> 11111111 [PASS]
Test 20: hex_to_bin 1A -> 00011010 [PASS]
Test 21: hex_to_bin a3 -> 10100011 [PASS]
Test 22: hex_to_bin Ff -> 11111111 [PASS]
Test 23: hex_to_bin aC -> 10101100 [PASS]
Test 24: hex_to_bin 0 -> 0000 [PASS]
Test 25: hex_to_bin 1 -> 0001 [PASS]
Test 26: hex_to_bin F -> 1111 [PASS]
Test 27: hex_to_bin CAFE -> 1100101011111110 [PASS]
Test 28: hex_to_bin 1234 -> 0001001000110100 [PASS]
Test 29: to_sign_magnitude 5 -> 00000000000000000000000000000101 [PASS]
Test 30: to_sign_magnitude 1 -> 00000000000000000000000000000001 [PASS]
Test 31: to_sign_magnitude 255 -> 00000000000000000000000011111111 [PASS]
Test 32: to_sign_magnitude -5 -> 10000000000000000000000000000101 [PASS]
Test 33: to_sign_magnitude -1 -> 10000000000000000000000000000001 [PASS]
Test 34: to_sign_magnitude -255 -> 10000000000000000000000011111111 [PASS]
Test 35: to_sign_magnitude 0 -> 00000000000000000000000000000000 [PASS]
Test 36: to_ones_complement 5 -> 00000000000000000000000000000101 [PASS]
Test 37: to_ones_complement 1 -> 00000000000000000000000000000001 [PASS]
Test 38: to_ones_complement 255 -> 00000000000000000000000011111111 [PASS]
Test 39: to_ones_complement -5 -> 11111111111111111111111111111010 [PASS]
Test 40: to_ones_complement -1 -> 11111111111111111111111111111110 [PASS]
Test 41: to_ones_complement -255 -> 11111111111111111111111100000000 [PASS]
Test 42: to_ones_complement 0 -> 00000000000000000000000000000000 [PASS]
Test 43: to_twos_complement 5 -> 00000000000000000000000000000101 [PASS]
Test 44: to_twos_complement 1 -> 00000000000000000000000000000001 [PASS]
Test 45: to_twos_complement 255 -> 00000000000000000000000011111111 [PASS]
Test 46: to_twos_complement -5 -> 11111111111111111111111111111011 [PASS]
Test 47: to_twos_complement -1 -> 11111111111111111111111111111111 [PASS]
Test 48: to_twos_complement -255 -> 11111111111111111111111100000001 [PASS]
Test 49: to_twos_complement 0 -> 00000000000000000000000000000000 [PASS]
Test 50: to_twos_complement 2147483647 -> 01111111111111111111111111111111 [PASS]
Test 51: to_twos_complement -2147483648 -> 10000000000000000000000000000000 [PASS]

Process finished with exit code 0
```

## Notes
Had some issues with leading 0's at the beginning.
Bases supported in converters: **2–36** (A–Z for digits ≥ 10)
Buffers are sized conservatively.
