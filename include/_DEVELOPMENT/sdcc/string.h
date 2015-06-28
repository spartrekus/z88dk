


#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned int  size_t;
#endif

#ifndef NULL
#define NULL            ((void*)(0))
#endif

extern int bcmp(void *b1,void *b2,size_t len);
extern int bcmp_callee(void *b1,void *b2,size_t len) __z88dk_callee;
#define bcmp(a,b,c) bcmp_callee(a,b,c)


extern void bcopy(const void *src,void *dst,size_t len);
extern void bcopy_callee(const void *src,void *dst,size_t len) __z88dk_callee;
#define bcopy(a,b,c) bcopy_callee(a,b,c)


extern void bzero(void *mem,size_t n);
extern void bzero_callee(void *mem,size_t n) __z88dk_callee;
#define bzero(a,b) bzero_callee(a,b)


extern char *index(char *s,int c);
extern char *index_callee(char *s,int c) __z88dk_callee;
#define index(a,b) index_callee(a,b)


extern char *rindex(char *s,int c);
extern char *rindex_callee(char *s,int c) __z88dk_callee;
#define rindex(a,b) rindex_callee(a,b)


extern char *strset(char *s,int c);
extern char *strset_callee(char *s,int c) __z88dk_callee;
#define strset(a,b) strset_callee(a,b)


extern char *strnset(char *s,int c,size_t n);
extern char *strnset_callee(char *s,int c,size_t n) __z88dk_callee;
#define strnset(a,b,c) strnset_callee(a,b,c)


extern void *rawmemchr(const void *mem,int c);
extern void *rawmemchr_callee(const void *mem,int c) __z88dk_callee;
#define rawmemchr(a,b) rawmemchr_callee(a,b)



extern char *_memlwr_(void *p,size_t n);
extern char *_memlwr__callee(void *p,size_t n) __z88dk_callee;
#define _memlwr_(a,b) _memlwr__callee(a,b)


extern char *_memstrcpy_(void *p,char *s,size_t n);
extern char *_memstrcpy__callee(void *p,char *s,size_t n) __z88dk_callee;
#define _memstrcpy_(a,b,c) _memstrcpy__callee(a,b,c)


extern char *_memupr_(void *p,size_t n);
extern char *_memupr__callee(void *p,size_t n) __z88dk_callee;
#define _memupr_(a,b) _memupr__callee(a,b)


extern char *_strrstrip_(char *s);
extern char *_strrstrip__fastcall(char *s) __z88dk_fastcall;
#define _strrstrip_(a) _strrstrip__fastcall(a)


extern int ffs(int i);
extern int ffs_fastcall(int i) __z88dk_fastcall;
#define ffs(a) ffs_fastcall(a)


extern int ffsl(long i);
extern int ffsl_fastcall(long i) __z88dk_fastcall;
#define ffsl(a) ffsl_fastcall(a)


extern void *memccpy(void *dst,void *src,int c,size_t n);
extern void *memccpy_callee(void *dst,void *src,int c,size_t n) __z88dk_callee;
#define memccpy(a,b,c,d) memccpy_callee(a,b,c,d)


extern void *memchr(void *s,int c,size_t n);
extern void *memchr_callee(void *s,int c,size_t n) __z88dk_callee;
#define memchr(a,b,c) memchr_callee(a,b,c)


extern int memcmp(void *s1,void *s2,size_t n);
extern int memcmp_callee(void *s1,void *s2,size_t n) __z88dk_callee;
#define memcmp(a,b,c) memcmp_callee(a,b,c)


extern void *memcpy(void *dst,void *src,size_t n);
extern void *memcpy_callee(void *dst,void *src,size_t n) __z88dk_callee;
#define memcpy(a,b,c) memcpy_callee(a,b,c)


extern void *memmem(void *haystack,size_t haystack_len,void *needle,size_t needle_len);
extern void *memmem_callee(void *haystack,size_t haystack_len,void *needle,size_t needle_len) __z88dk_callee;
#define memmem(a,b,c,d) memmem_callee(a,b,c,d)


extern void *memmove(void *dst,void *src,size_t n);
extern void *memmove_callee(void *dst,void *src,size_t n) __z88dk_callee;
#define memmove(a,b,c) memmove_callee(a,b,c)


