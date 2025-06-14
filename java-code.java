import java.io.*;
import java.nio.file.*;
import java.util.*;

public class UppercaseBenchmark {
    public static void generateFile(String filename, int sizeMB) throws IOException {
        String line = "this is a line of text for benchmarking purposes.\n";
        long count = (sizeMB * 1024L * 1024L) / line.length();
        BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
        for (long i = 0; i < count; i++) {
            writer.write(line);
        }
        writer.close();
    }

    public static double convertToUppercase(String infile, String outfile) throws IOException {
        long start = System.currentTimeMillis();
        BufferedReader reader = new BufferedReader(new FileReader(infile));
        BufferedWriter writer = new BufferedWriter(new FileWriter(outfile));
        int ch;
        while ((ch = reader.read()) != -1) {
            writer.write(Character.toUpperCase(ch));
        }
        reader.close();
        writer.close();
        long end = System.currentTimeMillis();
        return (end - start) / 1000.0;
    }

    public static void main(String[] args) throws IOException {
        int[] sizes = {200, 400, 600, 800, 1000};
        for (int size : sizes) {
            String inFile = "input_" + size + "MB.txt";
            String outFile = "output_" + size + "MB.txt";
            System.out.println("\nGenerating " + inFile + "...");
            generateFile(inFile, size);
            System.out.println("Converting " + inFile + " to uppercase...");
            double time = convertToUppercase(inFile, outFile);
            System.out.println("Size: " + size + "MB | Time: " + time + " sec");
        }
    }
}
