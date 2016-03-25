/*
 * libdpkg - Debian packaging suite library routines
 * ar.c - primitives for ar handling
 *
 * Copyright © 2010 Guillem Jover <guillem@debian.org>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LIBDPKG_AR_H
#define LIBDPKG_AR_H

#include <sys/types.h>

#include <stdbool.h>
#include <ar.h>

#include <dpkg/macros.h>

DPKG_BEGIN_DECLS

/**
 * @defgroup ar Ar archive handling
 * @ingroup dpkg-public
 * @{
 */

#define DPKG_AR_MAGIC "!<arch>\n"

/**
 * In-memory archive member information.
 */
struct dpkg_ar_member {
	struct dpkg_ar_member *next;
	const char *name;
	off_t offset;
	off_t size;
	time_t time;
	mode_t mode;
	uid_t uid;
	gid_t gid;
};

void dpkg_ar_normalize_name(struct ar_hdr *arh);
bool dpkg_ar_member_is_illegal(struct ar_hdr *arh);

void dpkg_ar_put_magic(const char *ar_name, int ar_fd);
void dpkg_ar_member_put_header(const char *ar_name, int ar_fd,
                               struct dpkg_ar_member *member);
void dpkg_ar_member_put_file(const char *ar_name, int ar_fd, const char *name,
                             int fd, off_t size);
void dpkg_ar_member_put_mem(const char *ar_name, int ar_fd, const char *name,
                            const void *data, size_t size);
off_t dpkg_ar_member_get_size(const char *ar_name, struct ar_hdr *arh);

/** @} */

DPKG_END_DECLS

#endif /* LIBDPKG_AR_H */