extern void *memrchr(void *s,int c,size_t n);
extern void *memrchr_callee(void *s,int c,size_t n) __z88dk_callee;
#define memrchr(a,b,c) memrchr_callee(a,b,c)


extern void *memset(void *s,int c,size_t n);
extern void *memset_callee(void *s,int c,size_t n) __z88dk_callee;
#define memset(a,b,c) memset_callee(a,b,c)


extern void *memswap(void *s1,void *s2,size_t n);
extern void *memswap_callee(void *s1,void *s2,size_t n) __z88dk_callee;
#define memswap(a,b,c) memswap_callee(a,b,c)


extern char *stpcpy(char *dst,char *src);
extern char *stpcpy_callee(char *dst,char *src) __z88dk_callee;
#define stpcpy(a,b) stpcpy_callee(a,b)


extern char *stpncpy(char *dst,char *src,size_t n);
extern char *stpncpy_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define stpncpy(a,b,c) stpncpy_callee(a,b,c)


extern int strcasecmp(char *s1,char *s2);
extern int strcasecmp_callee(char *s1,char *s2) __z88dk_callee;
#define strcasecmp(a,b) strcasecmp_callee(a,b)


extern char *strcat(char *dst,char *src);
extern char *strcat_callee(char *dst,char *src) __z88dk_callee;
#define strcat(a,b) strcat_callee(a,b)


extern char *strchr(char *s,int c);
extern char *strchr_callee(char *s,int c) __z88dk_callee;
#define strchr(a,b) strchr_callee(a,b)


extern char *strchrnul(char *s,int c);
extern char *strchrnul_callee(char *s,int c) __z88dk_callee;
#define strchrnul(a,b) strchrnul_callee(a,b)


extern int strcmp(char *s1,char *s2);
extern int strcmp_callee(char *s1,char *s2) __z88dk_callee;
#define strcmp(a,b) strcmp_callee(a,b)


extern int strcoll(char *s1,char *s2);
extern int strcoll_callee(char *s1,char *s2) __z88dk_callee;
#define strcoll(a,b) strcoll_callee(a,b)


extern char *strcpy(char *dst,char *src);
extern char *strcpy_callee(char *dst,char *src) __z88dk_callee;
#define strcpy(a,b) strcpy_callee(a,b)


extern size_t strcspn(char *s,char *nspn);
extern size_t strcspn_callee(char *s,char *nspn) __z88dk_callee;
#define strcspn(a,b) strcspn_callee(a,b)


extern char *strdup(char *s);
extern char *strdup_fastcall(char *s) __z88dk_fastcall;
#define strdup(a) strdup_fastcall(a)


extern char *strerror(int errnum);
extern char *strerror_fastcall(int errnum) __z88dk_fastcall;
#define strerror(a) strerror_fastcall(a)


extern int stricmp(char *s1,char *s2);
extern int stricmp_callee(char *s1,char *s2) __z88dk_callee;
#define stricmp(a,b) stricmp_callee(a,b)


extern size_t strlcat(char *dst,char *src,size_t n);
extern size_t strlcat_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define strlcat(a,b,c) strlcat_callee(a,b,c)


extern size_t strlcpy(char *dst,char *src,size_t n);
extern size_t strlcpy_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define strlcpy(a,b,c) strlcpy_callee(a,b,c)


extern size_t strlen(char *s);
extern size_t strlen_fastcall(char *s) __z88dk_fastcall;
#define strlen(a) strlen_fastcall(a)


extern char strlwr(char *s);
extern char strlwr_fastcall(char *s) __z88dk_fastcall;
#define strlwr(a) strlwr_fastcall(a)


extern int strncasecmp(char *s1,char *s2,size_t n);
extern int strncasecmp_callee(char *s1,char *s2,size_t n) __z88dk_callee;
#define strncasecmp(a,b,c) strncasecmp_callee(a,b,c)


extern char *strncat(char *dst,char *src,size_t n);
extern char *strncat_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define strncat(a,b,c) strncat_callee(a,b,c)


extern char *strnchr(char *s,size_t n,int c);
extern char *strnchr_callee(char *s,size_t n,int c) __z88dk_callee;
#define strnchr(a,b,c) strnchr_callee(a,b,c)


