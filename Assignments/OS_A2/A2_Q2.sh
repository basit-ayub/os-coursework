#!/bin/bash


show_help() {
    echo "Automated System Backup Script"
    echo
    echo "Usage: $0 <source_directory> <destination_directory>"
    echo
    echo "Arguments:"
    echo "  source_directory     The directory to back up."
    echo "  destination_directory The directory to save the backup."
    echo
    echo "Switches:"
    echo "  -help                 Display this help message and exit."
    echo
    exit 0
}

#help check
if [ "$1" == "-help" ]; then
    show_help
fi

#check for both arguments if not then retuern
if [ $# -ne 2 ]; then
    echo "Error: Two arguments (source and destination directories) are required."
    echo "Use -help for usage information."
    exit 1
fi

#asssignig names from cli argumetns
source_dir="$1"
destination_dir="$2"
log_file="backup.log"

#source check
if [ ! -d "$source_dir" ]; then
    echo "Error: Source directory '$source_dir' does not exist."
    exit 1
fi

# destination check and create if missing 
if [ ! -d "$destination_dir" ]; then
    echo "Destination directory '$destination_dir' does not exist. Creating it..."
    mkdir -p "$destination_dir"
fi

#extract the basename from the full path
source_dir_name=$(basename "$source_dir")

#current date
current_date=$(date +%Y-%m-%d)

# Create the full name for backup in giiven format
backup_filename="backup_${source_dir_name}_${current_date}.tar.gz"

# Create the backup and compress it 

tar -czf "$destination_dir/$backup_filename" -C "$source_dir" .

# Check if the backup was created successfully 
if [ $? -eq 0 ]; then
    echo "Backup of '$source_dir' created successfully at '$destination_dir/$backup_filename'."
    # Log the successful backup
    echo "$(date +%Y-%m-%d\ %H:%M:%S) - Backup of '$source_dir' created successfully." >> "$log_file"
else
    echo "Error: Failed to create backup."
    # Log the failed backup attempt
    echo "$(date +%Y-%m-%d\ %H:%M:%S) - Failed to create backup of '$source_dir'." >> "$log_file"
    exit 1
fi

# Verify the backup by checking if the .tar.gz file exists
echo
echo "Verifying the existence of .tar.gz file ..."
echo
if [ -f "$destination_dir/$backup_filename" ]; then
    echo "Verification: Backup '$backup_filename' exists. Backup successful."
else
    echo "Error: Backup '$backup_filename' was not created."
    exit 1
fi

