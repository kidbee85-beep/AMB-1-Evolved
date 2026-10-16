#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p build/host
cc -O2 -ffp-contract=off -DEN_HOST -Ifirmware/src/dsp tests/host/wolf_stress.c firmware/src/dsp/amb.c -lm -o build/host/wolf_stress
build/host/wolf_stress 3600
cc -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -DEN_HOST -Ifirmware/src/dsp tests/host/wolf_stress.c firmware/src/dsp/amb.c -lm -o build/host/wolf_stress_asan
ASAN_OPTIONS=detect_leaks=0 UBSAN_OPTIONS=halt_on_error=1 build/host/wolf_stress_asan 1200