extern int strncmp(char *s1,char *s2,size_t n);
extern int strncmp_callee(char *s1,char *s2,size_t n) __z88dk_callee;
#define strncmp(a,b,c) strncmp_callee(a,b,c)


extern char *strncpy(char *dst,char *src,size_t n);
extern char *strncpy_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define strncpy(a,b,c) strncpy_callee(a,b,c)


extern char *strndup(char *s,size_t n);
extern char *strndup_callee(char *s,size_t n) __z88dk_callee;
#define strndup(a,b) strndup_callee(a,b)


extern int strnicmp(char *s1,char *s2,size_t n);
extern int strnicmp_callee(char *s1,char *s2,size_t n) __z88dk_callee;
#define strnicmp(a,b,c) strnicmp_callee(a,b,c)


extern size_t strnlen(char *s,size_t max_len);
extern size_t strnlen_callee(char *s,size_t max_len) __z88dk_callee;
#define strnlen(a,b) strnlen_callee(a,b)


extern char strpbrk(char *s,char *set);
extern char strpbrk_callee(char *s,char *set) __z88dk_callee;
#define strpbrk(a,b) strpbrk_callee(a,b)


extern char *strrchr(char *s,int c);
extern char *strrchr_callee(char *s,int c) __z88dk_callee;
#define strrchr(a,b) strrchr_callee(a,b)


extern size_t strrcspn(char *s,char *set);
extern size_t strrcspn_callee(char *s,char *set) __z88dk_callee;
#define strrcspn(a,b) strrcspn_callee(a,b)


extern char *strrev(char *s);
extern char *strrev_fastcall(char *s) __z88dk_fastcall;
#define strrev(a) strrev_fastcall(a)


extern size_t strrspn(char *s,char *set);
extern size_t strrspn_callee(char *s,char *set) __z88dk_callee;
#define strrspn(a,b) strrspn_callee(a,b)


extern char *strrstrip(char *s);
extern char *strrstrip_fastcall(char *s) __z88dk_fastcall;
#define strrstrip(a) strrstrip_fastcall(a)


extern char *strsep(char **s,char *delim);
extern char *strsep_callee(char **s,char *delim) __z88dk_callee;
#define strsep(a,b) strsep_callee(a,b)


extern size_t strspn(char *s,char *pfx);
extern size_t strspn_callee(char *s,char *pfx) __z88dk_callee;
#define strspn(a,b) strspn_callee(a,b)


extern char *strstr(char *s,char *subs);
extern char *strstr_callee(char *s,char *subs) __z88dk_callee;
#define strstr(a,b) strstr_callee(a,b)


extern char *strstrip(char *s);
extern char *strstrip_fastcall(char *s) __z88dk_fastcall;
#define strstrip(a) strstrip_fastcall(a)


extern char *strtok(char *s,char *delim);
extern char *strtok_callee(char *s,char *delim) __z88dk_callee;
#define strtok(a,b) strtok_callee(a,b)


extern char *strtok_r(char *s,char *delim,char **last_s);
extern char *strtok_r_callee(char *s,char *delim,char **last_s) __z88dk_callee;
#define strtok_r(a,b,c) strtok_r_callee(a,b,c)


extern char strupr(char *s);
extern char strupr_fastcall(char *s) __z88dk_fastcall;
#define strupr(a) strupr_fastcall(a)


extern size_t strxfrm(char *dst,char *src,size_t n);
extern size_t strxfrm_callee(char *dst,char *src,size_t n) __z88dk_callee;
#define strxfrm(a,b,c) strxfrm_callee(a,b,c)



#ifdef __SDCC

   #ifndef __SDCC_DISABLE_BUILTIN

   #undef memcpy
   #undef strcpy
   #undef strncpy
   #undef strchr
   #undef memset

   #define memcpy(dst, src, n)          __builtin_memcpy(dst, src, n)
   #define strcpy(dst, src)             __builtin_strcpy(dst, src)
   #define strncpy(dst, src, n)         __builtin_strncpy(dst, src, n)
   #define strchr(s, c)                 __builtin_strchr(s, c)
   #define memset(dst, c, n)            __builtin_memset(dst, c, n)

   #endif

#endif

#endif
