#!/usr/bin/env python3
import os
import re
import subprocess
import sys
import shutil
from datetime import datetime

# Define necessary files and optional files
necessary_files = [
    os.path.join("..", "..", "watch-library", "hardware", "main.c"), 
    "Makefile"
]
optional_files = ["alarms.csv", "timers.csv", "timezone_offset"]

# Usage instructions
usage = """
This is a helper script to build the Sensor-Watch firmware for the specified board color while setting local time.

Usage: {} [-h] {{RED|GREEN|BLUE}} [install|emulate]
    -h|--help   Print this usage
    install     Runs 'make COLOR={{RED|GREEN|BLUE}} && make install COLOR={{RED|GREEN|BLUE}}'
    emulate     Runs 'emmake make COLOR=RED && python3 -m http.server -d build-sim'
    clean       Runs 'make clean COLOR={{RED|GREEN|BLUE}}'
""".format(os.path.basename(__file__))

def validate_color_argument(color):
    color = color.upper()
    if color in ["RED", "GREEN", "BLUE"]:
        return color
    else:
        print(f"Error: first argument must be RED, GREEN, or BLUE.\n\n{usage}")
        sys.exit(1)

def ensure_correct_directory():
    current_dir = os.getcwd()
    expected_dir = os.path.normpath(os.path.join("movement", "make"))
    if os.path.basename(current_dir) != os.path.basename(expected_dir):
        print("This script must be executed from within the movement/make directory.")
        sys.exit(1)

def check_file(file):
    file_path = os.path.normpath(file)  # Normalize path for cross-platform
    if not os.path.isfile(file_path):
        print(f"\t--Error: Required file '{file_path}' not found.")
        sys.exit(1)
    else:
        print(f"\t--File '{file_path}' found.")

def check_optional_file(file):
    file_path = os.path.normpath(file)  # Normalize path for cross-platform
    if not os.path.isfile(file_path):
        print(f"\t--Note: Optional file '{file_path}' not found.")
    else:
        print(f"\t--Optional file '{file_path}' found.")

def update_date_time(file_path):
    # Get current date and time
    now = datetime.now()
    current_data = {
        "year": now.year % 100 - 20,
        "month": now.month,
        "day": now.day,
        "hour": now.hour,
        "minute": now.minute
    }

    # Read the file and update lines
    with open(file_path, 'r') as file:
        lines = file.readlines()

    updated_lines = []
    for line in lines:
        for unit, value in current_data.items():
            if f"date_time.unit.{unit}" in line:
                line = f"        date_time.unit.{unit} = {value};\n"
        updated_lines.append(line)

    # Write the updated lines back to the file
    with open(file_path, 'w') as file:
        file.writelines(updated_lines)

# Main script execution
if len(sys.argv) == 1 or sys.argv[1] in ['-h', '--help']:
    print(usage)
    sys.exit(0)

# Validate color argument
COLOR = validate_color_argument(sys.argv[1])

# Validate optional install or emulate argument
make_arg = None
if len(sys.argv) > 2:
    if sys.argv[2] in ['install', 'emulate', 'clean']:
        make_arg = sys.argv[2]
    else:
        print(f"Error: Unrecognized option '{sys.argv[2]}'.\n{usage}")
        sys.exit(1)

# Ensure we're in the correct directory
ensure_correct_directory()

# Check for necessary files
print("\nChecking for necessary files\n")
for file in necessary_files:
    check_file(file)

# Check for optional files
print("\nChecking for optional files\n")
for file in optional_files:
    check_optional_file(file)

# Set date and time variables
update_date_time(necessary_files[0])

# Build the firmware
if make_arg is None:
    print(f"\n\nBuilding with COLOR={COLOR}\n")
    result = subprocess.run(["make", f"COLOR={COLOR}"], check=False)
    if result.returncode == 0:
        print("\n\nFirmware successfully built!!!!")
    else:
        print("\n\nSomething went wrong -- see `make` output above.")
        sys.exit(1)
elif make_arg == "install":
    print(f"\n\nBuilding and installing with COLOR={COLOR}\n")
    result = subprocess.run(["make", f"COLOR={COLOR}"], check=False)
    if result.returncode == 0:
        result = subprocess.run(["make", "install", f"COLOR={COLOR}"], check=False)
        if result.returncode == 0:
            print("\n\nFirmware successfully built and installed!!!!")
        else:
            print("\n\nSomething went wrong -- see `make install` output above.")
            sys.exit(1)
    else:
        print("\n\nSomething went wrong -- see `make` output above.")
        sys.exit(1)
elif make_arg == "emulate":
    print(f"\n\nBuilding and emulating with COLOR={COLOR}\n")
    result = subprocess.run(["emmake", "make", f"COLOR={COLOR}"], check=False)
    if result.returncode == 0:
        subprocess.run(["python3", "-m", "http.server", "-d", "build-sim"], check=False)
    else:
        print("\n\nSomething went wrong -- see `emmake` output above.")
        sys.exit(1)
elif make_arg == "clean":
    print(f"\n\nCleaning up the build\n")
    result = subprocess.run(["make", "clean", f"COLOR={COLOR}"], check=False)
    if result.returncode == 0:
        print("\n\nCleanup finished successfully.")
    else:
        print("\n\nSomething went wrong -- see `emmake` output above.")
        sys.exit(1)

