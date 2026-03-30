# reverse_me

A set of compiled C binaries where the source code is hidden. The goal is to find the correct password for each level using static analysis tools — without running the binary on your host machine.

---

## Running the original binaries

Levels 1 and 2 are 32-bit ELF binaries and require a compatible environment. Use Docker to avoid library conflicts on the host:

```bash
cd $(git rev-parse --show-toplevel)
docker run --rm -it -v $(pwd):/app ubuntu:22.04 bash -c "
  dpkg --add-architecture i386 &&
  apt-get update -q &&
  apt-get install -y libc6:i386 &&
  cp /app/level1/exe/level1 /tmp/level1 &&
  cp /app/level2/exe/level2 /tmp/level2 &&
  cp /app/level3/exe/level3 /tmp/level3 &&
  chmod +x /tmp/level* &&
  bash
"
# Inside the container:
/tmp/levelX
```

---

## Compiling and running the reconstructed source

Once you have reverse-engineered a level and written `source.c`, compile and test it directly:

```bash
gcc source.c -o /tmp/my_levelX
chmod +x /tmp/my_levelX
/tmp/my_levelX
```

Levels 1 and 2 produce 32-bit binaries — add `-m32` if compiling on a 64-bit host:

```bash
gcc -m32 source.c -o /tmp/my_levelX
```

---

## Analysis tools

```bash
# Extract printable strings from a binary
strings ./levelX | grep -v "^[. ]" > levelx_strings.txt

# Disassemble
objdump -d ./levelX > levelx.asm
```

For decompilation, [dogbolt.org](https://dogbolt.org/) (Decompiler Explorer) provides multiple decompilers side by side. Ghidra is used for deeper analysis and pseudocode reconstruction.

---

## Levels

### Level 1 — ELF 32-bit

The binary prompts for a key and compares it directly against a hardcoded string using `strcmp`. The password is assembled character by character on the stack before the comparison.

```
Please enter key: __stack_check
Good job.
```

**Analysis path:** `strings` output reveals the target string. Confirmed via Ghidra pseudocode showing stack-constructed char arrays fed directly into `strcmp`.

---

### Level 2 — ELF 32-bit

The input is decoded before comparison. The program expects a numeric-encoded string: the first two characters must be `00`, and every subsequent group of three digits is converted via `atoi` into a single byte. The result is then compared against a plaintext string.

```
Please enter key: 00101108097098101114101
Good job.
```

**Encoding scheme:** `00` prefix + each character of `delabere` as a zero-padded three-digit ASCII value.

| Char | ASCII | Encoded |
|------|-------|---------|
| d    | 100   | `100`   |
| e    | 101   | `101`   |
| l    | 108   | `108`   |
| a    | 097   | `097`   |
| b    | 098   | `098`   |
| e    | 101   | `101`   |
| r    | 114   | `114`   |
| e    | 101   | `101`   |

**Analysis path:** Ghidra pseudocode reveals the decode loop and the `strcmp` target `"delabere"`. The `no()` function calls `exit(1)` on failure, `ok()` prints `"Good job."` on success.

---

### Level 3 — ELF 64-bit

Same encoding scheme as Level 2. The prefix must be `42`, and each subsequent byte group decodes to a character. The decoded output is compared against `"********"` (eight asterisks, ASCII `42`).

```
Please enter key: 42042042042042042042042
Good job.
```

**Encoding scheme:** `42` prefix + `042` repeated seven times (ASCII 42 = `*`).

**Analysis path:** Ghidra pseudocode shows obfuscated function names (`___syscall_malloc`, `____syscall_malloc`) masking `nope()` and `good_job()`. The `strcmp` target string `"********"` appears directly in the strings output. The switch-like if-else chain over the `strcmp` return value calls `good_job()` only when `result == 0`.

---

## Directory structure

```
levelX/
├── exe/        Binary to crack
├── doc/        Analysis artifacts (strings, disassembly, Ghidra output)
├── source.c    Reconstructed or original source
└── password    Solution
```