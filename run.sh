#!/bin/bash
#
# Usage:
#   ./run.sh <function name>

set -o nounset
set -o pipefail
set -o errexit

compile() {
  # Started with:
  # cc -o mandelbrot mandelbrot.c

  cc -g -Wall -o mandelbrot mandelbrot.c -l m "$@"
  ls -l mandelbrot
}

c() {
  compile

  echo 'Rendering fractal...'
  time ./mandelbrot
  ls -l out.ppm
}

# r to run
# q to exit
debug() {
  compile
  gdb --args ./mandelbrot
}

with-asan() {
  echo 'Compiling with ASAN instrumentation'
  compile -fsanitize=address

  echo 'Rendering fractal...'
  time ./mandelbrot
  ls -l out.ppm
}

count() {
  wc -l *.js *.c
}

download-icdiff() {
  wget --no-clobber https://raw.githubusercontent.com/jeffkaufman/icdiff/release-1.9.1/icdiff
  chmod +x icdiff
}

compare() {
  #cdiff mandelbrot.js mandelbrot.c
  if test -f ./icdiff; then
    ./icdiff --whole-file mandelbrot.js mandelbrot.c
  else
    diff -y mandelbrot.js mandelbrot.c
  fi
}

bug2() {
  cc -o bug2 bug2.c
  ./bug2
}

bug3() {
  cc -o bug3 bug3.c
  ./bug3
}

"$@"
