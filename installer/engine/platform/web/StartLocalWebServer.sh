#!/bin/bash

pushd web || exit
  lsof -nti:8002 | xargs kill -9
  python -m SimpleHTTPServer 8002
popd