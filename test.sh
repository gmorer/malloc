DYLD_LIBRARY_PATH=. \
DYLD_INSERT_LIBRARIES=libft_malloc.so \
DYLD_FORCE_FLAT_NAMESPACE=1 \
./../ft_ls/ft_ls -l ; echo $?
