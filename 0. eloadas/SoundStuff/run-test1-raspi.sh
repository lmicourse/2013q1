#!/bin/sh
arecord -D plughw:1,0 -r 48000 | bin/SoundTest 48000 1000 1000
