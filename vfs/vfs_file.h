/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2015 - Daniel De Matteis
 * 
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __VFS_FILE__H
#define __VFS_FILE__H

#include <libretro.h>
#include <retro_common_api.h>

RETRO_BEGIN_DECLS

typedef struct vfs_file_t
{
   void *(*open)(const char *path, enum retro_vfs_open_mode mode);
   int64_t (*read)(void *data, uint8_t *buffer, size_t buffer_size);
   int64_t (*write)(void *data, const uint8_t *buffer, size_t buffer_size);
   int64_t (*seek)(void *data, uint64_t position);
   int64_t (*get_file_position)(void *data);
   int64_t (*get_file_size)(void *data);
   int64_t (*resize)(void *data, uint64_t size);
   void (*close)(void *data);
} vfs_file_t;

struct vfs_file_t *init_local_file(void);
struct vfs_file_t *init_retro_file(void);

void *vfs_open_file(const char *path, enum retro_vfs_open_mode mode);

int64_t vfs_read_file(void *data, uint8_t *buffer, size_t buffer_size);

int64_t vfs_write_file(void *data, const uint8_t *buffer, size_t buffer_size);

int64_t vfs_seek_file(void *data, uint64_t position);

int64_t vfs_get_file_position_t(void *data);

int64_t vfs_get_file_size_t(void *data);

int64_t vfs_resize_file(void *data, uint64_t size);

void vfs_close_file(void *data);

RETRO_END_DECLS

#endif
