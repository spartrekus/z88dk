


#ifndef _STDIO_H
#define _STDIO_H

#include <stdint.h>

// DATA STRUCTURES

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned int    size_t;
#endif

typedef unsigned long   fpos_t;
typedef struct { unsigned char file[13];} FILE;

#ifndef NULL
#define NULL            ((void*)(0))
#endif

#define _IOFBF          0
#define _IOLBF          1
#define _IONBF          2

#define BUFSIZ          1      // clib does not do high level buffering

#define EOF             (-1)

#define FOPEN_MAX       8      // probably changed by target

#define FILENAME_MAX    128

#define L_tmpnam        8
#define TMP_MAX         16

#ifndef SEEK_SET
#define SEEK_SET        0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR        1
#endif

#ifndef SEEK_END
#define SEEK_END        2
#endif

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

// FUNCTIONS

extern FILE __LIB__ *_fmemopen_(void **bufp,size_t *sizep,char *mode);
extern FILE __LIB__ __CALLEE__ *_fmemopen__callee(void **bufp,size_t *sizep,char *mode);
#define _fmemopen_(a,b,c) _fmemopen__callee(a,b,c)


extern int __LIB__ asprintf(char **ptr,char *format,...);


extern void __LIB__ __FASTCALL__ clearerr(FILE *stream);


extern int __LIB__ __FASTCALL__ fclose(FILE *stream);


extern FILE __LIB__ *fdopen(int fd,const char *mode);
extern FILE __LIB__ __CALLEE__ *fdopen_callee(int fd,const char *mode);
#define fdopen(a,b) fdopen_callee(a,b)


extern int __LIB__ __FASTCALL__ feof(FILE *stream);


extern int __LIB__ __FASTCALL__ ferror(FILE *stream);


extern int __LIB__ __FASTCALL__ fflush(FILE *stream);


extern int __LIB__ __FASTCALL__ fgetc(FILE *stream);


extern int __LIB__ fgetpos(FILE *stream,fpos_t *pos);
extern int __LIB__ __CALLEE__ fgetpos_callee(FILE *stream,fpos_t *pos);
#define fgetpos(a,b) fgetpos_callee(a,b)


extern char __LIB__ *fgets(char *s,int n,FILE *stream);
extern char __LIB__ __CALLEE__ *fgets_callee(char *s,int n,FILE *stream);
#define fgets(a,b,c) fgets_callee(a,b,c)


extern int __LIB__ __FASTCALL__ fileno(FILE *stream);


extern void __LIB__ __FASTCALL__ flockfile(FILE *stream);


extern FILE __LIB__ *fmemopen(void *buf,size_t size,char *mode);
extern FILE __LIB__ __CALLEE__ *fmemopen_callee(void *buf,size_t size,char *mode);
#define fmemopen(a,b,c) fmemopen_callee(a,b,c)


extern FILE __LIB__ *fopen(const char *filename,const char *mode);
extern FILE __LIB__ __CALLEE__ *fopen_callee(const char *filename,const char *mode);
#define fopen(a,b) fopen_callee(a,b)


extern int __LIB__ fprintf(FILE *stream,char *format,...);


extern int __LIB__ fputc(int c,FILE *stream);
extern int __LIB__ __CALLEE__ fputc_callee(int c,FILE *stream);
#define fputc(a,b) fputc_callee(a,b)


extern int __LIB__ fputs(char *s,FILE *stream);
extern int __LIB__ __CALLEE__ fputs_callee(char *s,FILE *stream);
#define fputs(a,b) fputs_callee(a,b)


extern size_t __LIB__ fread(void *ptr,size_t size,size_t nmemb,FILE *stream);
extern size_t __LIB__ __CALLEE__ fread_callee(void *ptr,size_t size,size_t nmemb,FILE *stream);
#define fread(a,b,c,d) fread_callee(a,b,c,d)


extern FILE __LIB__ *freopen(char *filename,char *mode,FILE *stream);
extern FILE __LIB__ __CALLEE__ *freopen_callee(char *filename,char *mode,FILE *stream);
#define freopen(a,b,c) freopen_callee(a,b,c)


