#!/bin/sh

case $1 in
    "") cmake . ;;
    run) cmake --build . && ./mapmaker ;;
esac ;
