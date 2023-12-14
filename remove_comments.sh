#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <JavaFile>"
    exit 1
fi
input_file=$1
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found."
    exit 1
fi

sed -i '/\/\*/,/\*\//d; s/\/\/.*//' "$input_file"

echo "Comments removed from '$input_file'."
