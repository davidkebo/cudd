# Security policy

## CUDD is no longer maintained upstream

Fabio Somenzi stopped maintaining CUDD after 3.0.0 (2015). This
repository distributes his releases unmodified; it does not patch
CUDD's source, including for security fixes. See
[`CONTRIBUTING.md`](CONTRIBUTING.md) for why, and for forks that do
carry patches.

## Supported versions

| Version | Source fixes here |
| ------- | ------------------ |
| 3.0.0   | No |
| 2.5.1   | No |
| 2.5.0   | No |
| 2.4.2   | No |

No version of CUDD's source receives security fixes in this
repository. If you need a patched build, see the forks listed in
`CONTRIBUTING.md`.

## Reporting a vulnerability

Please do not open a public issue for a security report. Use GitHub's
private reporting instead:

1. Go to the repository's **Security** tab.
2. Select **Report a vulnerability**.
3. Describe the issue, affected version(s), and, if possible, how to
   reproduce it.

Do not report vulnerabilities by email; this repository does not list
one for that purpose.

## What happens after a report

1. **Acknowledgment.** We aim to acknowledge a report within a few
   days.
2. **Assessment.** Because CUDD's source is not patched here, most
   reports will concern the repository's own tooling (CI workflows,
   build scripts, the documentation build, the tutorials) rather than
   CUDD itself. We assess which case applies.
3. **Advisory.** If the report warrants it, we publish a GitHub
   Security Advisory describing the issue and any mitigation.
4. **README note.** If the issue affects CUDD's source itself, the
   README is updated to point affected users to a maintained fork,
   since this repository will not carry the fix.

Private vulnerability reporting and Dependabot alerts are enabled on
this repository.
