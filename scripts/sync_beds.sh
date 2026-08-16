#!/usr/bin/env bash

# Ensure the data directory exists
mkdir -p "$(dirname "$(realpath "$0")")/../data"

# Compile the BedSync utility
g++ -std=c++17 "../Modules/BedSync.cpp" -o "../bin/BedSync"
if [ $? -ne 0 ]; then
    echo "Failed to compile BedSync.cpp"
    exit 1
fi

# Run the utility to generate JSON configuration
"../bin/BedSync"
if [ $? -ne 0 ]; then
    echo "BedSync execution failed"
    exit 1
fi

# Run the Django management command to sync beds
python manage.py sync_beds_from_cpp
if [ $? -ne 0 ]; then
    echo "Django bed sync command failed"
    exit 1
fi

echo "Bed synchronization complete."
