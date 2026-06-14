#!/bin/bash

# grab directory param
# grab sandbox name
# create folder in the directory
# rename to sandbox name
# goinside the sandbox folder
# create assets, source folder
# create .sh to make builds

#/Users/akira/Downloads/physicat/meowprojects

SANDBOX_NAME="${1}"
SANDBOX_DIRECTORY="${2}"
SH_DIRECTORY="$(cd "$(dirname "$0")" && pwd)"


echo "Sandbox project location: ${SANDBOX_DIRECTORY}/${SANDBOX_NAME}"
echo "Run location: $SH_DIRECTORY"

mkdir -p "${SANDBOX_DIRECTORY}/${SANDBOX_NAME}"
cd "${SANDBOX_DIRECTORY}/${SANDBOX_NAME}" || exit

mkdir "assets"
mkdir "source"
cp "${SH_DIRECTORY}/Layout.ini" ""
cp "${SH_DIRECTORY}/TemplateSandboxBuild.sh" ""
mv TemplateSandboxBuild.sh "${SANDBOX_NAME}"

