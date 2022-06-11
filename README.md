# Image2PrimeASCII

This is a project to convert an image into a ASCII art representation using only digits. The goal being to create a version of that digit representation that is also prime.

The prime representation is embedded into an black and white image.

This project uses OpenCV for image processes and GMP for multiple-precision arithmetic.

## Usage
Once compiled usage is very simple:
```
./im2prime [imagename.png] [number of digits]
```
Number of digits is *not* required. If not specified (or specified as 0) the output image will aim to be the same resolution of the input image. Each number is embedded into 3x5 pixels, with a 1 pixel padding around the outside (effectively 5x7 pixels per digit). The program will try it's best to stick to the number of digits with the same aspect ratio of the input image.

## Primality testing

This program uses Rabin-Miller primality testing, so the generated prime is **not** guaranteed to be prime. However, by performing sufficient tests we can reduce the probability of errors down to a sufficient range.

The worst case error for $k$ tests using this method is $4^{-k}$, however for larger numbers we must perform more and more tests before we find a prime (with the expecting gap between primes being $g_n\approx log(p_n)$). With a few assumptions about how often primes occur, we end up with the following probability:

$$ p_0 = \frac{a-1}{4^k+a-1} $$

with $p_0$ being the probability that the selected number is **not** prime, given $a$ is the number of digits where we are looking for primes, and $k$ the number of tests we perform. In this case we have selected $k=15$ which equates to $p_0\approx 5.6\times 10^{-5}$ for a number $60,000$ digits long.


## Limitations
This project is in infancy and may never be finished. The current limiting factor is for increased detail in the image, one needs to increase the size of the number, which int turn makes the program run slower. This project does allow for multithreaded operation but for larger numbers can still take huge amounts of time.

For example - an image which is 1920x1080 will be automatically converted to a number approximately 60,000 digits long. As the program currently stands, I have tried calculating an example prime of this size across 10 threads and have test 53,000 different numbers across 2/3 days. Still no prime has been found.

## TODO

 - Better input parsing. It's quite elementary at this stage and needs to be much better. Does not check whether the inputs make sense or not.
 - Skip input. This will be useful if for whatever reason you need to stop processing on a particularly large number and resume state.
 - Text output of number. This feels pretty important I just haven't had the time to add it yet.
 - GPU implementation. I know there are CUDA implementations of MPA systems (e.g. CUMP) however I hate the idea of supporting hardware limited programs. I plan to build what I can in OpenCL but this may be a long time coming.


