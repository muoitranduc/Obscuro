/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/*
 * POSIX Standard: 5.6 File Characteristics  <sys/stat.h>
 */

#ifndef  _SYS_STAT_H
#define  _SYS_STAT_H 1

#include <sgx/features.h>

#include <sgx/bits/types.h>    /* For __mode_t and __dev_t.  */

#if defined __USE_XOPEN || defined __USE_XOPEN2K || defined __USE_MISC \
    || defined __USE_ATFILE
# if defined __USE_XOPEN || defined __USE_XOPEN2K
#  define __need_time_t
# endif
# if defined __USE_MISC || defined __USE_ATFILE
#  define __need_timespec
# endif
# include <struct/sgx_time_struct.h>      /* For time_t resp. timespec.  */
#endif

#if defined __USE_XOPEN || defined __USE_XOPEN2K
/* The Single Unix specification says that some more types are
   available here.  */
# ifndef __dev_t_defined
typedef __dev_t dev_t;
#  define __dev_t_defined
# endif

# ifndef __gid_t_defined
typedef __gid_t gid_t;
#  define __gid_t_defined
# endif

# ifndef __ino_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __ino_t ino_t;
#  else
typedef __ino64_t ino_t;
#  endif
#  define __ino_t_defined
# endif

# ifndef __mode_t_defined
typedef __mode_t mode_t;
#  define __mode_t_defined
# endif

# ifndef __nlink_t_defined
typedef __nlink_t nlink_t;
#  define __nlink_t_defined
# endif

# ifndef __off_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
#  else
typedef __off64_t off_t;
#  endif
#  define __off_t_defined
# endif

# ifndef __uid_t_defined
typedef __uid_t uid_t;
#  define __uid_t_defined
# endif
#endif   /* X/Open */

#ifdef __USE_UNIX98
# ifndef __blkcnt_t_defined
#  ifndef __USE_FILE_OFFSET64
typedef __blkcnt_t blkcnt_t;
#  else
typedef __blkcnt64_t blkcnt_t;
#  endif
#  define __blkcnt_t_defined
# endif

# ifndef __blksize_t_defined
typedef __blksize_t blksize_t;
#  define __blksize_t_defined
# endif
#endif   /* Unix98 */

#include <sgx/bits/stat.h>

#if defined __USE_BSD || defined __USE_MISC || defined __USE_XOPEN
# define S_IFMT      __S_IFMT
# define S_IFDIR  __S_IFDIR
# define S_IFCHR  __S_IFCHR
# define S_IFBLK  __S_IFBLK
# define S_IFREG  __S_IFREG
# ifdef __S_IFIFO
#  define S_IFIFO __S_IFIFO
# endif
# ifdef __S_IFLNK
#  define S_IFLNK __S_IFLNK
# endif
# if (defined __USE_BSD || defined __USE_MISC || defined __USE_UNIX98) \
     && defined __S_IFSOCK
#  define S_IFSOCK   __S_IFSOCK
# endif
#endif

/* Test macros for file types.   */

#define  __S_ISTYPE(mode, mask)  (((mode) & __S_IFMT) == (mask))

#define  S_ISDIR(mode)   __S_ISTYPE((mode), __S_IFDIR)
#define  S_ISCHR(mode)   __S_ISTYPE((mode), __S_IFCHR)
#define  S_ISBLK(mode)   __S_ISTYPE((mode), __S_IFBLK)
#define  S_ISREG(mode)   __S_ISTYPE((mode), __S_IFREG)
#ifdef __S_IFIFO
# define S_ISFIFO(mode)  __S_ISTYPE((mode), __S_IFIFO)
#endif
#ifdef __S_IFLNK
# define S_ISLNK(mode)   __S_ISTYPE((mode), __S_IFLNK)
#endif

#if defined __USE_BSD && !defined __S_IFLNK
# define S_ISLNK(mode)  0
#endif

#if (defined __USE_BSD || defined __USE_UNIX98 || defined __USE_XOPEN2K) \
    && defined __S_IFSOCK
# define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)
#elif defined __USE_XOPEN2K
# define S_ISSOCK(mode) 0
#endif

/* These are from POSIX.1b.  If the objects are not implemented using separate
   distinct file types, the macros always will evaluate to zero.  Unlike the
   other S_* macros the following three take a pointer to a `struct stat'
   object as the argument.  */
#ifdef   __USE_POSIX199309
# define S_TYPEISMQ(buf) __S_TYPEISMQ(buf)
# define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
# define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#endif


/* Protection bits.  */

#define  S_ISUID __S_ISUID /* Set user ID on execution.  */
#define  S_ISGID  __S_ISGID   /* Set group ID on execution.  */

#if defined __USE_BSD || defined __USE_MISC || defined __USE_XOPEN
/* Save swapped text after use (sticky bit).  This is pretty well obsolete.  */
# define S_ISVTX  __S_ISVTX
#endif

#define  S_IRUSR  __S_IREAD   /* Read by owner.  */
#define  S_IWUSR  __S_IWRITE  /* Write by owner.  */
#define  S_IXUSR  __S_IEXEC   /* Execute by owner.  */
/* Read, write, and execute by owner.  */
#define  S_IRWXU  (__S_IREAD|__S_IWRITE|__S_IEXEC)

#if defined __USE_MISC && defined __USE_BSD
# define S_IREAD  S_IRUSR
# define S_IWRITE S_IWUSR
# define S_IEXEC  S_IXUSR
#endif

#define  S_IRGRP  (S_IRUSR >> 3) /* Read by group.  */
#define  S_IWGRP  (S_IWUSR >> 3) /* Write by group.  */
#define  S_IXGRP  (S_IXUSR >> 3) /* Execute by group.  */
/* Read, write, and execute by group.  */
#define  S_IRWXG  (S_IRWXU >> 3)

#define  S_IROTH  (S_IRGRP >> 3) /* Read by others.  */
#define  S_IWOTH  (S_IWGRP >> 3) /* Write by others.  */
#define  S_IXOTH  (S_IXGRP >> 3) /* Execute by others.  */
/* Read, write, and execute by others.  */
#define  S_IRWXO  (S_IRWXG >> 3)


#ifdef   __USE_BSD
/* Macros for common mode bit masks.  */
# define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO) /* 0777 */
# define ALLPERMS (S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)/* 07777 */
# define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)/* 0666*/

# define S_BLKSIZE   512   /* Block size for `st_blocks'.  */
#endif


#endif /* sys/stat.h  */
