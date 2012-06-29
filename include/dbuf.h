/*
 * IRC - Internet Relay Chat, include/dbuf.h
 * Copyright (C) 1990 Markku Savela
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/** @file
 * @brief Interfaces and declarations for dealing with data buffers.
 * @version $Id$
 */
#ifndef INCLUDED_dbuf_h
#define INCLUDED_dbuf_h
#ifndef INCLUDED_sys_types_h
#include <sys/types.h>          /* size_t */
#define INCLUDED_sys_types_h
#endif

/*
 * These two globals should be considered read only
 */
extern int DBufAllocCount;
extern int DBufUsedCount;

struct DBufBuffer;

/** Queue of data chunks. */
struct DBuf {
  unsigned int length;          /**< Current number of bytes stored */
  struct DBufBuffer *head;      /**< First data buffer, if length > 0 */
  struct DBufBuffer *tail;      /**< Last data buffer, if length > 0 */
};

/** Return number of bytes in a DBuf. */
#define DBufLength(dyn) ((dyn)->length)

/** Release the entire content of a DBuf. */
#define DBufClear(dyn) dbuf_delete((dyn), DBufLength(dyn))

/*
 * Prototypes
 */
extern void dbuf_delete(struct DBuf *dyn, unsigned int length);
extern int dbuf_put(struct DBuf *dyn, const char *buf, unsigned int length);
extern const char *dbuf_map(const struct DBuf *dyn, unsigned int *length);
extern unsigned int dbuf_get(struct DBuf *dyn, char *buf, unsigned int length);
extern unsigned int dbuf_getmsg(struct DBuf *dyn, char *buf, unsigned int length);
extern void dbuf_count_memory(size_t *allocated, size_t *used);


#endif /* INCLUDED_dbuf_h */
