#!/usr/bin/env bash
set -e

# Get the directory of the current script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the parent directory of the script
cd "$DIR/.."

# File path for the AUTHORS file
AUTHORS_FILE="AUTHORS"

# Content to write into AUTHORS file
cat <<- 'EOH' > "$AUTHORS_FILE"
# This file lists all individuals having contributed content to the repository.
# For how it is generated, see `simple_shell/authors_generator.sh`.
EOH

# Append git log contributors to AUTHORS file
git log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf >> "$AUTHORS_FILE"

# Display success message
echo "AUTHORS file generated successfully."

