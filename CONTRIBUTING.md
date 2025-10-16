\# Contributing to ds\_demo\_cpp14\_msvc\_interactive\_v3\_5



Thanks for helping improve the \*\*Interactive C++14 Learning Lab\*\* (BST, linked lists, menu + autorun + step-through).



\## Quick start



1\. Create a branch  

&nbsp;   four example:

&nbsp;   

&nbsp;       git checkout -b feature/my-change



2\. Build in \*\*Visual Studio 2022\*\* (MSVC v143), \*\*x64 Debug\*\* (and Release before PR).



3\. Format your code using the repo \*\*.clang-format\*\* (Allman braces).



4\. Commit using \*\*Conventional Commits\*\* (see examples below).



5\. Open a Pull Request to `main` and complete the checklist.



---



\## Project standards



\- \*\*Language/Toolchain:\*\* C++14, MSVC v143 (VS 2022).

\- \*\*Style:\*\* Allman brace style (via `.clang-format`).

\- \*\*Identifiers:\*\* Avoid single-letter names, except loop indices `i`, `j`, `k`.

\- \*\*Functions:\*\* Prefer \*\*single-return\*\* per function (DO-178 style).

\- \*\*Headers / Inline:\*\* Put inline/template implementations in tracked `\*.inl` files.

\- \*\*Logging:\*\* Use the `Tee` infrastructure to mirror console → log file.

\- \*\*Warnings:\*\* Builds should introduce \*\*no new warnings\*\* at the repo’s warning level (e.g., `/W4`).



---



\## Repository layout



/src         # .cpp implementations

/include     # .h and .inl (tracked)

/assets      # small sample inputs / demo scripts (no binaries)

/docs        # screenshots / notes



> Build artifacts and IDE caches are ignored by `.gitignore` (`.vs/`, `x64/`, `Debug/`, `Release/`, `obj/`, `\*.exe`, `\*.pdb`, `\*.recipe`, etc.).  

> \*\*Do not commit\*\* binaries or large files. Use Git LFS only if a sample must exceed ~10 MB.



---



\## Commit message convention (Conventional Commits)



Examples:



\- `feat: add step-through renderer for BST insert`

\- `fix: correct linked-list splice edge case`

\- `chore: ignore obj/ and \*.recipe`

\- `docs: expand README with autorun instructions`

\- `refactor: extract Tee abstraction into separate unit`



Scope is optional, e.g. `feat(bst): …`.



---



\## Branching \& releases



\- Work in branches: `feature/\*`, `fix/\*`.

\- Open PRs against `main`.

\- Releases are tagged by the maintainer, e.g. `v3.5.0`.



---



\## Pull Request checklist



\- \[ ] Builds on \*\*VS 2022\*\* in \*\*x64 Debug/Release\*\*.

\- \[ ] Code formatted with repo `.clang-format` (Allman).

\- \[ ] No new compiler warnings.

\- \[ ] Follows \*\*single-return\*\* and identifier rules.

\- \[ ] Comments added/updated where logic is non-trivial.

\- \[ ] `README.md` updated if behavior/usage changed.

\- \[ ] No binaries or build artifacts in the diff.



---



\## Reporting bugs



Please include:

\- Repro steps (menu path / autorun script used).

\- Expected vs. actual behavior.

\- Console/log output snippet (from the `Tee` log if available).

\- VS version and configuration (x64 Debug/Release).



---



\## Security / sensitive info



Do not include secrets (API keys, tokens) or personal data in commits, issues, or logs.



---



\## License



By contributing, you agree your contributions are licensed under the \*\*MIT License\*\* included in this repository.



