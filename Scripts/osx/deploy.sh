#!/bin/bash

source ./setup_environment.sh
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

MACDEPLOYQT=${NOTETRAINER_QT_BIN_DIR}/macdeployqt
BUILD_DIR=`find ../../.. -depth 1 -iname "build-NoteTrainer*-Release"`
RELEASE_DIR="../../../release-osx"
INSTALLER_DIR="../../../installer-osx"

if [ -z "$BUILD_DIR" ]; then
	echo -----
	echo ERROR
	echo -----
	echo Release build directory not found
	echo
	read -n1 -r -p "Press any key to continue..." key
	exit 1
fi

echo Removing old release folders
sudo rm -rf "$RELEASE_DIR"
mkdir -p "$RELEASE_DIR"
cp -R "${BUILD_DIR}/NoteTrainer.app" "$RELEASE_DIR/"

sudo rm -rf "$INSTALLER_DIR"
mkdir -p "$INSTALLER_DIR"

echo Calling macdeployqt
# -dmg
sudo ${MACDEPLOYQT} "$RELEASE_DIR/NoteTrainer.app" -verbose=3 > deploy_log.txt 2>&1

echo Creating dmg file
# --volicon "appicons/osx.icns" \
# --background "images/osx/NoteTrainerDmg.tiff" \
sudo ../../ThirdParty/create-dmg/create-dmg \
	--volname "NoteTrainer" \
	--window-size 600 398 \
	--icon-size 96 \
	--icon "NoteTrainer" 157 280 \
	--app-drop-link 467 280 \
	"$INSTALLER_DIR/NoteTrainer.dmg" \
	"$RELEASE_DIR/"
sudo chown -R ${USER}:${GROUP} "$INSTALER_DIR"

