#!/bin/sh

cc -o run in.c `pkg-config --cflags --libs hyperdex-client`
cc -o check check.c `pkg-config --cflags --libs hyperdex-client`
