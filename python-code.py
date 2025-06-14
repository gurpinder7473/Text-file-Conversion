import time
import os

def generate_file(filename, size):
    l = "this is a line of text for benchmarking purposes.\n"
    cnt = (size * 1024 * 1024) // len(l)
    with open(filename, "w") as f:
        for _ in range(cnt):
            f.write(l)

def convert_to_uppercase(input_file, output_file):
    start = time.time()
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        for line in infile:
            outfile.write(line.upper())
    end = time.time()
    return round(end - start, 2)

sizes = [200, 400, 600, 800, 1000]

times=[]
for size in sizes:
    fname = f"input_{size}MB.txt"
    print(f"\nGenerating {fname}...")
    generate_file(fname, size)
    print(f"Converting {fname} to uppercase...")
    t = convert_to_uppercase(fname, f"output_{size}MB.txt")
    print(f"Size: {size}MB | Time: {t} sec")
    times.append(t)
print(times)