extern int __LIB__ fscanf(FILE *stream,char *format,...);


extern int __LIB__ fseek(FILE *stream,long offset,int whence);
extern int __LIB__ __CALLEE__ fseek_callee(FILE *stream,long offset,int whence);
#define fseek(a,b,c) fseek_callee(a,b,c)


extern int __LIB__ fsetpos(FILE *stream,fpos_t *pos);
extern int __LIB__ __CALLEE__ fsetpos_callee(FILE *stream,fpos_t *pos);
#define fsetpos(a,b) fsetpos_callee(a,b)


extern uint32_t __LIB__ __FASTCALL__ ftell(FILE *stream);


extern int __LIB__ __FASTCALL__ ftrylockfile(FILE *stream);


extern void __LIB__ __FASTCALL__ funlockfile(FILE *stream);


extern size_t __LIB__ fwrite(void *ptr,size_t size,size_t nmemb,FILE *stream);
extern size_t __LIB__ __CALLEE__ fwrite_callee(void *ptr,size_t size,size_t nmemb,FILE *stream);
#define fwrite(a,b,c,d) fwrite_callee(a,b,c,d)


extern int __LIB__ __FASTCALL__ getc(FILE *stream);


extern int __LIB__ getchar(void);


extern int __LIB__ getdelim(char **lineptr,size_t *n,int delim,FILE *stream);
extern int __LIB__ __CALLEE__ getdelim_callee(char **lineptr,size_t *n,int delim,FILE *stream);
#define getdelim(a,b,c,d) getdelim_callee(a,b,c,d)


extern int __LIB__ getline(char **lineptr,size_t *n,FILE *stream);
extern int __LIB__ __CALLEE__ getline_callee(char **lineptr,size_t *n,FILE *stream);
#define getline(a,b,c) getline_callee(a,b,c)


extern char __LIB__ __FASTCALL__ gets(char *s);


extern int __LIB__ obstack_printf(struct obstack *ob,char *format,...);


extern int __LIB__ obstack_vprintf(struct obstack *ob,char *format,void *arg);
extern int __LIB__ __CALLEE__ obstack_vprintf_callee(struct obstack *ob,char *format,void *arg);
#define obstack_vprintf(a,b,c) obstack_vprintf_callee(a,b,c)


extern FILE __LIB__ *open_memstream(char **bufp,size_t *sizep);
extern FILE __LIB__ __CALLEE__ *open_memstream_callee(char **bufp,size_t *sizep);
#define open_memstream(a,b) open_memstream_callee(a,b)


extern void __LIB__ __FASTCALL__ perror(char *s);


extern int __LIB__ printf(char *format,...);


extern int __LIB__ putc(int c,FILE *stream);
extern int __LIB__ __CALLEE__ putc_callee(int c,FILE *stream);
#define putc(a,b) putc_callee(a,b)


extern int __LIB__ __FASTCALL__ putchar(int c);


extern int __LIB__ __FASTCALL__ puts(char *s);


extern void __LIB__ __FASTCALL__ rewind(FILE *stream);


extern int __LIB__ scanf(char *format,...);


extern int __LIB__ snprintf(char *s,size_t n,char *format,...);


extern int __LIB__ sprintf(char *s,char *format,...);


extern int __LIB__ sscanf(char *s,char *format,...);


extern int __LIB__ ungetc(int c,FILE *stream);
extern int __LIB__ __CALLEE__ ungetc_callee(int c,FILE *stream);
#define ungetc(a,b) ungetc_callee(a,b)


extern int __LIB__ vasprintf(char **ptr,char *format,void *arg);
extern int __LIB__ __CALLEE__ vasprintf_callee(char **ptr,char *format,void *arg);
#define vasprintf(a,b,c) vasprintf_callee(a,b,c)


extern int __LIB__ vfprintf(FILE *stream,char *format,void *arg);
extern int __LIB__ __CALLEE__ vfprintf_callee(FILE *stream,char *format,void *arg);
#define vfprintf(a,b,c) vfprintf_callee(a,b,c)


