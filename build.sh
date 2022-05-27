#!/bin/bash

## you should opt: debug, release, releasewithdebinfo
case "$1" in
    release)
	model=release
	;;
    debug)
	model=debug
	;;
    releasewithdebinfo)
        model=releasewithdebinfo
        ;;
    *)
        model=release
	;;
esac

current="$(pwd)"
## rm -rf "$current/build"
mkdir -p "$current/build"
cd "$current/build"



function show_build_failed
{
  echo "*********************************************"
  echo "BUILD FAILED"
  echo "*********************************************"
}

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$model ..
if [[ $? -ne 0 ]]; then
  show_build_failed
  exit 1
fi

cmake --build . --config $model -- -j4
if [[ $? -ne 0 ]]; then
  show_build_failed
  exit 1
fi

stage=$current/stage/bin/$model
artifacts=$current/artifacts/x86_64/$model/bin

mkdir -p $artifacts

$artifacts/server --version
ls -l $artifacts/server
ldd $artifacts/server

# Move files from "cfg" to "stage/cfg".
cp -f -r $current/cfg $stage/cfg/

# Move folder "data" to "stage/data".
cp -f -r $current/data $stage

# Move some files from "stage" to "artifacts".
cp -f $current/stage/bin/$model/server $artifacts

echo "*********************************************"
echo "BUILD SUCCEEDED"
echo "*********************************************"
