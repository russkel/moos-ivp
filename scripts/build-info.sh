#!/bin/bash
#=============================================================
# Mike Benjamin, December 26th, 2017
#=============================================================
# This script will determine the lines of C++ code for for all
# subdirectories.
# 
# Each line will be of the form:
#    pFoobar   <number>
#
# It is intended that the user will likely generate this output
# to a file by simply re-directing the output which otherwise
# goes to the terminal:
#   $ ./build-info.sh > filename
#
# Initial motivation for this is to generate stats to be used
# by the manifest_wiki utility.
#
# The redirection of stderr in sloccount is to suppress MD5 error
# messages often found on MacOS where the md5sum utility is
# typically not installed.

# MYCODE=(pHelmIvP pEchoVar uXMS)
# echo ${MYCODE[*]}

#----------------------------------------------------------
#  Part 1: Check for and handle command-line arguments
#----------------------------------------------------------
for ARGI; do
    if [ "${ARGI}" = "--help" -o "${ARGI}" = "-h" ] ; then
        echo "build-info.sh [OPTIONS]                                 " 
	echo "                                                        "
	echo "SYNOPSIS                                                "
	echo "  This script will generate lines-of-code info suitable "
	echo "  suitable for generating manifest reports. This should "
	echo "  be run in the top-level src/ directory and will report"
	echo "  on all subdirectories.                                "
	echo "                                                        "
        echo "  --help,    -h      Display this help message          " 
        echo "  --info,    -i      Output brief description of script "  
        exit 0;
    elif [ "${ARGI}" = "--info" -o "${ARGI}" = "-i" ] ; then
	echo "Generate lines_of_code info for manifests"
	exit
    else 
        echo "Bad arg:" $ARGI "Run with -h for help."
        exit 1
    fi
done



for D in *; do
    if [ -d "${D}" ]; then
        LOC=`sloccount "${D}" 2> /dev/null | fgrep "cpp:" | awk -F' ' '{print $2}'`
        FOC=`sloccount --filecount "${D}" 2> /dev/null | fgrep "cpp:" | awk -F' ' '{print $2}'`

	WYR=`sloccount "${D}" 2> /dev/null | fgrep "Development" | awk -F' ' '{print $7}'`
	printf "${D}, ${LOC}, ${FOC}, ${WYR}\n"

    fi
done

exit 0

