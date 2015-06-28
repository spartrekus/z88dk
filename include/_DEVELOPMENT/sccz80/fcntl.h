


#ifndef _FCNTL_H
#define _FCNTL_H

typedef unsigned int  mode_t;

#ifndef _OFF_T_DEFINED
#define _OFF_T_DEFINED
typedef unsigned long off_t;
#endif

#define O_CREAT  0x10
#define O_EXCL   0x20
#define O_TRUNC  0x40

#define O_APPEND 0x04
#define O_BINARY 0x08

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR   0x03

#ifndef SEEK_SET
#define SEEK_SET        0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR        1
#endif

#ifndef SEEK_END
#define SEEK_END        2
#endif

extern int __LIB__ creat(char *path,mode_t mode);
extern int __LIB__ __CALLEE__ creat_callee(char *path,mode_t mode);
#define creat(a,b) creat_callee(a,b)


extern int __LIB__ open(char *path,int oflag,...);


extern int __LIB__ vopen(char *path,int oflag,void *arg);
extern int __LIB__ __CALLEE__ vopen_callee(char *path,int oflag,void *arg);
#define vopen(a,b,c) vopen_callee(a,b,c)



#endif
