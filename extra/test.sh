#!/bin/bash

# echo with option -n
echo_with_n() {
	echo "Hello, world!"
    echo -n "Hello, world! "
    echo "Hello, \nworld!"
    echo -E "Hello, \nworld!"
    message="Hello, world!"
	echo "$message"
	echo -e "Hello, \033[1;31mworld!\033[0m"
	echo "Hello," "world!"
	echo -E "Hello, \nworld!"
}

# cd with only a relative or absolute path
cd_with_path() {
    cd /tmp
    pwd
    cd -
    pwd
}

# pwd with no options
pwd_no_options() {
    pwd
}

# export with no options
export_no_options() {
    export MY_VARIABLE="Hello"
    echo "MY_VARIABLE is $MY_VARIABLE"
}

# unset with no options
unset_no_options() {
    MY_VARIABLE="Hello"
    echo "MY_VARIABLE is $MY_VARIABLE"
    unset MY_VARIABLE
    echo "MY_VARIABLE is $MY_VARIABLE"
}

# env with no options or arguments
env_no_options() {
    env
}

# exit with no options
exit_no_options() {
    echo "Exiting..."
    exit 0
}

# Test the commands
echo_with_n
#cd_with_path
#pwd_no_options
#export_no_options
#unset_no_options
#env_no_options
#exit_no_options

# Cleanup (optional)
#unset -f echo_with_n cd_with_path pwd_no_options export_no_options unset_no_options env_no_options exit_no_options

