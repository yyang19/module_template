#ifndef ENV_H
#define ENV_H
#include <stddef.h>

#define SYS_CONTAINER_OF(ptr, type, member) ({\
         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
         (type *)( (char *)__mptr - offsetof(type,member) );})

#endif
