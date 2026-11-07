// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
#include <sys/types.h>
BMW_BEGIN_DECLS
struct _Filet;
typedef struct _Filet FILE;
typedef struct { int64_t _Off; unsigned char _Wstate[8]; } fpos_t;
extern FILE _Stdin, _Stdout, _Stderr;
#define stdin (&_Stdin)
#define stdout (&_Stdout)
#define stderr (&_Stderr)
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define BUFSIZ 1024
#define FILENAME_MAX 255
#define FOPEN_MAX 16
#define L_tmpnam 255
#define TMP_MAX 17576
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
FILE *fopen(const char *,const char *);
FILE *freopen(const char *,const char *,FILE *);
FILE *fdopen(int,const char *);
FILE *tmpfile(void);
int fclose(FILE *);
int fflush(FILE *);
int printf(const char *,...);
int fprintf(FILE *,const char *,...);
int sprintf(char *,const char *,...);
int snprintf(char *,size_t,const char *,...);
int vprintf(const char *,__builtin_va_list);
int vfprintf(FILE *,const char *,__builtin_va_list);
int vsprintf(char *,const char *,__builtin_va_list);
int vsnprintf(char *,size_t,const char *,__builtin_va_list);
int scanf(const char *,...);
int fscanf(FILE *,const char *,...);
int sscanf(const char *,const char *,...);
int vscanf(const char *,__builtin_va_list);
int vfscanf(FILE *,const char *,__builtin_va_list);
int vsscanf(const char *,const char *,__builtin_va_list);
size_t fread(void *,size_t,size_t,FILE *);
size_t fwrite(const void *,size_t,size_t,FILE *);
char *fgets(char *,int,FILE *);
char *gets(char *);
int fputs(const char *,FILE *);
int puts(const char *);
int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int fputc(int,FILE *);
int putc(int,FILE *);
int putchar(int);
int ungetc(int,FILE *);
int fseek(FILE *,long,int);
long ftell(FILE *);
void rewind(FILE *);
int fgetpos(FILE *,fpos_t *);
int fsetpos(FILE *,const fpos_t *);
int feof(FILE *);
int ferror(FILE *);
void clearerr(FILE *);
void perror(const char *);
int fileno(FILE *);
int remove(const char *);
int rename(const char *,const char *);
void setbuf(FILE *,char *);
int setvbuf(FILE *,char *,int,size_t);
char *tmpnam(char *);
FILE *popen(const char *,const char *);
int pclose(FILE *);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::FILE; using ::clearerr; using ::fclose; using ::fdopen; using ::feof; using ::ferror; using ::fflush; using ::fgetc; using ::fgetpos; using ::fgets; using ::fileno; using ::fopen; using ::fpos_t; using ::fprintf; using ::fputc; using ::fputs; using ::fread; using ::freopen; using ::fscanf; using ::fseek; using ::fsetpos; using ::ftell; using ::fwrite; using ::getc; using ::getchar; using ::gets; using ::pclose; using ::perror; using ::popen; using ::printf; using ::putc; using ::putchar; using ::puts; using ::remove; using ::rename; using ::rewind; using ::scanf; using ::setbuf; using ::setvbuf; using ::snprintf; using ::sprintf; using ::sscanf; using ::tmpfile; using ::tmpnam; using ::ungetc; using ::vfprintf; using ::vfscanf; using ::vprintf; using ::vscanf; using ::vsnprintf; using ::vsprintf; using ::vsscanf; }
#endif
