#include "shell.h"
int calculateStringLength(const char *s);
char *copyString(char *dest, const char *src);
char *concatenateStrings(char *dest, const char *src);
char *concatenateStringsWithLength(char *dest, const char *src, size_t n);
/**
* calculateStringLength - Returns the length of a string.
* @s: A pointer to the characters string.
* Return: The length of the character string.
*/
int calculateStringLength(const char *s)
{
int length = 0;
if (!s)
for (length = 0; s[length], length++);
return (length);
}
/**
* copyString - Copies the string pointed to by src, including the
* terminating null byte, to the buffer pointed by des.
* @dest: Pointer to the destination of copied string.
* @src: Pointer to the src of the source string.
* Return: Pointer to dest.
*/
char *copyString(char *dest, const char *src)
{
size_t i;
for (i = 0; src[i] != '\0'; i++)
dest[i] = src[i];
dest[i] = '\0';
return (dest);
}
/**
* concatenateStrings - Concantenates two strings.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
* Return: Pointer to destination string.
*/
char *concatenateStrings(char *dest, const char *src)
{
char *destTemp;
const char *srcTemp;
destTemp = dest;
srcTemp =  src;
while (*destTemp != '\0')
destTemp++;
while (*srcTemp != '\0')
*destTemp++ = *srcTemp++;
*destTemp = '\0';
return (dest);
}
/**
* concatenateStringsWithLength - Concantenates two strings where n number
* of bytes are copied from source.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
* @n: n bytes to copy from src.
* Return: Pointer to destination string.
*/
char *concatenateStringsWithLength(char *dest, const char *src, size_t n)
{
size_t dest_len = calculateStringLength(dest);
size_t i;
for (i = 0; i < n && src[i] != '\0'; i++)
dest[dest_len + i] = src[i];
dest[dest_len + i] = '\0';
return (dest);
}
