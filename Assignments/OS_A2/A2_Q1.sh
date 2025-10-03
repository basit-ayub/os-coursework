#!/bin/bash

NAME="Abdul Basit--Noor Alam"
ROLL="  23i3018  -- 23i3089"



user_create() {
    read -p "Enter the username to create: " USERNAME
    read -s -p "Enter the password: " PASSWORD
    echo

    if id "$USERNAME" &>/dev/null; then
        echo "User '$USERNAME' already exists. Skipping creation."
    else
        echo "Creating user '$USERNAME'"
        useradd -s /bin/bash "$USERNAME"
        echo "$USERNAME:$PASSWORD" | chpasswd &>/dev/null
        usermod -aG sudo "$USERNAME"
        echo "User '$USERNAME' created with sudo privileges!"
        echo
    fi
}

list_installed_apps() {
    echo "Installed Packages:"
    echo "-----------------------------------------------"
    printf "%-30s %-20s %s\n" "Package Name" "Version" "Description"
    echo "-----------------------------------------------"
    dpkg -l | awk '/^ii/ { printf "%-30s %-20s %s\n", $2, $3, $4 }'
}

install_app() {
    read -p "Enter the name of the application to install: " app_name

    if dpkg -l | grep -q "^ii  $app_name "; then
        echo "The application '$app_name' is already installed."
    else
        echo "Installing '$app_name'..."
        if sudo apt install -y "$app_name" &>/dev/null; then
            echo "'$app_name' installed successfully."
            echo "$app_name" > /tmp/last_installed_app
        else
            echo "Failed to install '$app_name'."
        fi
    fi
}

configure_network() {
    echo "Configuring Network Settings"
    read -p "Enter the network interface name (e.g., eth0): " iface

    sudo ip addr flush dev "$iface"
    sudo ip addr add 10.0.0.1/24 dev "$iface"
    sudo ip link set "$iface" up
    sudo ip route add default via 10.0.0.254 dev "$iface"
    echo "nameserver 8.8.8.8" | sudo tee /etc/resolv.conf > /dev/null

    echo "Network configuration complete for interface '$iface'"
    echo "$iface" > /tmp/last_iface
}

show_help() {
    echo "HELP MENU"
    echo
    echo "Available options:"
    echo "  -uc       Create a user and give admin rights"
    echo "  -ld       List all installed applications in a formatted table"
    echo "  -ins      Install an application if not already installed"
    echo "  -ipcon    Temporarily configure a network interface"
    echo "  -verify   Verify user, installed app, and IP configuration"
    echo "  -help     Show this help menu"
}

verify_system() {
    echo "System Verification Results:"
    echo "----------------------------"

    if id "OS_Assignment_1" &>/dev/null; then
        echo "User OS_Assignment_1 exists: PASS"
    else
        echo "User OS_Assignment_1 exists: FAIL"
    fi

    last_installed_app=$(cat /tmp/last_installed_app 2>/dev/null)
    if [ -n "$last_installed_app" ] && dpkg -l | grep -qw "$last_installed_app"; then
        echo "Package '$last_installed_app' is installed: PASS"
    else
        echo "Package '$last_installed_app' is installed: FAIL"
    fi

    last_iface=$(cat /tmp/last_iface 2>/dev/null)
    if [ -n "$last_iface" ] && ip addr show "$last_iface" | grep -q "10.0.0.1"; then
        echo "Interface '$last_iface' has IP 10.0.0.1: PASS"
    else
        echo "Interface with IP 10.0.0.1 not found: FAIL"
    fi
}



main() {
    # Check root
    if [ "$EUID" -ne 0 ]; then
        echo "Please run as root (use sudo)"
        exit 1
    fi

    # Print Name and Roll Number
    echo "Name: $NAME"
    echo "Roll Number: $ROLL"
    echo

    # Check and run the given switch
    case "$1" in
        -uc) user_create ;;
        -ld) list_installed_apps ;;
        -ins) install_app ;;
        -ipcon) configure_network ;;
        -verify) verify_system ;;
        -help) show_help ;;
        *) 
            echo "Invalid option. Use -help to see available switches."
            exit 1
            ;;
    esac
}

# Call main with all script arguments
main "$@"