extern int __LIB__ vfscanf(FILE *stream,char *format,void *arg);
extern int __LIB__ __CALLEE__ vfscanf_callee(FILE *stream,char *format,void *arg);
#define vfscanf(a,b,c) vfscanf_callee(a,b,c)


extern int __LIB__ vprintf(char *format,void *arg);
extern int __LIB__ __CALLEE__ vprintf_callee(char *format,void *arg);
#define vprintf(a,b) vprintf_callee(a,b)


extern int __LIB__ vscanf(char *format,void *arg);
extern int __LIB__ __CALLEE__ vscanf_callee(char *format,void *arg);
#define vscanf(a,b) vscanf_callee(a,b)


extern int __LIB__ vsnprintf(char *s,size_t n,char *format,void *arg);
extern int __LIB__ __CALLEE__ vsnprintf_callee(char *s,size_t n,char *format,void *arg);
#define vsnprintf(a,b,c,d) vsnprintf_callee(a,b,c,d)


extern int __LIB__ vsprintf(char *s,char *format,void *arg);
extern int __LIB__ __CALLEE__ vsprintf_callee(char *s,char *format,void *arg);
#define vsprintf(a,b,c) vsprintf_callee(a,b,c)


extern int __LIB__ vsscanf(char *s,char *format,void *arg);
extern int __LIB__ __CALLEE__ vsscanf_callee(char *s,char *format,void *arg);
#define vsscanf(a,b,c) vsscanf_callee(a,b,c)



extern void __LIB__ __FASTCALL__ clearerr_unlocked(FILE *stream);


extern int __LIB__ __FASTCALL__ fclose_unlocked(FILE *stream);


extern int __LIB__ __FASTCALL__ feof_unlocked(FILE *stream);


extern int __LIB__ __FASTCALL__ ferror_unlocked(FILE *stream);


extern int __LIB__ __FASTCALL__ fflush_unlocked(FILE *stream);


extern int __LIB__ __FASTCALL__ fgetc_unlocked(FILE *stream);


extern int __LIB__ fgetpos_unlocked(FILE *stream,fpos_t *pos);
extern int __LIB__ __CALLEE__ fgetpos_unlocked_callee(FILE *stream,fpos_t *pos);
#define fgetpos_unlocked(a,b) fgetpos_unlocked_callee(a,b)


extern char __LIB__ *fgets_unlocked(char *s,int n,FILE *stream);
extern char __LIB__ __CALLEE__ *fgets_unlocked_callee(char *s,int n,FILE *stream);
#define fgets_unlocked(a,b,c) fgets_unlocked_callee(a,b,c)


extern int __LIB__ __FASTCALL__ fileno_unlocked(FILE *stream);


extern int __LIB__ fprintf_unlocked(FILE *stream,char *format,...);


extern int __LIB__ fputc_unlocked(int c,FILE *stream);
extern int __LIB__ __CALLEE__ fputc_unlocked_callee(int c,FILE *stream);
#define fputc_unlocked(a,b) fputc_unlocked_callee(a,b)


extern int __LIB__ fputs_unlocked(char *s,FILE *stream);
extern int __LIB__ __CALLEE__ fputs_unlocked_callee(char *s,FILE *stream);
#define fputs_unlocked(a,b) fputs_unlocked_callee(a,b)


extern size_t __LIB__ fread_unlocked(void *ptr,size_t size,size_t nmemb,FILE *stream);
extern size_t __LIB__ __CALLEE__ fread_unlocked_callee(void *ptr,size_t size,size_t nmemb,FILE *stream);
#define fread_unlocked(a,b,c,d) fread_unlocked_callee(a,b,c,d)


extern FILE __LIB__ *freopen_unlocked(char *filename,char *mode,FILE *stream);
extern FILE __LIB__ __CALLEE__ *freopen_unlocked_callee(char *filename,char *mode,FILE *stream);
#define freopen_unlocked(a,b,c) freopen_unlocked_callee(a,b,c)


