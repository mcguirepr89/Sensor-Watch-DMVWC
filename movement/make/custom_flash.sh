#!/usr/bin/env bash
set -e

# Function to override echo with -e flag by default
echo() {
    command echo -e "$@"
}

# Files and executables to check
necessary_files=(../../watch-library/hardware/main.c Makefile)
optional_files=(alarms.csv timers.csv timezone_offset)
executables=(sed)

# Usage instructions
usage=$(cat <<-END
This is a helper script to build the Sensor-Watch firmware for the 
specified board color while setting local time.

Usage: $(basename "$0") [-h] {RED|GREEN|BLUE} [install]
    -h|--help   Print this usage
    install     Runs 'make COLOR={RED|GREEN|BLUE} && make install COLOR={RED|GREEN|BLUE}'
END
)

# Parse and validate the COLOR argument
validate_color_argument() {
    local color="$1"
    color=$(echo "$color" | tr '[:lower:]' '[:upper:]')
    if [[ "$color" == "RED" || "$color" == "GREEN" || "$color" == "BLUE" ]]; then
        COLOR="$color"
    else
        echo "Error: first argument must be RED, GREEN, or BLUE. See usage below.\n"
        echo "$usage"
        exit 1
    fi
}

# Ensure the script is run from the correct directory
ensure_correct_directory() {
    if [[ "${PWD#/*/*/*/*/*}" != "movement/make" ]]; then
        echo "This script must be executed from within the movement/make directory."
        exit 1
    fi
}

# Check for a required file
check_file() {
    local file="$1"
    if [[ ! -f "$file" ]]; then
        echo "\t--Error: Required file '$file' not found."
        exit 1
    else
        echo "\t--File '$file' found."
    fi
}

# Check for an optional file
check_optional_file() {
    local file="$1"
    if [[ ! -f "$file" ]]; then
        echo "\t--Note: Optional file '$file' not found."
    else
        echo "\t--Optional file '$file' found."
    fi
}

# Check for an executable
check_executable() {
    local exec="$1"
    if ! command -v "$exec" &> /dev/null; then
        echo "\t--Error: Required executable '$exec' not found."
        exit 1
    else
        echo "\t--Executable '$exec' found."
    fi
}

# Main script execution

# Display usage if -h or --help is passed
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    echo "$usage"
    exit 0
fi

# Ensure COLOR argument is provided and valid
if [[ -z "$1" ]]; then
    echo "$usage"
    exit 1
else
    validate_color_argument "$1"
fi

# Ensure install argument is valid if provided
if [[ -n "$2" ]];then
    if [[ "$2" == "install" ]];then
        echo "Installing after make"
    else
        echo "Error: Unrecognized option '$2'. See $(basename "$0") -h for more info."
        exit 1
    fi
fi
       

# Ensure we're in the correct directory
ensure_correct_directory

# Check for necessary files
echo "\nChecking for necessary files\n"
for file in "${necessary_files[@]}"; do
    check_file "$file"
done

# Check for optional files
echo "\nChecking for optional files\n"
for file in "${optional_files[@]}"; do
    check_optional_file "$file"
done

# Check for required executables
echo "\nChecking for necessary executables\n"
for exec in "${executables[@]}"; do
    check_executable "$exec"
done

# Set date and time variables
YEAR="$(( $(date +%-g) - 20 ))"
MONTH="$(date +%-m)"
DAY="$(date +%-d)"
HOUR="$(date +%-H)"
MINUTE="$(( $(date +%-M) + 1 ))"

# Update local time in the RTC
echo "\nSetting current time in ${necessary_files[0]} to \"$HOUR:$MINUTE $DAY/$MONTH/202$YEAR\"\n"
sed -Ei "
    s/(unit.year = ).*(;)/\1$YEAR\2/;
    s/(unit.month = ).*(;)/\1$MONTH\2/;
    s/(unit.day = ).*(;)/\1$DAY\2/;
    s/(unit.hour = ).*(;)/\1$HOUR\2/;
    s/(unit.minute = ).*(;)/\1$MINUTE\2/" "${necessary_files[0]}"

# Build (and optionally install) the firmware
echo "\n\nBuilding${2:+ and installing} with COLOR=$COLOR\n"
if [[ -z "$2" ]]; then
    if make COLOR="$COLOR"; then
        echo "\n\nFirmware successfully built!!!!"
    else
        echo "\n\nSomething went wrong -- see \`make\` output above."
        exit 1
    fi
else
    if make COLOR="$COLOR" && make install COLOR="$COLOR"; then
        echo "\n\nFirmware successfully built and installed!!!!"
    else
        echo "\n\nSomething went wrong -- see \`make install\` output above."
        exit 1
    fi
fi
