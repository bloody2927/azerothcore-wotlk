#!/usr/bin/env bash
# Simple helper that installs AzerothCore build dependencies
set -e
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
"$SCRIPT_DIR/../acore.sh" install-deps
