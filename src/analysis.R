
## this is gibberish right now
getwd()
setwd(
  "~/Documents/class/bio478/thomFinal/test/"
)

  A <- read.csv("samplereads.fa.csv", header = FALSE)
  B <- read.csv("sampleRef.fa.csv", header = FALSE)

ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = A$V2), fill = "#f000a0", color = "#2f2f2f",alpha = 0.5, binwidth = 1000)
  ggplot2::geom_histogram(ggplot2::aes(x = B$V2), fill = "#a0f0d0", binwidth = 1000)


ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = B$V2), fill = "#a0f0d0", color = "black", binwidth = 10)





A <- read.csv("hmeph_T_S-contig.csv", header = FALSE)
B <- read.csv("hmephReads.csv", header = FALSE)


ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = B$V2), binwidth = 10000, fill = "#f000a0") +
  ggplot2::geom_histogram(ggplot2::aes(x = A$V2), binwidth = 10000, fill = "#f0f000") +
  ggplot2::theme_bw()

ggplot2::ggplot() + ggplot2::geom_density(ggplot2::aes(x = A$V2), fill = "#f0f0a0",alpha = 1, colour = "white") +
  ggplot2::geom_density(ggplot2::aes(x = B$V2), fill = "#f000a0", alpha = 0.4, colour = "white") +
  ggplot2::theme_bw() +
  ggplot2::scale_y_log10()


ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = A$V2), fill = "#f000a0")


library(dplyr)
Bcount <- B %>% 
  group_by(V2) %>% 
  summarise(count = n())

?ggplot2::geom_density

sort(B$V2)


A <- read.csv("hmeph1.csv", header = FALSE) ## FIFTEEN MERS
B <- read.csv("hmeph2.csv", header = FALSE) ## THIRTY MERS

ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = A$V2), alpha = 1, binwidth = 2000, fill = "#f0f0a0") +
  ggplot2::geom_histogram(ggplot2::aes(x = B$V2), alpha = 0.5, binwidth = 2000, fill = "#f000a0") +
  ggplot2::theme_bw()

ggplot2::ggplot() + ggplot2::geom_density(ggplot2::aes(x = B$V2), fill = "#f0f0a0",alpha = 10, colour = "white") +
  ggplot2::geom_density(ggplot2::aes(x = A$V2), fill = "#f000a0", colour = "white") +
  ggplot2::theme_bw()


ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = A$V2), binwidth = 500, fill = "#f000a0") +
  ggplot2::theme_bw()




Aold <- read.csv("testOrg.thom", header = FALSE)
Anew <- read.csv("testOrg.thom", header = FALSE)

Atrash <- read.csv("testOrg.thom", header = FALSE)


ggplot2::ggplot() + ggplot2::geom_density(ggplot2::aes(x = Aold$V2), fill = "#f000a0", colour = "white") +
  ggplot2::theme_bw()


ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = Aold$V2), binwidth = 900, fill = "#f000a0") +
  ggplot2::theme_bw()

ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = Anew$V2), binwidth = 900, fill = "#f0f0a0") +
  ggplot2::theme_bw()

ggplot2::ggplot() + ggplot2::geom_histogram(ggplot2::aes(x = Atrash$V2), alpha = 0.5, binwidth = 900, fill = "#f0f0a0") +
  ggplot2::geom_histogram(ggplot2::aes(x = Aold$V2)) +
  ggplot2::theme_bw()
## I prefer the histogram here instead of the density plot


B <- seq.int(1, 2832)
length(A$V1)

ggplot2::ggplot() + ggplot2::geom_point(ggplot2::aes(x = B, y = A$V1)) +
  ggplot2::theme_bw()
