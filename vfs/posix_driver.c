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

#include "vfs_driver.h"

static void posix_vfs_init(void)
{
}

static void posix_vfs_deinit()
{
}

bool posix_vfs_translate_path(const char *path, char* target_dir, size_t target_dir_size)
{
   return false;
}

bool posix_vfs_stat_file(const char *path, struct retro_file_info *buffer)
{
   return false; // TODO
}

bool posix_vfs_remove_file(const char *path)
{
   return false; // TODO
}

bool posix_vfs_create_directory(const char *path)
{
   return false; // TODO
}

bool posix_vfs_remove_directory(const char *path)
{
   return false; // TODO
}

bool posix_vfs_list_directory(const char *path, char ***items, unsigned int *item_count)
{
   return false; // TODO
}

struct vfs_driver_t vfs_posix_driver = {
   posix_vfs_init,
   posix_vfs_deinit,
   posix_vfs_translate_path,
   posix_vfs_stat_file,
   posix_vfs_remove_file,
   posix_vfs_create_directory,
   posix_vfs_remove_directory,
   posix_vfs_list_directory,
};
