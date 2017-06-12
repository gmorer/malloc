#!/bin/sh
export DYLD_LIBRARY_PATH="/Users/gmorer/malloc"
export DYLD_INSERT_LIBRARIES="/Users/gmorer/malloc/libft_malloc.so"
export DYLD_FORCE_FLAT_NAMESPACE="1"
$@
