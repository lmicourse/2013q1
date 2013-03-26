#!/bin/sh
arecord -D plughw:1,0 -r 48000 | bin/SoundStuff 48000 4750 100
