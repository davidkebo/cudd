# CUDD tutorials

Two small, self-contained programs that build a BDD with CUDD, convert it
to an ADD for display, and write a Graphviz `.dot` file. They are the
same tutorials published at
[davidkebo.com/cudd](https://davidkebo.com/cudd/), now kept as readable
source instead of a prebuilt tarball.

- `tutorial1.c` builds a single BDD variable.
- `tutorial2.c` builds the conjunction of four complemented BDD variables.

## 1. Build and install CUDD

From the repository root:

```sh
git clone https://github.com/davidkebo/cudd.git
cd cudd

# Git does not preserve file timestamps, so the autotools-generated
# files look older than their sources after a clone, and make tries
# to regenerate them with the exact autoconf/automake versions used
# in 2015. Touching them in dependency order avoids that.
touch aclocal.m4 configure Makefile.in config.h.in

./configure --prefix="$HOME/cudd-install"
make
make check
make install
```

## 2. Build and run the tutorials

```sh
cd tutorials
make CUDD="$HOME/cudd-install" run
```

This builds `tutorial1` and `tutorial2` and runs both. Each program
creates `bdd/` if it does not exist and writes its own file there:
`bdd/tutorial1.dot` and `bdd/tutorial2.dot`.

## 3. Render the output

```sh
dot -Tpng bdd/tutorial1.dot -o tutorial1.png
dot -Tpng bdd/tutorial2.dot -o tutorial2.png
```

`dot` is part of [Graphviz](https://www.graphviz.org/download/).

## Changes from the 2016 version

The 2016 tutorial archives (`tutorial1.tar.gz`, `tutorial2.tar.gz`, still
available from the
[`tutorials-2016` release](https://github.com/davidkebo/cudd/releases/tag/tutorials-2016))
bundled a full copy of CUDD 2.4.1, including 111 compiled `.o` files and
x86-64 executables. The sources here are ported to build against CUDD
3.0.0 instead, with the minimum change needed to do that cleanly:

- Added `SPDX-License-Identifier: BSD-3-Clause` and a copyright line.
- Added `#include <sys/stat.h>` and `#include <errno.h>`, and create
  `bdd/` with `mkdir` if it is missing, instead of assuming it exists.
- Split the single reused `bdd` variable into a `bdd` (BDD) and `add`
  (ADD) pointer, with an explicit `Cudd_Ref`/`Cudd_RecursiveDeref` for
  each, and added a `Cudd_CheckZeroRef` check before `Cudd_Quit`.
  The 2016 version reassigned `bdd` to the result of `Cudd_BddToAdd`
  without ever releasing the original BDD reference.
- Added `(void)argc; (void)argv;` so the unused `main` parameters do
  not warn under `-Wall -Wextra`.
- Output files are named `bdd/tutorial1.dot` and `bdd/tutorial2.dot`
  (the 2016 version wrote both to `bdd/graph.dot`, so running one
  tutorial after the other silently overwrote the first's output).
- Replaced the old hand-written Makefile (which hardcoded paths into
  a bundled `cudd-2.4.1/` tree) with one that links against an
  installed CUDD via `CUDD ?= /usr/local`.
- Removed the outdated contact email from the old `README.txt`; see
  the root [`SECURITY.md`](../.github/SECURITY.md) and
  [`CONTRIBUTING.md`](../.github/CONTRIBUTING.md) for how to reach
  this repository instead.

The logic, structure and comments of `tutorial.c` are otherwise
unchanged, since davidkebo.com/cudd shows this code directly.

## More

See [davidkebo.com/cudd](https://davidkebo.com/cudd/) for the tutorial
write-up, and the repository [README](../README.md) for the rest of
CUDD's documentation.
