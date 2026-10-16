#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
mkdir -p build/host
cc -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -DEN_HOST -Ifirmware/src/dsp tests/host/bunka_modes_test.c firmware/src/dsp/amb.c -lm -o build/host/bunka_modes_test
# LeakSanitizer cannot inspect /proc tasks in this managed runner; the DSP uses static buffers.
ASAN_OPTIONS=detect_leaks=0 UBSAN_OPTIONS=halt_on_error=1 build/host/bunka_modes_test
