# CUDD

CUDD is the reference C library for binary decision diagrams (BDDs),
algebraic decision diagrams (ADDs) and zero-suppressed binary decision
diagrams (ZDDs), written by Fabio Somenzi at the University of
Colorado at Boulder.

[![build](https://github.com/davidkebo/cudd/actions/workflows/build.yml/badge.svg)](https://github.com/davidkebo/cudd/actions/workflows/build.yml)
[![docs](https://github.com/davidkebo/cudd/actions/workflows/docs.yml/badge.svg)](https://github.com/davidkebo/cudd/actions/workflows/docs.yml)
[![License: BSD-3-Clause](https://img.shields.io/badge/license-BSD--3--Clause-blue)](LICENSE)
[![Latest release](https://img.shields.io/github/v/release/davidkebo/cudd)](https://github.com/davidkebo/cudd/releases/latest)

## What CUDD is

CUDD manipulates BDDs, ADDs and ZDDs. Since the mid-1990s it has been
the reference BDD package used in hardware verification and logic
synthesis, and it sits inside model checkers (NuSMV, nuXmv, VIS),
synthesis tools (ABC, OpenROAD), probabilistic model checkers (PRISM),
and many research tools. The package bundles:

- `cudd/` — BDDs, ADDs and ZDDs;
- `dddmp/` — a library to save and load decision diagrams to and from disk;
- `cplusplus/` — a C++ wrapper around the C API;
- `nanotrav/` — a demonstration program that reads a network and builds BDDs for it;
- `epd/`, `mtr/`, `st/`, `util/` — supporting libraries (extended double precision, variable groups, hashing, and general utilities).

## About this repository

CUDD's last release was 3.0.0, in 2015. Its original distribution
site (vlsi.colorado.edu/~fabio) and documentation are no longer
reachable.

This repository holds Somenzi's releases unmodified: each version
(2.4.2, 2.5.0, 2.5.1, 3.0.0) is one tagged commit, so `git diff
v2.5.1 v3.0.0` shows exactly what changed upstream. It is maintained
by David Kebo Houngninou. **It is not an official upstream**, and no
patch is applied to CUDD's source — the `pristine` CI job checks every
push against the `v3.0.0` tag to enforce that.

Somenzi's own README is the file [`README.upstream`](README.upstream)
at the repository root, kept under that name so GitHub only renders
this file as the repository's README.

## Quick start

```sh
git clone https://github.com/davidkebo/cudd.git
cd cudd

# Git does not preserve file timestamps. Without this, make tries to
# regenerate configure/Makefile.in with the exact autoconf/automake
# versions used to cut the 2015 release, and fails.
touch aclocal.m4 configure Makefile.in config.h.in

./configure
make
make check
make install
```

Documented `./configure` options:

| Option | Effect |
|---|---|
| `--enable-dddmp` | Build the dddmp load/store library |
| `--enable-obj` | Build the C++ wrapper (`cplusplus/`) |
| `--enable-shared` | Also build a shared library |
| `--with-system-qsort` | Use the system's `qsort` instead of CUDD's own |

### Supported platforms

As shown by [CI](https://github.com/davidkebo/cudd/actions/workflows/build.yml):

- Linux (GCC and Clang) and macOS (Clang) — required, both the
  default and the `--enable-dddmp --enable-obj --enable-shared`
  configuration.
- Windows (MSYS2 UCRT64) — best effort, not required to pass.
- CUDD 2.4.2, 2.5.0 and 2.5.1 — best effort, built the way each
  version's own README documents.

One note for modern compilers: GCC 14+ and recent Clang reject
"implicit int" by default, which breaks one of CUDD 3.0.0's own
`configure`-time feature tests (for IEEE 754 infinity) and, with it,
one regression test. CI and the commands above work around this with
`CFLAGS=-Wno-implicit-int`; this is a build flag, not a source change.

## Documentation

The CUDD user manual and API reference, rebuilt from this source and
published on GitHub Pages:

- [Documentation site](https://davidkebo.github.io/cudd/)
- [User manual (PDF)](https://davidkebo.github.io/cudd/cudd.pdf)
- [API reference (Doxygen)](https://davidkebo.github.io/cudd/api/)

## Downloads

| Release | Archive | Size | SHA-256 |
|---|---|---|---|
| 3.0.0 | [cudd-3.0.0.tar.gz](https://github.com/davidkebo/cudd/releases/download/v3.0.0/cudd-3.0.0.tar.gz) | 1,175,302 bytes | `b8e966b4562c96a03e7fbea239729587d7b395d53cadcc39a7203b49cf7eeb69` |
| 2.5.1 | [cudd-2.5.1.tar.gz](https://github.com/davidkebo/cudd/releases/download/v2.5.1/cudd-2.5.1.tar.gz) | 1,122,736 bytes | `4b19c34328d8738a839b994c6b9395f3895ff981d2f3495ce62e7ba576ead88b` |
| 2.5.0 | [cudd-2.5.0.tar.gz](https://github.com/davidkebo/cudd/releases/download/v2.5.0/cudd-2.5.0.tar.gz) | 1,053,054 bytes | `4f3bc49b35564af94b17135d8cb8c4063fb049cfaa442f80dc40ba73c6345a85` |
| 2.4.2 | [cudd-2.4.2.tar.gz](https://github.com/davidkebo/cudd/releases/download/v2.4.2/cudd-2.4.2.tar.gz) | 1,121,873 bytes | `9dd7c9926258e2557bbd61328d0e685b7ac508af300cc54175b5dec8138a7175` |

The 2016 tutorial tarballs (superseded by [`tutorials/`](tutorials/))
are kept on the [2016 tutorials release](https://github.com/davidkebo/cudd/releases/tag/legacy-tarballs) (tag `legacy-tarballs`).

**Verify a download:**

```sh
sha256sum cudd-3.0.0.tar.gz
# compare against the table above, or the release's SHA256SUMS file

gh release verify-asset v3.0.0 cudd-3.0.0.tar.gz
# checks the GitHub release attestation
```

GitHub's automatic "Source code (zip/tar.gz)" links on each release
page are **not** these archives — they are a snapshot of the git tree
at that tag, with different layout and metadata. Use the archive link
in the table, or the matching asset on the release page, to get the
exact file Somenzi released.

## Release history

Tags `v2.4.2`, `v2.5.0`, `v2.5.1` and `v3.0.0` each point at a pure,
unmodified import of that release. For example:

```sh
git diff v2.5.1 v3.0.0        # see exactly what changed upstream
git diff --stat v2.5.1 v3.0.0 # ...or just the file-level summary
```

2.5.0 and 2.5.1 build with a plain `make` (see each tag's own
`README`); 2.4.2's `Makefile` defaults to a 32-bit-era `XCFLAGS` that
needs the 64-bit alternative already commented into that same
Makefile, e.g. `make XCFLAGS="-mtune=native -DHAVE_IEEE_754 -DBSD
-DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8"`. All three are built this way by
the (best-effort) `legacy` CI job.

`legacy-tarballs` tags the commit at which this repository still held
release tarballs instead of source (see [Downloads](#downloads) and
the [2016 tutorials release](https://github.com/davidkebo/cudd/releases/tag/legacy-tarballs)).

## Tutorials

[`tutorials/`](tutorials/) has two small CUDD programs — one builds a
single BDD variable, the other the conjunction of four complemented
variables — ported to build against CUDD 3.0.0, plus a Makefile and
build instructions. They replace the 2016 tutorial tarballs (full
CUDD 2.4.1 copies with 111 prebuilt `.o` files and x86-64 binaries),
which are still available as a release download if you need them. See
[davidkebo.com/cudd](https://davidkebo.com/cudd/) for the tutorial
write-up.

## Related projects

- [davidkebo/ddcal](https://github.com/davidkebo/ddcal) — DDcal, a BDD calculator built on CUDD
- [cuddorg/cudd](https://github.com/cuddorg/cudd) — a maintained fork with patches and portability fixes
- [ssoelvsten/cudd](https://github.com/ssoelvsten/cudd) — another maintained, patched fork
- [tulip-control/dd](https://github.com/tulip-control/dd) — a pure-Python/Cython BDD library inspired by CUDD

## Packaged by

- [Gentoo](https://packages.gentoo.org/packages/sci-mathematics/cudd) (`sci-mathematics/cudd`)
- [Julia `CUDD_jll`](https://github.com/JuliaBinaryWrappers/CUDD_jll.jl)
- [OpenROAD](https://github.com/The-OpenROAD-Project/cudd)

All three currently fetch `cudd-3.0.0.tar.gz` by URL and check it by
SHA-256; the file is unchanged, and remains available both as a
release asset here and at davidkebo.com's download path.

## Citing CUDD

See [`CITATION.cff`](CITATION.cff). In BibTeX:

```bibtex
@software{somenzi_cudd_2015,
  author  = {Somenzi, Fabio},
  title   = {{CUDD: CU Decision Diagram Package}},
  version = {3.0.0},
  year    = {2015},
  url     = {https://github.com/davidkebo/cudd}
}
```

## Contributing, security and conduct

- [Contributing](.github/CONTRIBUTING.md) — what is welcome (docs,
  tutorials, CI, build-instruction fixes, problem reports) and what
  is not (changes to CUDD's source).
- [Security policy](.github/SECURITY.md) — CUDD is not patched here;
  report vulnerabilities through GitHub's private reporting.
- [Code of Conduct](.github/CODE_OF_CONDUCT.md) — Contributor Covenant 2.1.

Questions about using CUDD belong in
[Discussions](https://github.com/davidkebo/cudd/discussions); tutorial
questions belong at [davidkebo.com/cudd](https://davidkebo.com/cudd/).

## License

- **CUDD** is BSD-3-Clause, copyright the Regents of the University of
  Colorado — see [`LICENSE`](LICENSE), from upstream, unmodified.
- **The tutorials** under `tutorials/` are BSD-3-Clause,
  copyright David Kebo Houngninou — see
  [`tutorials/LICENSE`](tutorials/LICENSE).
