#!/bin/bash

# Create example directory
mkdir -p example

# Create schema.txt
cat > example/schema.txt <<EOF
age int
name string
email string
is_active bool
filepath filepath
EOF

# Create data.txt
cat > example/data.txt <<EOF
-- schema --
age int
name string
email string
is_active bool
filepath filepath

-- Hash Map 1 --
age 21
name Abhay
email abhay@example.com
is_active true
filepath /home/abhay/file.txt

-- Hash Map 2 --
age 22
name Aryan
email aryan@example.com
is_active false
filepath C:\\Users\\Aryan\\doc.txt
EOF

# Create diff.diff.files
cat > example/diff.diff.files <<EOF
[Feature] Added bool and filepath type support
[Feature] Added purge function to clear all records
[Test]    Inserted 2 records with different types
[Test]    Updated record with key=10 and verified output
[Test]    Deleted record with key=10 and checked BST state
[Test]    Committed and retrieved data from files/text.txt
EOF

# Create a README for the example directory
cat > example/README.md <<EOF
# Example Usage

This directory contains example files and scripts to quickly test the C++ BST database project.

## Quick Start

### On Linux/macOS

\`\`\`sh
bash ../scripts/main.sh
\`\`\`

### On Windows (PowerShell)

\`\`\`powershell
../scripts/main.ps1
\`\`\`

## Files

- \`schema.txt\` — Example schema definition.
- \`data.txt\` — Example data file (can be used as input or for comparison).
- \`diff.diff.files\` — Example diff file for tracking changes or features.
EOF

echo "Example directory and files created!"