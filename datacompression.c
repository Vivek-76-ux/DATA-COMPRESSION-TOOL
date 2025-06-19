#include <stdio.h>
#include <stdlib.h>

// Function to compress the file using Run-Length Encoding
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char currentChar, prevChar;
    int count = 1;

    prevChar = fgetc(in);
    while ((currentChar = fgetc(in)) != EOF) {
        if (currentChar == prevChar) {
            count++;
        } else {
            fprintf(out, "%c%d", prevChar, count);
            count = 1;
        }
        prevChar = currentChar;
    }

    // Write the last sequence
    fprintf(out, "%c%d", prevChar, count);

    fclose(in);
    fclose(out);
    printf("Compression complete. Output saved in '%s'.\n", outputFile);
}

// Function to decompress the RLE-compressed file
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    int count;

    while (fscanf(in, "%c%d", &ch, &count) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression complete. Output saved in '%s'.\n", outputFile);
}

int main() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("=== Data Compression Tool (RLE) ===\n");
    printf("1. Compress File\n");
    printf("2. Decompress File\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    printf("Enter input file name: ");
    scanf("%s", inputFile);
    printf("Enter output file name: ");
    scanf("%s", outputFile);

    if (choice == 1) {
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
