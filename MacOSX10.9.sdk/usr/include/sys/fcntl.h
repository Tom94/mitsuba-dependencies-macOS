/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*-
 * Copyright (c) 1983, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)fcntl.h	8.3 (Berkeley) 1/21/94
 */


#ifndef _SYS_FCNTL_H_
#define	_SYS_FCNTL_H_

/*
 * This file includes the definitions for open and fcntl
 * described by POSIX for <fcntl.h>; it also includes
 * related kernel definitions.
 */
#include <sys/_types.h>
#include <sys/cdefs.h>
#include <Availability.h>

/* We should not be exporting size_t here.  Temporary for gcc bootstrapping. */
#include <sys/_types/_size_t.h>
#include <sys/_types/_mode_t.h>
#include <sys/_types/_off_t.h>
#include <sys/_types/_pid_t.h>

/*
 * File status flags: these are used by open(2), fcntl(2).
 * They are also used (indirectly) in the kernel file structure f_flags,
 * which is a superset of the open/fcntl flags.  Open flags and f_flags
 * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
 * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
 */
/* open-only flags */
#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */

/*
 * Kernel encoding of open mode; separate read and write bits that are
 * independently testable: 1 greater than the above.
 *
 * XXX
 * FREAD and FWRITE are excluded from the #ifdef KERNEL so that TIOCFLUSH,
 * which was documented to use FREAD/FWRITE, continues to work.
 */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define	FREAD		0x0001
#define	FWRITE		0x0002
#endif
#define	O_NONBLOCK	0x0004		/* no delay */
#define	O_APPEND	0x0008		/* set append mode */

#include <sys/_types/_o_sync.h>

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define	O_SHLOCK	0x0010		/* open with shared file lock */
#define	O_EXLOCK	0x0020		/* open with exclusive file lock */
#define	O_ASYNC		0x0040		/* signal pgrp when data ready */
#define	O_FSYNC		O_SYNC		/* source compatibility: do not use */
#define O_NOFOLLOW  0x0100      /* don't follow symlinks */
#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */
#define	O_CREAT		0x0200		/* create if nonexistant */
#define	O_TRUNC		0x0400		/* truncate to zero length */
#define	O_EXCL		0x0800		/* error if already exists */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define	O_EVTONLY	0x8000		/* descriptor requested for event notifications only */
#endif


#define	O_NOCTTY	0x20000		/* don't assign controlling terminal */


#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define O_DIRECTORY	0x100000
#define O_SYMLINK	0x200000	/* allow open of a symlink */
#endif

#include <sys/_types/_o_dsync.h>


#if __DARWIN_C_LEVEL >= 200809L
#define	O_CLOEXEC	0x1000000	/* implicitly set FD_CLOEXEC */
#endif




/* Data Protection Flags */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define O_DP_GETRAWENCRYPTED	0x0001
#endif



/*
 * The O_* flags used to have only F* names, which were used in the kernel
 * and by fcntl.  We retain the F* names for the kernel f_flags field
 * and for backward compatibility for fcntl.
 */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define	FAPPEND		O_APPEND	/* kernel/compat */
#define	FASYNC		O_ASYNC		/* kernel/compat */
#define	FFSYNC		O_FSYNC		/* kernel */
#define	FFDSYNC		O_DSYNC		/* kernel */
#define	FNONBLOCK	O_NONBLOCK	/* kernel */
#define	FNDELAY		O_NONBLOCK	/* compat */
#define	O_NDELAY	O_NONBLOCK	/* compat */
#endif

/*
 * Flags used for copyfile(2)
 */

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define CPF_OVERWRITE 1
#define CPF_IGNORE_MODE 2
#define CPF_MASK (CPF_OVERWRITE|CPF_IGNORE_MODE)
#endif

/*
 * Constants used for fcntl(2)
 */

/* command values */
#define	F_DUPFD		0		/* duplicate file descriptor */
#define	F_GETFD		1		/* get file descriptor flags */
#define	F_SETFD		2		/* set file descriptor flags */
#define	F_GETFL		3		/* get file status flags */
#define	F_SETFL		4		/* set file status flags */
#define	F_GETOWN	5		/* get SIGIO/SIGURG proc/pgrp */
#define F_SETOWN	6		/* set SIGIO/SIGURG proc/pgrp */
#define	F_GETLK		7		/* get record locking information */
#define	F_SETLK		8		/* set record locking information */
#define	F_SETLKW	9		/* F_SETLK; wait if blocked */
#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
#define F_SETLKWTIMEOUT 10		/* F_SETLK; wait if blocked, return on timeout */
#endif /* __DARWIN_C_LEVEL >= __DARWIN_C_FULL */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define F_FLUSH_DATA    40
#define F_CHKCLEAN      41              /* Used for regression test */
#define F_PREALLOCATE   42		/* Preallocate storage */
#define F_SETSIZE       43		/* Truncate a file without zeroing space */	
#define F_RDADVISE      44              /* Issue an advisory read async with no copy to user */
#define F_RDAHEAD       45              /* turn read ahead off/on for this fd */
/*
 * 46,47 used to be F_READBOOTSTRAP and F_WRITEBOOTSTRAP 
 */
