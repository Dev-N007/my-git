# ccgit — Minimal Git Implementation in C

## Overview

ccgit is a simplified reimplementation of Git’s core internals written in C.  
The purpose of this project is to understand how Git works internally by building a basic content-addressable version control system from scratch.

It supports:

- `init` — initialize repository  
- `add` — stage files  
- `commit` — create commits  

---

## Key Concepts

### 1. Content-Addressable Storage

Git stores data using SHA-1 hashes instead of filenames.

When a file is added:

blob <size>\0<file_content>

The SHA-1 hash of this data becomes the object’s identity.  
Objects are stored inside:

.git/objects/<first_2_chars>/<remaining_38_chars>

If two files have identical content, they share the same hash.

---

### 2. SHA-1 Hashing

SHA-1 generates a 40-character hash.  
Any change in file content produces a new hash.

This ensures:

- Integrity  
- Uniqueness  
- Immutability  

---

### 3. zlib Compression

All objects are compressed before being stored to save space.  
This matches Git’s internal storage behavior.

---

## Repository Structure

After running:

./ccgit init

Structure:
.git/
├── HEAD
├── objects/
├── refs/heads/master
└── index

- `HEAD` → points to current branch  
- `objects/` → stores compressed objects  
- `refs/heads/master` → stores latest commit hash  
- `index` → staging area  

---

## How Add Works

./ccgit add file.txt

Steps:

1. Read file content  
2. Create blob object  
3. Compute SHA-1  
4. Compress and store object  
5. Record hash in index  

---

## How Commit Works

./ccgit commit "message"

Steps:

1. Read staged files from index  
2. Create tree object  
3. Create commit object  
4. Store commit  
5. Update branch reference  

Commit format:

tree <tree_sha>
author Name <email> timestamp
committer Name <email> timestamp

---

## Compilation

Requires:

- GCC  
- OpenSSL  
- zlib  

Compile with:

gcc src/*.c -Iinclude -lssl -lcrypto -lz -o ccgit

---

## Example Usage

./ccgit init
echo "hello" > file.txt
./ccgit add file.txt
./ccgit commit "first commit"

---

## What This Project Demonstrates

- Systems programming in C  
- File system operations  
- Cryptographic hashing  
- Data compression  
- Git’s internal storage model  

---

## Conclusion

ccgit is a simplified educational implementation of Git’s core storage engine.  
It demonstrates how Git stores objects, creates commits, and manages repository history at a low level.
