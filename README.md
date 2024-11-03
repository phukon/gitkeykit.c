# GitKeyKit (C Port) 🔐

A C implementation of [GitKeyKit](https://github.com/phukon/gitkeykit), originally created in TypeScript. This port brings the same simplified PGP key management for Git commit signing to C, making it more portable and dependency-free.

GitKeyKit is a lightweight command-line tool that simplifies PGP key management for Git commit signing. It automates the process of creating, importing, and configuring GPG keys for Git commit verification.

## Features ✨

- **Create PGP Keys**: Automatically generate new PGP keys using your Git user information
- **Import Existing Keys**: Import your existing PGP keys seamlessly
- **Git Configuration**: Automatically configure Git to use your PGP key for commit signing
- **Cross-Platform**: Works on both Windows and Unix-based systems
- **Easy Reset**: Quick command to reset all GPG-related Git configurations

## Prerequisites 📋

Before using GitKeyKit, ensure you have:

- Git installed and configured with user.name and user.email
- GPG (GnuPG) installed
  - Windows: Install [Gpg4win](https://www.gpg4win.org/)
  - macOS: `brew install gnupg`
  - Linux: `sudo apt-get install gnupg` (Ubuntu/Debian) or equivalent

## Installation 🚀

### From Source
```bash
git clone https://github.com/yourusername/gitkeykit.git
cd gitkeykit
make
bash
gitkeykit create
bash
gitkeykit import path/to/key.asc
bash
gitkeykit --reset
```

## Error Codes 🚨

- `0`: Success
- `1`: GPG not found
- `2`: Git not found
- `3`: Invalid arguments