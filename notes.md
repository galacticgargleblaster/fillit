
We're interested in what other folks have done before
to checkout prior art submodules:
`git submodule init`
`git submodule update`

Everyone we've found so far uses a *very similar* implementation of recursive backtracking.
### Stack size
The maximum stack size is limited to the number of tetrominoes being placed -- 26.

Why choose Knuth's DLX?  It doesn't seem to differ from recursive backtracking in time complexity.  It's elegant, but a little verbose and hard to understand without reading Knuth's paper first.

https://github.com/nmei-42/42-fillit
https://arxiv.org/pdf/cs/0011047.pdf

# Let's try solving iteratively with a queue
This is an embarrassingly parallelizable problem.  Although we're prohibited from multithreading in this assignment, I chose to practice writing in iterative rather than recursive form.

## Tetromino Validity Check
[1](#alexisadorn)checks each `#` for fewer than six neighbors, and asserts that the total number of `#` is 4.

./prior_art/alexisadorn/srcs/check_if_valid.c

all prior art <sup>[2](#pbondoer)</sup> seems to function similarly here.

## Tetromino data representation

Shrinking the problem space by one dimension per tetromino, rotated tetrominoes are considered unique.

## Q: Is this an Exact Cover problem?

### A: Yes, it can be represented as one

https://en.wikipedia.org/wiki/Exact_cover
http://garethrees.org/2007/06/10/zendoku-generation/#section-4
https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/sudoku.paper.html


<a name="alexisadorn">1</a>: https://github.com/alexisadorn/42-fillit
<a name="pbondoer">2</a>: https://github.com/pbondoer/42-fillit
