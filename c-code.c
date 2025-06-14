#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void generate_file(const char* filename, int size_mb) {
    const char* line = "this is a line of text for benchmarking purposes.\n";
    long long count = (long long)(size_mb * 1024 * 1024) / strlen(line);
    FILE* f = fopen(filename, "w");
    for (long long i = 0; i < count; i++) {
        fputs(line, f);
    }
    fclose(f);
}

double convert_uppercase(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    FILE* out = fopen(output_file, "w");
    if (!in || !out) return -1;
    clock_t start = clock();
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        fputc(toupper(ch), out);
    }
    clock_t end = clock();
    fclose(in);
    fclose(out);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int sizes[] = {200, 400, 600, 800, 1000};
    for (int i = 0; i < 5; i++) {
        char in_file[30], out_file[30];
        sprintf(in_file, "input_%dMB.txt", sizes[i]);
        sprintf(out_file, "output_%dMB.txt", sizes[i]);
        printf("Generating %s...\n", in_file);
        generate_file(in_file, sizes[i]);
        printf("Converting %s to uppercase...\n", in_file);
        double time_taken = convert_uppercase(in_file, out_file);
        printf("Size: %dMB | Time: %.2f sec\n", sizes[i], time_taken);
    }
    return 0;
}
