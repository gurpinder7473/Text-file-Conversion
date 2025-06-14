generate_file <- function(filename, size_mb) {
  line <- "this is a line of text for benchmarking purposes.\n"
  count <- floor((size_mb * 1024 * 1024) / nchar(line))
  con <- file(filename, "w")
  for (i in 1:count) writeLines(line, con, sep = "")
  close(con)
}

convert_uppercase <- function(infile, outfile) {
  start <- Sys.time()
  lines <- readLines(infile, warn = FALSE)
  writeLines(toupper(lines), outfile)
  end <- Sys.time()
  round(as.numeric(difftime(end, start, units = "secs")), 2)
}

sizes <- c(200, 400, 600, 800, 1000)
for (size in sizes) {
  in_file <- sprintf("input_%dMB.txt", size)
  out_file <- sprintf("output_%dMB.txt", size)
  cat(sprintf("\nGenerating %s...\n", in_file))
  generate_file(in_file, size)
  cat(sprintf("Converting %s to uppercase...\n", in_file))
  time_taken <- convert_uppercase(in_file, out_file)
  cat(sprintf("Size: %dMB | Time: %.2f sec\n", size, time_taken))
}