#define F_NOCACHE       48              /* turn data caching off/on for this fd */
#define F_LOG2PHYS	49		/* file offset to device offset */
#define F_GETPATH       50              /* return the full path of the fd */
#define F_FULLFSYNC     51		/* fsync + ask the drive to flush to the media */
#define F_PATHPKG_CHECK 52              /* find which component (if any) is a package */
#define F_FREEZE_FS     53              /* "freeze" all fs operations */
#define F_THAW_FS       54              /* "thaw" all fs operations */
#define	F_GLOBAL_NOCACHE 55		/* turn data caching off/on (globally) for this file */


#define F_ADDSIGS	59		/* add detached signatures */


#define F_ADDFILESIGS	61		/* add signature from same file (used by dyld for shared libs) */

#define F_NODIRECT	62		/* used in conjunction with F_NOCACHE to indicate that DIRECT, synchonous writes */
                                        /* should not be used (i.e. its ok to temporaily create cached pages) */

#define F_GETPROTECTIONCLASS	63		/* Get the protection class of a file from the EA, returns int */
#define F_SETPROTECTIONCLASS	64		/* Set the protection class of a file for the EA, requires int */

#define F_LOG2PHYS_EXT  65		/* file offset to device offset, extended */

#define	F_GETLKPID		66		/* get record locking information, per-process */

/* See F_DUPFD_CLOEXEC below for 67 */


#define F_SETBACKINGSTORE	70	/* Mark the file as being the backing store for another filesystem */
#define F_GETPATH_MTMINFO	71 	/* return the full path of the FD, but error in specific mtmd circumstances */

/* 72 is free.  It used to be F_GETENCRYPTEDDATA, which is now removed. */

#define F_SETNOSIGPIPE		73	/* No SIGPIPE generated on EPIPE */
#define F_GETNOSIGPIPE		74	/* Status of SIGPIPE for this fd */

#define F_TRANSCODEKEY		75 	/* For some cases, we need to rewrap the key for AKS/MKB */

#define F_SINGLE_WRITER		76	/* file being written to a by single writer... if throttling enabled, writes */
                                        /* may be broken into smaller chunks with throttling in between */

#define F_GETPROTECTIONLEVEL	77	/* Get the protection version number for this filesystem */

#define F_FINDSIGS		78	/* Add detached code signatures (used by dyld for shared libs) */



// FS-specific fcntl()'s numbers begin at 0x00010000 and go up
#define FCNTL_FS_SPECIFIC_BASE  0x00010000

#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */

#if __DARWIN_C_LEVEL >= 200809L
#define	F_DUPFD_CLOEXEC		67	/* mark the dup with FD_CLOEXEC */
#endif

/* file descriptor flags (F_GETFD, F_SETFD) */
#define	FD_CLOEXEC	1		/* close-on-exec flag */

/* record locking flags (F_GETLK, F_SETLK, F_SETLKW) */
#define	F_RDLCK		1		/* shared or read lock */
#define	F_UNLCK		2		/* unlock */
#define	F_WRLCK		3		/* exclusive or write lock */

/*
 * [XSI] The values used for l_whence shall be defined as described
 * in <unistd.h>
 */
#include <sys/_types/_seek_set.h>

/*
 * [XSI] The symbolic names for file modes for use as values of mode_t
 * shall be defined as described in <sys/stat.h>
 */
#include <sys/_types/_s_ifmt.h>

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
/* allocate flags (F_PREALLOCATE) */

#define F_ALLOCATECONTIG  0x00000002    /* allocate contigious space */
#define F_ALLOCATEALL     0x00000004	/* allocate all requested space or no space at all */

/* Position Modes (fst_posmode) for F_PREALLOCATE */

#define F_PEOFPOSMODE 3			/* Make it past all of the SEEK pos modes so that */
					/* we can keep them in sync should we desire */	
#define F_VOLPOSMODE	4		/* specify volume starting postion */
#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */

/*
 * Advisory file segment locking data type -
 * information passed to system by user
 */
struct flock {
	off_t	l_start;	/* starting offset */
	off_t	l_len;		/* len = 0 means until end of file */
	pid_t	l_pid;		/* lock owner */
	short	l_type;		/* lock type: read/write, etc. */
	short	l_whence;	/* type of l_start */
};

#include <sys/_types/_timespec.h>

#if __DARWIN_C_LEVEL >= __DARWIN_C_FULL
/*
 * Advisory file segment locking with time out -
 * Information passed to system by user for F_SETLKWTIMEOUT
 */
struct flocktimeout {
	struct flock    fl;             /* flock passed for file locking */
	struct timespec timeout;        /* timespec struct for timeout */
};
#endif /* __DARWIN_C_LEVEL >= __DARWIN_C_FULL */

#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
/*
 * advisory file read data type -
 * information passed by user to system
 */


struct radvisory {
       off_t   ra_offset;
       int     ra_count;
};


