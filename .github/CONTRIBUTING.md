# Contributing to this repository

This repository holds Fabio Somenzi's CUDD releases, unmodified, plus
the documentation, tutorials and build tooling around them. Please read
this before opening an issue or a pull request.

## What is welcome

- Fixes and improvements to this repository's own documentation
  (`README.md`, `CITATION.cff`, the files under `.github/`).
- Fixes and improvements to the tutorials under `tutorials/`.
- Improvements to the CI workflows and build instructions: new
  platforms, new compilers, better caching, clearer error messages.
- Reports of a broken download link, a checksum mismatch, or a build
  failure that happens from a clean clone following the README's
  quick start.

## What is not accepted

Changes to CUDD's own source code (anything under `cudd/`, `cplusplus/`,
`dddmp/`, `epd/`, `mtr/`, `st/`, `util/`, `nanotrav/`, `doc/`, `configure`,
`configure.ac`, `Makefile.am`, or any other file that came from one of
Fabio Somenzi's release tarballs) are not accepted here.

This repository's value is that it holds exactly what Somenzi released,
one tagged commit per version, byte-identical to the original archive.
A CI job (`pristine`) checks every push against tag `v3.0.0` for exactly
this reason. Patching CUDD here would quietly turn a trusted mirror into
an unverifiable fork, which is the one thing this repository must not
become.

If you need CUDD with bug fixes, patches, or new features, these
community-maintained forks accept them:

- [cuddorg/cudd](https://github.com/cuddorg/cudd)
- [ssoelvsten/cudd](https://github.com/ssoelvsten/cudd)

## Reporting a build problem

Open an issue using the "Build problem" template. Include:

- the CUDD version or tag you built;
- your OS and compiler, with version (`gcc --version`, `clang --version`,
  or similar);
- the exact `./configure` options you used;
- the commands you ran and the point where they failed;
- the relevant part of the build log.

Check the [`build` and `legacy` CI jobs](../../actions) first: if CI
builds the same version cleanly on the same OS and compiler, the
problem is most likely local to your environment, and the issue should
say what differs.

## Reporting a broken download

Open an issue using the "Broken download" template, with the URL, the
checksum you expected, and the checksum you got.

## Pull requests

- Keep each pull request to one concern.
- CI must pass. The `pristine`, `build` and `tutorials` jobs are
  required; `windows` and `legacy` are informational.
- See the pull request template's checklist for which paths may change.
