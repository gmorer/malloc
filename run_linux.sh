#!/bin/sh
LD_PRELOAD=libft_malloc.so \
LD_LIBRARY_PATH=. test/test \
$@
