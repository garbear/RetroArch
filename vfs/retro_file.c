/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2016 - Daniel De Matteis
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

#include "vfs_file.h"

#include <stdlib.h>
#include <string.h>

struct retro_file_data
{
   // TODO
};

void *retro_open_file(const char *path, enum retro_vfs_open_mode mode)
{
   if (!path || strcmp(path, "retro://") != 0)
      return NULL;

   path += strlen("retro://");

   struct retro_file_data *file = (struct retro_file_data*)malloc(sizeof(*file));
   if (file)
      return file;

   return NULL;
}

int64_t retro_read_file(void* data, uint8_t *buffer, size_t buffer_size)
{
   return -1; // TODO
}

int64_t retro_write_file(void* data, const uint8_t *buffer, size_t buffer_size)
{
   return -1; // TODO
}

int64_t retro_seek_file(void* data, uint64_t position)
{
   return -1; // TODO
}

int64_t retro_get_file_position_t(void* data)
{
   return -1; // TODO
}

int64_t retro_get_file_size_t(void* data)
{
   return -1; // TODO
}

int64_t retro_resize_file(void* data, uint64_t size)
{
   return -1; // TODO
}

void retro_close_file(void* data)
{
   struct retro_file_data *file = (struct retro_file_data*)data;
   if (file)
      free(file);
}

struct vfs_file_t *init_retro_file(void)
{
   struct vfs_file_t *file = (struct vfs_file_t*)malloc(sizeof(struct vfs_file_t));
   if (file)
   {
      file->open = retro_open_file;
      file->read = retro_read_file;
      file->write = retro_write_file;
      file->seek = retro_seek_file;
      file->get_file_position = retro_get_file_position_t;
      file->get_file_size = retro_get_file_size_t;
      file->resize = retro_resize_file;
      file->close = retro_close_file;
      return file;
   }

   return NULL;
}
