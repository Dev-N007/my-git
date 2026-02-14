# MyGit — Minimal Git Implementation in C

## Overview

MyGit is a simplified reimplementation of Git’s core internals written in C.  
The purpose of this project is to understand how Git works internally by building a basic content-addressable version control system from scratch.

It supports:

- `init` — initialize repository  
- `add` — stage files  
- `commit` — create commits  
- `status` — show working directory state  
- `revert` — restore files to last commit  
- `log` — displays the commit history 
- `rm` — removes files from staging area  

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
./mygit init

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
./mygit add file.txt

Steps:

1. Read file content  
2. Create blob object  
3. Compute SHA-1  
4. Compress and store object  
5. Record hash in index  

---

## How Commit Works
./mygit commit "message"

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

## How Status Works
./mygit status

Shows the current state of the working directory.

Steps:

1. Reads the index (`.git/index`).
2. For each staged file:
   - If the file is missing → marked as **deleted**.
   - If its current hash differs from stored hash → marked as **modified**.
3. Scans the current directory:
   - Files not present in the index → marked as **untracked**.

This helps identify changes before committing.


## How Revert Works
./mygit revert

Restores working directory files to the state of the last commit.

Steps:

1. Read latest commit SHA  
2. Read associated tree object  
3. Restore blob contents  
4. Overwrite working directory files  

This behaves similarly to:

git restore .
or
git reset --hard HEAD

It does not delete commit history.  
It restores files to match the last committed snapshot.

---

## How log Works
./mygit log

Displays the commit history starting from the latest commit (HEAD).

Steps:

1. Reads the latest commit SHA from `.git/refs/heads/master`.
2. Loads and decompresses the commit object.
3. Displays:
   - Commit SHA
   - Author
   - Date
   - Commit message
4. Reads the parent commit (if exists).
5. Repeats until no parent is found.

This recreates Git’s commit history traversal using parent-linked commits.

## How rm Works
./mygit rm <filename>

Removes a file from both:

- Working directory  
- Staging area (index)

Steps:

1. Deletes the file from the current directory.
2. Removes the file’s entry from `.git/index`.
3. Updates the index file.

## Compilation

Requires:

- GCC  
- OpenSSL  
- zlib  

Compile with:

gcc src/*.c -Iinclude -lssl -lcrypto -lz -o ccgit

---

## Example Usage

./mygit init
echo "hello" > file.txt
./mygit add file.txt
./mygit commit "first commit"
./mygit status
./mygit revert

---

## What This Project Demonstrates

- Systems programming in C  
- File system operations  
- Cryptographic hashing  
- Data compression  
- Git’s internal storage model  
- Basic repository state management 

---

## Conclusion

mygit is a simplified educational implementation of Git’s core storage engine.  
It demonstrates how Git stores objects, creates commits, and manages repository history at a low level.
