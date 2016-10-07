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
#include "vfs_driver.h"

#include <streams/file_stream.h>

#include <stdlib.h>
#include <string.h>

struct vfs_file_internal
{
   struct vfs_file_t *handle;
   void *data;
};

struct vfs_file_t *init_vfs_file(const char *path)
{
   if (strcmp("file://", path) == 0)
      return init_local_file();

   if (strcmp("retro://", path) == 0)
      return init_retro_file();

   return NULL;
}

void *vfs_open_file(const char *path, enum retro_vfs_open_mode mode)
{
   char translated_path[PATH_MAX];
   if (vfs_translate_path(path, translated_path, sizeof(translated_path)))
      path = translated_path;

   struct vfs_file_internal *file = (struct vfs_file_internal*)malloc(sizeof(*file));
   if (file)
   {
      file->handle = init_vfs_file(path);
      if (file->handle)
      {
         file->data = file->handle->open(path, mode);
         if (file->data)
            return file;

         free(file->handle);
      }
      free(file);
   }

   return NULL;
}

int64_t vfs_read_file(void* data, uint8_t *buffer, size_t buffer_size)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->read(file->data, buffer, buffer_size);

   return -1;
}

int64_t vfs_write_file(void* data, const uint8_t *buffer, size_t buffer_size)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->write(file->data, buffer, buffer_size);

   return -1;
}

int64_t vfs_seek_file(void* data, uint64_t position)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->seek(file->data, position);

   return -1;
}

int64_t vfs_get_file_position_t(void* data)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->get_file_position(file->data);

   return -1;
}

int64_t vfs_get_file_size_t(void* data)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->get_file_size(file->data);

   return -1;
}

int64_t vfs_resize_file(void* data, uint64_t size)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
      return file->handle->resize(file->data, size);

   return -1;
}

void vfs_close_file(void* data)
{
   struct vfs_file_internal *file = (struct vfs_file_internal*)data;
   if (file)
   {
      file->handle->close(file->data);
      free(file->handle);
      free(file);
   }
}
