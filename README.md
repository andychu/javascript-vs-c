An Exercise to Learn C
======================

As a performance experiment, I ported a small piece of JavaScript to C.  I
tried to do it as fast as possible, like this:

1. Dumb Textual Substitution
2. Fix compile errors.
3. Debug runtime errors (with printf and GDB)

After doing this, I conjectured that it's a good exercise for people who
want to learn C.  It's a complement to the "textbook way" of writing programs
from scratch.

I'm giving a 5-minute presentation at the [Recurse
Center](https://www.recurse.com/) on this topic.

### Prerequisites

You should know some of the basic concepts of C, like what an `int` and a
`double` is.  Knowing where `char*` is used would be useful.

I'm advocating somewhat mindless hacking as a shortcut to learning, but it
shouldn't be random hacking. :-)

### Try It

Try the two programs, and verify they do the same thing.

1. Open up mandelbrot.html in your browser.
2. `./run.sh c` to run the C version.  Then open `out.ppm`. (The OS X Finder
   only shows a thumbnail, but Ubuntu can view it by default.)

### Overview of the Source

    $ ./run.sh count
    $ ./run.sh compare

### How I Ported It

1. Downloaded https://rosettacode.org/wiki/Mandelbrot_set#JavaScript 
2. Wrote mandelbrot.html to test mandelbrot.js
3. Separated the *scaffolding* from the computation.  That is, I factored out
   a `main()` function to separate the browser-specific JS stuff (`canvas`)
   from the computation.  Only the computation can be ported to C.
4. `cp mandelbrot.js mandelbrot.c`.
5. Commented the whole thing out and then add a "hello world" `main()`
   function in C.  Make sure it compiles and runs.
6. Uncomment one function at a time.  Added types until it compiles.
   - Example: Figure out what is a floating point number (`double`) and what
     is an integer (`int`).  Declare an array of bytes (`char[]`).
7. Write new scaffolding to save the array of bytes to as a "PPM" file, which
   I learned about from
   https://rosettacode.org/wiki/Mandelbrot_set#PPM_non_interactive .  (NOTE:
   This C code doesn't do the same thing as the JavaScript, so it wasn't good
   for my benchmark.)
8. Localize errors with GDB.  Debug with `printf()`.

#### Time Spent

- Friday: 60-90 minutes downloading Python, JS, and C versions.  Playing
  around with them and comparing what they did.  Figuring out what I wanted to
  do for the performance benchmark.
- Monday: 60-90 minutes discussing it with Aurora, porting it, and debugging
  the two major bugs (segfault and "missing" type error).

### Lessons / Advice

- Treat C like Python or Ruby by writing a tiny shell script.  `[demo]`
  - Don't worry about build systems for now.

- Learn how to read error messages (compiler errors and warnings).

- Learn how to obtain better error messages (stack traces)
  - With GDB and/or ASAN

### Exercises

1. Do the same thing with a different piece of code!  Find another small piece
   of JavaScript code on the Internet, and follow the steps above.
   
   Good candidates for code to port:

   1. Are short.  Start with something 20-50 lines, and then work your way up
      to bigger pieces of code.
   1. Don't use too many libraries.  Writing an image into an array is ideal.
   1. Use numbers, not strings.  (Strings in C are very different than strings
      in JavaScript.)

2. Do performance experiments.  Make a prediction about the speed before
   running it.
   - Try running it in a VM.
   - Demonstrate a case where transliterating JavaScript is 10x or 100x slower
     than C.

3. Do the reverse direction: port C to JavaScript by removing types.  This
   should be easier than JavaScript -> C ?

### Example Bugs

#### Bug #1: Segfault

`[live demo]` with GDB and ASAN.

- Need to pass `-g` flag to get symbols

#### Bug #2: The Screen is Black

`[live quiz]` with bug2.c.

#### Other Issues

- On Linux, I had to pass `-l m` on the command line to fix a link error link
  the math library.  And it has to come *after* `mandelbrot.c` on the command
  line (order matters).
- `man fwrite` may be useful.

### Follow-Up

1. If it works, and you have code that now works in JavaScript and in C, send
   me a link or a pull request to this repo.
   
   It would also be interesting to know how long the port took.

2. If this learning-by-porting strategy doesn't work for you, also let me know
   (on Zulip or in person.)

### Caveats

- Performance: This is the best case for JavaScript.  JavaScript can be many
  times slower than C if the JIT can't do its work.

- You have to find something small enough.  If you get stuck porting a piece
  of code, find something even smaller.

### For Advanced Readers

- Types: hardware view vs. the mathematical view (contrast with Haskell or
  Rust).
  - C used to be a dynamic language! Show untyped C.
  - In C, types are only for instruction selection.  Nothing more.
  - C++ is different than C.

- [Hello, JIT
  World](http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html)
  -- The mechanism that allows modern JavaScript engines to be comparable in
  speed to C (for some problems).

