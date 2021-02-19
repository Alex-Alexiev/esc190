#ifndef UTIL_H_
#define UTIL_H_

char *utStringer_int(void *val);

char *utStringer_float(void *val);

char *utStringer_double(void *val);

char *my_strcat(char *dest, char *src);

int my_strcmp_rec(char *str1, char *str2);

int my_atoi(char *str);

#endif