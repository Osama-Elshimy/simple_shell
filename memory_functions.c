#include "main.h"

/**
 * _memcpy - copy memory area
 *
 * @dest: destination
 * @src: source
 * @n: number of bytes
 *
 * Return: pointer to dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _realloc - reallocate memory block
 *
 * @ptr: pointer to memory block
 * @size: size of new memory block
 *
 * Return: pointer to new memory block
 */

void *_realloc(void *ptr, size_t size)
{
	void *new_ptr;
	size_t old_size, copy_size;

	if (ptr == NULL)
		return (malloc(size));

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(size);

	if (new_ptr == NULL)
		return (NULL);

	old_size = malloc_usable_size(ptr);
	copy_size = (old_size < size) ? old_size : size;
	_memcpy(new_ptr, ptr, copy_size);

	free(ptr);

	return (new_ptr);
}

/**
 * _calloc - allocate memory for an array
 *
 *  @nmemb: number of elements
 *  @size: size of each element
 *
 *  Return: pointer to allocated memory
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *arr;

	if (nmemb == 0 || size == 0)
		return (NULL);

	arr = malloc(nmemb * size);

	if (arr == NULL)
		return (NULL);

	memset(arr, 0, nmemb * size);

	return (arr);
}
