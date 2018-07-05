An Exercise to Learn C
======================

As a performance experiment, I ported a small piece of JavaScript to C.  I
tried to do it as fast as possible, like this:

1. Dumb textual substitution.
2. Fix compile errors.
3. Debug runtime errors (with `printf()` and [GDB][]).

After doing this, I conjectured that it's a good exercise for people who
want to learn C.  It's a complement to the "textbook way" of writing programs
from scratch.

I'm giving a 5-minute presentation at the [Recurse
Center](https://www.recurse.com/) on this topic.

## Prerequisites

You should know some of the basic concepts of C, like what an `int` and a
`double` is.  Knowing where `char*` is used would be useful.

I'm advocating *somewhat mindless* hacking as a shortcut to learning, but it
shouldn't be *random* hacking. :-)

## Try It

Verify that the two programs do the same thing:

1. Open up `mandelbrot.html` in your browser.
2. In your shell, type `./run.sh c` to run the C version.  Then open
   `out.ppm`. (The OS X Finder only shows a thumbnail, but Ubuntu can view it
   by default.)

## Overview of the Source

    $ ./run.sh count
    $ ./run.sh compare

## How I Ported It

1. Downloaded https://rosettacode.org/wiki/Mandelbrot_set#JavaScript 
2. Added `mandelbrot.html` for `mandelbrot.js` to render to.
3. In JavaScript, Separated the **scaffolding** from the **computation**.
   That is, I factored out a `main()` function that was independent from
   browser-specific stuff like `canvas`.  Only the computation can be ported
   to C.
4. `cp mandelbrot.js mandelbrot.c`.
5. Commented all the JavaScript out, then added a "hello world" `main()`
   function in C.  Make sure it compiles and runs.
6. Uncommented one function at a time.  Added types until it compiles.
   - Figure out which vars are floating point numbers (`double`) and which
     vars are integers (`int`).  Declare an array of bytes (`char[]`).
7. Write new scaffolding in C.  It saves the array of bytes to as a `.ppm`
   file, which I learned about from
   https://rosettacode.org/wiki/Mandelbrot_set#PPM_non_interactive .  (NOTE:
   The C and JavaScript should do the same thing in order to produce a
   meaningful benchmark.)
8. Run it.  Localize errors with GDB (particularly the segfault).
9. Debug with `printf()`.

### Time Spent

- Friday: 60-90 minutes downloading Python, JS, and C versions.  Playing
  around with them and comparing what they did.  Figuring out what I wanted to
  do for the performance benchmark.
- Monday: 60-90 minutes discussing it with Aurora, porting it, and debugging
  the two major bugs (segfault and "missing" type error).

## Lessons / Advice

- Treat C like Python or Ruby by writing a tiny shell script.  `[demo]`
  - Don't worry about build systems for now.
- Learn how to read error messages (compiler errors and warnings).
- Learn how to obtain better error messages (stack traces)
  - With [GDB][] and/or [ASAN][].

## Exercises

1. Do the same thing with a different piece of code!  Find another small piece
   of JavaScript code on the Internet, and follow the steps above.
   
   Good candidates for code to port:

   1. Are short.  Start with something 20-50 lines, and then work your way up
      to bigger pieces of code.
   1. Don't use too many libraries.  Writing an image to an array is ideal.
   1. Use numbers, not strings.  (Strings in C are very different than strings
     in JavaScript.)

2. Do performance experiments.  Make a prediction about the speed before
   running it.
   - Try running it in a VM.
   - Demonstrate a case where transliterating JavaScript to C results in code
     that's 10x or 100x slower.

3. Do the reverse direction: port C to JavaScript by removing types.  This
   should be easier than JavaScript -> C ?

If it works, and you have code that now works in JavaScript and in C, send me
a link or a **pull request** to this repo.
   
It would also be interesting to know how long the port took.

If this learning-by-porting strategy doesn't work for you, also let me know
(on Zulip or in person.)

## Example Bugs

### Bug #1: Segfault

`[live demo]` with [GDB][] and [ASAN][].

- Need to pass `-g` flag to get symbols

### Bug #2: The Screen is Black

`[live quiz]` with bug2.c.

### Other Issues

- On Linux, I had to pass `-l m` on the command line to fix a link error link
  the math library.  And it has to come *after* `mandelbrot.c` on the command
  line (order matters).
- `printf()` without the right args gives a compiler warning, but still runs!
  It just produces garbage.
- `man fwrite` may be useful.

## Caveats

- For the exercise: You have to find something small enough.  If you get stuck
  porting a piece of code, find something even smaller.
- Performance: This is the best case for JavaScript.  JavaScript can be many
  times slower than C if the JIT can't do its work.

## For Advanced Readers

- Types: hardware view vs. the mathematical view (contrast with Haskell or
  Rust).
  - C used to be a dynamic language! Show untyped C.
  - In C, types are only for instruction selection.  Nothing more.
  - C++ is different than C.
- [Hello, JIT
  World](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html)
  -- The mechanism that allows modern JavaScript engines to be comparable in
  speed to C (for some problems).

[GDB]: https://beej.us/guide/bggdb/

[ASAN]: https://github.com/google/sanitizers/wiki/AddressSanitizer