/*
 * detached code signatures data type -
 * information passed by user to system used by F_ADDSIGS and F_ADDFILESIGS.
 * F_ADDFILESIGS is a shortcut for files that contain their own signature and
 * doesn't require mapping of the file in order to load the signature.
 */
typedef struct fsignatures {
	off_t		fs_file_start;
	void		*fs_blob_start;
	size_t		fs_blob_size;
} fsignatures_t;

/* lock operations for flock(2) */
#define	LOCK_SH		0x01		/* shared file lock */
#define	LOCK_EX		0x02		/* exclusive file lock */
#define	LOCK_NB		0x04		/* don't block when locking */
#define	LOCK_UN		0x08		/* unlock file */

/*  fstore_t type used by F_DEALLOCATE and F_PREALLOCATE commands */

typedef struct fstore {
	unsigned int fst_flags;	/* IN: flags word */
	int 	fst_posmode;	/* IN: indicates use of offset field */
	off_t	fst_offset;	/* IN: start of the region */
	off_t	fst_length;	/* IN: size of the region */
	off_t   fst_bytesalloc;	/* OUT: number of bytes allocated */
} fstore_t;

/* fbootstraptransfer_t used by F_READBOOTSTRAP and F_WRITEBOOTSTRAP commands */

typedef struct fbootstraptransfer {
  off_t fbt_offset;             /* IN: offset to start read/write */
  size_t fbt_length;          /* IN: number of bytes to transfer */
  void *fbt_buffer;             /* IN: buffer to be read/written */
} fbootstraptransfer_t;


/*
 * For F_LOG2PHYS this information is passed back to user
 * Currently only devoffset is returned - that is the VOP_BMAP
 * result - the disk device address corresponding to the
 * current file offset (likely set with an lseek).
 *
 * The flags could hold an indication of whether the # of 
 * contiguous bytes reflects the true extent length on disk,
 * or is an advisory value that indicates there is at least that
 * many bytes contiguous.  For some filesystems it might be too
 * inefficient to provide anything beyond the advisory value.
 * Flags and contiguous bytes return values are not yet implemented.
 * For them the fcntl will nedd to switch from using BMAP to CMAP
 * and a per filesystem type flag will be needed to interpret the
 * contiguous bytes count result from CMAP.
 *
 * F_LOG2PHYS_EXT is a variant of F_LOG2PHYS that uses a passed in
 * file offset and length instead of the current file offset.
 * F_LOG2PHYS_EXT operates on the same structure as F_LOG2PHYS, but
 * treats it as an in/out.
 */
#pragma pack(4)

struct log2phys {
	unsigned int	l2p_flags;	 /* unused so far */
	off_t		l2p_contigbytes; /* F_LOG2PHYS:     unused so far */
					 /* F_LOG2PHYS_EXT: IN:  number of bytes to be queried */
					 /*                 OUT: number of contiguous bytes at this position */
	off_t		l2p_devoffset;   /* F_LOG2PHYS:     OUT: bytes into device */
					 /* F_LOG2PHYS_EXT: IN:  bytes into file */
					 /*                 OUT: bytes into device */
};

#pragma pack()

#define	O_POPUP	   0x80000000   /* force window to popup on open */
#define	O_ALERT	   0x20000000	/* small, clean popup window */


#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */


#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)

#include <sys/_types/_filesec_t.h>

typedef enum {
	FILESEC_OWNER = 1,
	FILESEC_GROUP = 2,
	FILESEC_UUID = 3,
	FILESEC_MODE = 4,
	FILESEC_ACL = 5,
	FILESEC_GRPUUID = 6,

/* XXX these are private to the implementation */
	FILESEC_ACL_RAW = 100,
	FILESEC_ACL_ALLOCSIZE = 101
} filesec_property_t;

/* XXX backwards compatibility */
#define FILESEC_GUID FILESEC_UUID
#endif /* (_POSIX_C_SOURCE && !_DARWIN_C_SOURCE) */

__BEGIN_DECLS
int	open(const char *, int, ...) __DARWIN_ALIAS_C(open);
int	creat(const char *, mode_t) __DARWIN_ALIAS_C(creat);
int	fcntl(int, int, ...) __DARWIN_ALIAS_C(fcntl);
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)

int	openx_np(const char *, int, filesec_t);
/* data-protected non-portable open(2) */
int open_dprotected_np ( const char *, int, int, int, ...);
int	flock(int, int);
filesec_t filesec_init(void);
filesec_t filesec_dup(filesec_t);
void	filesec_free(filesec_t);
int	filesec_get_property(filesec_t, filesec_property_t, void *);
int	filesec_query_property(filesec_t, filesec_property_t, int *);
int	filesec_set_property(filesec_t, filesec_property_t, const void *);
int	filesec_unset_property(filesec_t, filesec_property_t) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#define _FILESEC_UNSET_PROPERTY	((void *)0)
#define _FILESEC_REMOVE_ACL	((void *)1)
#endif /* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
__END_DECLS

#endif /* !_SYS_FCNTL_H_ */
