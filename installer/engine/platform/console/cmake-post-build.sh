#!/bin/bash
#../../../

echo "-- Engine Path"
echo "${ENGINE_PATH}"

echo "-- Sandbox Path (test this for ide and external)"
SANDBOX_PATH=$(pwd)
echo "${SANDBOX_PATH}"

echo "-- Linking files"
pushd builds/console || exit

  if [ ! -d 'engine' ]; then
    mkdir "engine"
  fi

  pushd engine || exit
    if [ ! -d 'dependencies' ]; then
      mkdir dependencies
    fi

    if [ ! -d 'dependencies/Framework' ]; then
      pushd dependencies  || exit
        echo "Linking libraries"
        # shellcheck disable=SC2226
        ln -s "${ENGINE_PATH}/libs/Frameworks"
      popd || exit
    fi

    if [ !  -d 'dependencies/profiler' ]; then
      pushd dependencies || exit
        echo "Linking Tracy Server Profiler"
        # shellcheck disable=SC2226
        ln -s "${ENGINE_PATH}/libs/third-party/tracy/profiler"
      popd || exit
    fi

    if [ !  -d 'assets' ]; then
        echo "Linking Engine Data"
        # shellcheck disable=SC2226
        ln -s "${ENGINE_PATH}/engine/assets"
    fi

    if [ ! -d 'shaders' ]; then
        echo "Linking Shaders"
        # shellcheck disable=SC2226
        ln -s "${ENGINE_PATH}/engine/shaders/compiled" "shaders"
    fi

  popd || exit

  if [ ! -d 'assets' ]; then
      echo "Linking Example Project"
      # shellcheck disable=SC2226
      ln -s "${SANDBOX_PATH}"/assets
  fi

  if [ ! -d 'shaders' ]; then
      echo "Linking Example Project"
      # shellcheck disable=SC2226
      ln -s "${SANDBOX_PATH}/shaders/compiled" "shaders"
  fi

popd || exit

echo "- Adding Frameworks @rpath to binary ..."
## TODO: Some error on this file

#BINARY_PATH=$2

#echo "test"
#echo $BINARY_PATH
#if ! otool -l "$BINARY_PATH" | grep -q "@loader_path/dependencies/Frameworks"; then
#    install_name_tool -add_rpath @loader_path/dependencies/Frameworks "$BINARY_PATH"/MeowEngineTest2
#fi



#install_name_tool -add_rpath @loader_path/dependencies/Frameworks ../../../builds/console/MeowEngineTest2