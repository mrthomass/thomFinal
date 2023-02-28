#! /usr/bin/env Rscript

args = commandArgs(trailingOnly = TRUE)

## arguments have the form reads.csv assembly.csv
## error exception here is not very robust
if (length(args) < 2)
{
  stop("File Arguments Required", call. = FALSE)
}

A <- read.csv(args[1], header = FALSE)
B <- read.csv(args[2], header = FALSE)


assemblyPlot <- ggplot2::ggplot() + ggplot2::geom_density(ggplot2::aes(x = B$V2), fill = "#a0f0d0", alpha = 0.3) + ggplot2::theme_minimal() +
  ggplot2::labs(x = "kmer freq freq", title = "Assembly Kmer Frequency Plot")

readsPlot <- ggplot2::ggplot() + ggplot2::geom_density(ggplot2::aes(x = A$V2), fill = "#f000a0", alpha = 0.3) +
  ggplot2::theme_minimal() +   ggplot2::labs(x = "kmer freq freq", title = "Reads Kmer Frequency Plot")

ggplot2::ggsave(filename = paste0(args[2], "_plot.png"), plot = assemblyPlot, width = 6, height = 5)
ggplot2::ggsave(filename = paste0(args[1], "_plot.png"), plot = readsPlot, width = 6, height = 5)

