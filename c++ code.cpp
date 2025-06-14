#include <iostream>
#include <fstream>
#include <chrono>
#include <cctype>
#include <string>

using namespace std;
using namespace chrono;
void generateFile(const string& filename, int sizeMB) {
    string line = "this is a line of text for benchmarking purposes.\n";
    long long numLines = (sizeMB * 1024LL * 1024LL) / line.length();
    ofstream file(filename);
    for (long long i = 0; i < numLines; ++i) {
        file << line;
    }
    file.close();
}
double convertToUpper(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    ofstream out(outputFile);
    char ch;
    auto start = high_resolution_clock::now();
    while (in.get(ch)) {
        out.put(toupper(ch));
    }
    auto end = high_resolution_clock::now();
    duration<double> timeTaken = end - start;
    in.close();
    out.close();
    return timeTaken.count();
}

int main() {
    int sizes[] = {200, 400, 600, 800, 1000};
    for (int size : sizes) {
        string input = "input_" + to_string(size) + "MB.txt";
        string output = "output_" + to_string(size) + "MB.txt";
        cout << "\nGenerating " << input << "..." << endl;
        generateFile(input, size);
        cout << "Converting " << input << " to uppercase" << endl;
        double time = convertToUpper(input, output);
        cout << "Size: " << size << "MB | Time: " << time << " sec" << endl;
    }

    return 0;
}
