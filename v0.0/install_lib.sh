#!/bin/bash

# This script should work for any shared library so long as
# I replace variable values with the appropriate values.

# File extentions.
obj=".o"
src=".c"
hdr=".h"

# Source file names.
FILES=( "string_utils" )

# Shared library name.
libnam="libsafe_utils.so"

# Absolute path, where to install the library.
libdir="/usr/lib/"

# Absolute path, where to remove an existing verison of the library.
oldlib="$libdir$libnam"

# Absolute path, where the library's source is living.
newlib="/home/lappop/programs/C_programs/Lib_safeutils/"

# Compiler flags (GCC).
# Careful, these flags are shared between every call to gcc.
# Input them as a string. (Empty string for no extra arguments.)

CFLAGS="-Wall -Wextra -Wpedantic -g" 

# Libraries to pass to the linker while creating object files.
# Input them as a string (Empty string for no extra libraries.)

CLIBS="-lsafe_utils"



# Remove existing .o files.
for file in ${FILES[@]}
do
    if [ -a "$file$obj" ]
    then
	`rm $file$obj`
	_mesg_="Removing $file$obj"
	printf "%-47s OK\n" "$_mesg_"
    else
	_mesg_="Removing $file$obj"
	printf "%-47s --\n" "$_mesg_"
    fi
done

_mesg_="Removing $libnam"
# Remove the old shared library in the current directory if it exists.
if [ -a "$libnam" ]
then
    `rm $libnam`
    printf "%-47s OK\n" "$_mesg_"
else
    printf "%-47s --\n" "$_mesg_"
    
fi

# Compile new position independent object files.
for sfile in ${FILES[@]}
do
    if [ -a "$sfile$src" ]
    then
	_mesg_="Creating $file$obj"
	`gcc $CFLAGS -c -fPIC $sfile$src $CLIBS`
	if [ $? == 0 ]
	then
	    printf "%-47s OK\n" "$_mesg_"
	else
	    printf "%-47s --\n" "$_mesg_"
	    exit
	fi
    fi
done


# Create the shared library.
_mesg_="Creating shared library"
cmd="$CFLAGS -shared -o $libnam "
for sfile in ${FILES[@]}
do
    if [ -a "$sfile$obj" ] 
    then
	cmd="$cmd $sfile$obj"
    fi
done
`gcc $cmd`
if [ $? != 0 ]
then  
    printf "%-47s --\n" "$_mesg_"
    exit
else
    printf "%-47s OK\n" "$_mesg_"
fi

# Remove the old library file
if [ -a "$oldlib" ]
then
    _mesg_="Removing $oldlib"
    `sudo rm -i $oldlib`
    if [ $? == 0 ]
    then
	printf "%-47s OK\n" "$_mesg_"
    else
	printf "%-47s --\n" "$_mesg_"
	exit
    fi

    _mesg_="Change directory to /usr/lib"
    # Change dir to /usr/lib and run ldconfig
    cd '/usr/lib/'
    if [ $? == 0 ]
    then
	printf "%-47s OK\n" "$_mesg_"
    else
	printf "%-47s --\n" "$_mesg_"
	exit
    fi
    
    _mesg_="ldconfig [no_param]"
    `sudo ldconfig`
    if [ $? != 0 ]
    then
	printf"%-47s --\n" "$_mesg_"
	exit
    else
	printf "%-47s OK\n" "$_mesg_"
    fi
    
    
else
    
    printf "%-47s --\n" "$_mesg_"
    exit

fi

_mesg_="Copy the new $libnam to /usr/lib"
# Copy the new library to /usr/lib/
`sudo cp $newlib$libnam $libdir`
if [ $? != 0 ]
then
    printf "%-47s --\n" "$_mesg_"
    exit
else
    printf "%-47s OK\n" "$_mesg_"

fi

_mesg_="ldconfig [-l] [$libnam]"
# Run the linker to create dependencies for our new library:
`sudo ldconfig -l $libnam`
if [ $? != 0 ]
then
    printf "%-47s --\n" "$_mesg_"
    exit
else
    printf "%-47s OK\n" "$_mesg_"
fi

exit
