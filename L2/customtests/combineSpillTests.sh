#!/bin/bash

# Define the directory containing the files
directory="/home/apc6353/Documents/school/cs322/322_framework/L2/tests/spill"

# Define the output file
output_file="spillTestsCombined.txt"

# Clear contents of output file if it already exists
> "$output_file"

# Loop through each .L2f file in the subdirectory
for file in "$directory"/*.L2f; do
    echo "Combining contents of $file"
    echo "=================================" >> "$output_file"
    cat "$file" >> "$output_file"
    echo -e "\n\n" >> "$output_file"  # Add visible separation between files
done

echo "Combining files completed. Output saved to $output_file"
