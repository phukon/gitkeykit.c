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

### Unix-like systems
```bash
cd gitkeykit
sudo make install
```

## Usage 📖

### Setup GPG key for signing commits
```bash
gitkeykit
```

### Import PGP key from file
```bash
gitkeykit import <key_path>
```

### Reset Git and GPG configurations
```bash
gitkeykit --reset
```

## Building from Source 🛠️

### Compilation
```bash
make all
```

This will:
- Compile the source files from `src/`, `src/commands/`, and `src/utils/` directories
- Link object files and create the executable in `bin/` directory
- Create necessary directories (`build/` and `bin/`) if they don't exist
- Generate the executable `gitkeykit` (or `gitkeykit.exe` on Windows)

### Cleaning Up
```bash
make clean
```
This removes the `build/` and `bin/` directories along with all generated files.

## Error Codes 🚨

| Code | Description |
|------|-------------|
| 0 | Success |
| 1 | GPG not found |
| 2 | Git not found |
| 3 | Invalid arguments |
| 4 | No secret keys found |
| 5 | Invalid input |
| 6 | Git configuration error |
| 7 | Key generation error |
| 8 | Key import error |
| 9 | Git configuration reset error |
| 10 | GPG configuration reset error |
| 11 | Home directory not found |