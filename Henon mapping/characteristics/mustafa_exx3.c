#include <stdio.h>
#include <stdint.h>

// The S-Box to be tested
const uint8_t sbox[256] =  { 0xa2, 0x9b, 0x78, 0xa5, 0x62, 0x95, 0x7b, 0x4a, 0x90, 0xa3, 0x18, 0xf8, 0x12, 0x92, 0x70, 0xea, 0x9f, 0xe5, 0x5f, 0x9c, 0xa, 0x8d, 0x79, 0xcb, 0x63, 0xaa, 0xff, 0xf1, 0xec, 0x40, 0x96, 0xbe, 0x89, 0xb5, 0xa7, 0x2e, 0x71, 0x1f, 0x3a, 0xb1, 0xe0, 0x59, 0x2a, 0xa0, 0xcd, 0x53, 0x2c, 0x6a, 0xd5, 0x76, 0x67, 0x4f, 0x4c, 0xe7, 0x28, 0x44, 0xcc, 0x84, 0x94, 0x1b, 0x69, 0xab, 0x7a, 0x73, 0x9e, 0x74, 0xba, 0xb3, 0xb0, 0x5e, 0x82, 0x34, 0xf5, 0x48, 0xc3, 0xaf, 0x50, 0x97, 0x27, 0x7e, 0x1c, 0x6d, 0xac, 0x32, 0x23, 0xed, 0x0, 0xad, 0xc4, 0x83, 0xe, 0xc6, 0x60, 0x6b, 0xb8, 0xe8, 0xdd, 0xa9, 0xde, 0xfc, 0x5, 0x37, 0xe6, 0xd, 0xc2, 0xb6, 0xdb, 0x85, 0xc, 0x2b, 0x9, 0x21, 0x5d, 0xd6, 0x19, 0x13, 0x31, 0x6, 0x43, 0xef, 0xd4, 0x7d, 0xc5, 0x8f, 0xc8, 0x41, 0xf9, 0x5a, 0x81, 0x8c, 0xee, 0xe2, 0xbc, 0x14, 0x56, 0xe9, 0x75, 0x4e, 0x3, 0x10, 0xfa, 0xc0, 0x17, 0x80, 0xdc, 0x11, 0xbf, 0x42, 0xd9, 0x6e, 0x4d, 0xfe, 0x6f, 0xf2, 0x8e, 0x47, 0x4, 0x4b, 0xb4, 0x39, 0x77, 0xdf, 0xf0, 0x65, 0x24, 0xb9, 0x98, 0x72, 0xd7, 0xe4, 0x87, 0xa8, 0x7, 0x57, 0x9a, 0x3d, 0xe1, 0x5b, 0x30, 0x35, 0xf, 0xf3, 0xb2, 0xbb, 0xfb, 0x9d, 0x26, 0x5c, 0x38, 0x25, 0x88, 0xce, 0x3c, 0x86, 0x58, 0x2f, 0x8a, 0xd2, 0x46, 0x51, 0xca, 0xeb, 0x7c, 0x49, 0xb, 0x2d, 0xf6, 0xa1, 0x55, 0x91, 0xd3, 0xb7, 0x2, 0xda, 0x16, 0xfd, 0xbd, 0x29, 0x66, 0x64, 0x99, 0x45, 0x15, 0x3f, 0x52, 0x33, 0x3b, 0xf4, 0x93, 0x1e, 0xcf, 0xa6, 0x68, 0x1d, 0xd0, 0xd1, 0x54, 0xe3, 0x8b, 0xa4, 0x61, 0xc1, 0x6c, 0x36, 0x7f, 0xf7, 0xd8, 0x8, 0x20, 0xae, 0x3e, 0xc9, 0x1a, 0x22, 0xc7, 0x1};

int main()
{
    int delta_u, delta_v, x, y, z;
    int max_differential = 0;
    int nonlinearity = 0; // Nonlinearity
    int min_abs_diff = 256;
    int differential_uniformity = 0; // Differential Uniformity
    int bijectivity = 1; // Bijectivity
    int sac = 0; // Strict Avalanche Criterion
    int bic = 0; // Bit Independence Criterion
    int n = 256;

    // Differential Probability Table
    int ddt[256][256] = {0};

    // Iterate over all possible input differences
    for (delta_u = 1; delta_u < 256; delta_u++) {

        // Iterate over all possible input values
        for (x = 0; x < 256; x++) {

            // Calculate output difference
            delta_v = sbox[x] ^ sbox[x ^ delta_u];

            // Increment probability count in DDT
            ddt[delta_u][delta_v]++;
        }
    }

    // Find the maximum differential probability
    for (delta_u = 1; delta_u < 256; delta_u++) {
        for (delta_v = 1; delta_v < 256; delta_v++) {
            if (ddt[delta_u][delta_v] > max_differential) {
                max_differential = ddt[delta_u][delta_v];
                sac++; // Increment SAC
            }
            if (ddt[delta_u][delta_v] < min_abs_diff) {
                min_abs_diff = ddt[delta_u][delta_v];
            }
            if (ddt[delta_u][delta_v] == 0) {
                bijectivity = 0; // Not bijective
            }
        }
    }

    // Calculate Nonlinearity
    nonlinearity = 128 - (max_differential / 2);

    // Calculate Differential Uniformity
    differential_uniformity = (n - min_abs_diff) / 2;

    // Calculate BIC
    bic = 256 - max_differential;

    // Print the results
    printf("Nonlinearity: %d\n", nonlinearity);
    printf("Differential Uniformity: %d\n", differential_uniformity);
    printf("Bijectivity: %s\n", (bijectivity == 1) ? "Yes" : "No");
    printf("SAC: %d\n", sac);
    printf("BIC: %d\n", bic);
    printf("Differential Probability: %f\n", (float)max_differential / n);

    return 0;
}