extern int __LIB__ fscanf_unlocked(FILE *stream,char *format,...);


extern int __LIB__ fseek_unlocked(FILE *stream,long offset,int whence);
extern int __LIB__ __CALLEE__ fseek_unlocked_callee(FILE *stream,long offset,int whence);
#define fseek_unlocked(a,b,c) fseek_unlocked_callee(a,b,c)


extern int __LIB__ fsetpos_unlocked(FILE *stream,fpos_t *pos);
extern int __LIB__ __CALLEE__ fsetpos_unlocked_callee(FILE *stream,fpos_t *pos);
#define fsetpos_unlocked(a,b) fsetpos_unlocked_callee(a,b)


extern uint32_t __LIB__ __FASTCALL__ ftell_unlocked(FILE *stream);


extern size_t __LIB__ fwrite_unlocked(void *ptr,size_t size,size_t nmemb,FILE *stream);
extern size_t __LIB__ __CALLEE__ fwrite_unlocked_callee(void *ptr,size_t size,size_t nmemb,FILE *stream);
#define fwrite_unlocked(a,b,c,d) fwrite_unlocked_callee(a,b,c,d)


extern int __LIB__ __FASTCALL__ getc_unlocked(FILE *stream);


extern int __LIB__ getchar_unlocked(void);


extern int __LIB__ getdelim_unlocked(char **lineptr,size_t *n,int delim,FILE *stream);
extern int __LIB__ __CALLEE__ getdelim_unlocked_callee(char **lineptr,size_t *n,int delim,FILE *stream);
#define getdelim_unlocked(a,b,c,d) getdelim_unlocked_callee(a,b,c,d)


extern int __LIB__ getline_unlocked(char **lineptr,size_t *n,FILE *stream);
extern int __LIB__ __CALLEE__ getline_unlocked_callee(char **lineptr,size_t *n,FILE *stream);
#define getline_unlocked(a,b,c) getline_unlocked_callee(a,b,c)


extern char __LIB__ __FASTCALL__ gets_unlocked(char *s);


extern int __LIB__ printf_unlocked(char *format,...);


extern int __LIB__ putc_unlocked(int c,FILE *stream);
extern int __LIB__ __CALLEE__ putc_unlocked_callee(int c,FILE *stream);
#define putc_unlocked(a,b) putc_unlocked_callee(a,b)


extern int __LIB__ __FASTCALL__ putchar_unlocked(int c);


extern int __LIB__ __FASTCALL__ puts_unlocked(char *s);


extern void __LIB__ __FASTCALL__ rewind_unlocked(FILE *stream);


extern int __LIB__ scanf_unlocked(char *format,...);


extern int __LIB__ ungetc_unlocked(int c,FILE *stream);
extern int __LIB__ __CALLEE__ ungetc_unlocked_callee(int c,FILE *stream);
#define ungetc_unlocked(a,b) ungetc_unlocked_callee(a,b)


extern int __LIB__ vfprintf_unlocked(FILE *stream,char *format,void *arg);
extern int __LIB__ __CALLEE__ vfprintf_unlocked_callee(FILE *stream,char *format,void *arg);
#define vfprintf_unlocked(a,b,c) vfprintf_unlocked_callee(a,b,c)


extern int __LIB__ vfscanf_unlocked(FILE *stream,char *format,void *arg);
extern int __LIB__ __CALLEE__ vfscanf_unlocked_callee(FILE *stream,char *format,void *arg);
#define vfscanf_unlocked(a,b,c) vfscanf_unlocked_callee(a,b,c)


extern int __LIB__ vprintf_unlocked(char *format,void *arg);
extern int __LIB__ __CALLEE__ vprintf_unlocked_callee(char *format,void *arg);
#define vprintf_unlocked(a,b) vprintf_unlocked_callee(a,b)


extern int __LIB__ vscanf_unlocked(char *format,void *arg);
extern int __LIB__ __CALLEE__ vscanf_unlocked_callee(char *format,void *arg);
#define vscanf_unlocked(a,b) vscanf_unlocked_callee(a,b)



#endif
