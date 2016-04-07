#!/bin/sh

if [ -z "$NOTETRAINER_QMAKE" ]; then
	echo -----
	echo ERROR
	echo -----
	echo NOTETRAINER_QMAKE environment variable is not set.
	echo
	echo Example:
	echo export NOTETRAINER_QMAKE=/Users/user/Qt5.6.0/5.6/clang_64/bin/qmake
	echo
	read -n1 -r -p "Press any key to continue..." key
	exit 1
fi

export NOTETRAINER_QT_BIN_DIR=`dirname $NOTETRAINER_QMAKE`/

if [ -z "$NOTETRAINER_USER" ]; then
	#export USER=`id -un`
	export USER=`logname`
else
	export USER=$NOTETRAINER_USER
fi

if [ -z "$NOTETRAINER_USER" ]; then
	export GROUP=`id -gn`
	#export GROUP=`id -gn $USER`
else
	export GROUP=$NOTETRAINER_GROUP
fi

