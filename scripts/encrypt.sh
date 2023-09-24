#!/bin/bash

# Specify the folder paths
input_folder="output"
output_folder="encrypted"

# Create the "encrypted" directory inside the specified folder if it doesn't exist
mkdir -p "$output_folder"

# Set the encryption key and IV as hexadecimal strings
key="00000000000000000000000000000000000000000000000000000000000000f1"
iv="000000000000000000000000000000e2"

# Function to encrypt a file with AES-256 CBC encryption and add padding
function encrypt_file() {
    local input_file="$1"
    local output_file="$2"

    # Calculate the padding size needed to align the input file's length with the AES block size (16 bytes)
    filesize=$(stat -c%s "$input_file")
    padding_size=$((16 - (filesize % 16)))

    # Add padding to the input file using 'dd', then encrypt with 'openssl' and remove the extra line
    (cat "$input_file"; dd if=/dev/zero bs=1 count="$padding_size") | openssl enc -aes-256-cbc -K "$key" -iv "$iv" -nopad -out "$output_file"
    truncate -s -"$padding_size" "$output_file"
}

# Loop through each file in the input folder
for input_file in "$input_folder"/*; do
    # Extract the filename without the path
    filename=$(basename "$input_file")

    # Generate the output filename in the format "encrypted_filename"
    output_file="$output_folder/$filename"

    # Encrypt the file using AES-256 CBC encryption with padding and remove the extra line
    encrypt_file "$input_file" "$output_file"

    # Optionally, print the result for each file
    echo "Encrypted $input_file -> $output_file"
done