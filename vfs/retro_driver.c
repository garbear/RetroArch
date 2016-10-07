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
#include "config.h"
#include "configuration.h"
#include "dirs.h"
#include "paths.h"
#include "verbosity.h"

#include <compat/strl.h>
#include <string/stdstring.h>

#include <string.h>

#ifndef MIN
#  define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

char retro_assets_dir[PATH_MAX] = { };
char retro_core_dir[PATH_MAX] = { };
char retro_game_dir[PATH_MAX] = { };
char retro_save_dir[PATH_MAX] = { };
char retro_system_dir[PATH_MAX] = { };

/* TODO: move to URL-parsing module */
bool get_hostname(const char *url, char *hostname, size_t hostname_max_size)
{
   if (hostname_max_size == 0)
      return false;

   const char *scheme_separator = strchr(url, ':');
   if (!scheme_separator)
      return false;

   const char *hostname_start = scheme_separator + 1;
   while (*hostname_start == '/' && *hostname_start != '\0')
   {
      /* Don't proceed past two slashes */
      if (hostname_start - scheme_separator >= 2)
         break;

      hostname_start++;
   }

   const char *hostname_end = hostname_start;
   while (*hostname_end != '/' && *hostname_end != '\0')
      hostname_end++;

   unsigned int hostname_length = hostname_end - hostname_start;

   strlcpy(hostname, hostname_start, MIN(hostname_length, hostname_max_size - 1));

   return true;
}

static void retro_vfs_init(void)
{
   settings_t *settings = config_get_ptr();

   /* asset */
   if (!string_is_empty(settings->directory.core_assets))
      strlcpy(retro_assets_dir, settings->directory.core_assets, sizeof(retro_assets_dir) - 1);

   /* core */
#ifdef HAVE_DYNAMIC
   strlcpy(retro_assets_dir, path_get(RARCH_PATH_CORE), sizeof(retro_assets_dir) - 1);
   // TODO: Remove basename
#endif

   /* game */
   retro_game_dir[0] = '\0'; // TODO

   /* save */
   strlcpy(retro_save_dir, dir_get(RARCH_DIR_CURRENT_SAVEFILE), sizeof(retro_save_dir) - 1);

   /* system */
   if (!string_is_empty(settings->directory.system))
      strlcpy(retro_system_dir, dir_get(RARCH_DIR_SYSTEM), sizeof(retro_system_dir) - 1);

   RARCH_LOG("retro://assets/ mapped to \"%s\"\n", retro_assets_dir);
   RARCH_LOG("retro://game/ mapped to \"%s\"\n", retro_game_dir);
   RARCH_LOG("retro://save/ mapped to \"%s\"\n", retro_save_dir);
   RARCH_LOG("retro://system/ mapped to \"%s\"\n", retro_system_dir);
}

static void retro_vfs_deinit()
{
}

bool retro_vfs_translate_path(const char *path, char* target_dir, size_t target_dir_size)
{
   if (!path || strcmp(path, "retro://") != 0)
      return false;

   char hostname[16];
   if (get_hostname(path, hostname, sizeof(hostname)))
   {
      if (strcmp(hostname, "assets") == 0)
         strlcpy(target_dir, retro_assets_dir, target_dir_size - 1);

      else if (strcmp(hostname, "core") == 0)
         strlcpy(target_dir, retro_core_dir, target_dir_size - 1);

      else if (strcmp(hostname, "game") == 0)
         strlcpy(target_dir, retro_game_dir, target_dir_size - 1);

      else if (strcmp(hostname, "save") == 0)
         strlcpy(target_dir, retro_save_dir, target_dir_size - 1);

      else if (strcmp(hostname, "system") == 0)
         strlcpy(target_dir, retro_system_dir, target_dir_size - 1);
   }

   if (*target_dir == '\0')
      return false;

   /* Append remaining path */
   const char *remaining_path = path + strlen("retro://") + strlen(hostname);
   if (*remaining_path == '/')
      remaining_path++;

   strlcpy(target_dir + strlen(target_dir), remaining_path, target_dir_size - strlen(path));

   return true;
}

bool retro_vfs_stat_file(const char *path, struct retro_file_info *buffer)
{
   return false;
}

bool retro_vfs_remove_file(const char *path)
{
   return false;
}

bool retro_vfs_create_directory(const char *path)
{
   return false;
}

bool retro_vfs_remove_directory(const char *path)
{
   return false;
}

bool retro_vfs_list_directory(const char *path, char ***items, unsigned int *item_count)
{
   return false;
}

struct vfs_driver_t vfs_retro_driver = {
   retro_vfs_init,
   retro_vfs_deinit,
   retro_vfs_translate_path,
   retro_vfs_stat_file,
   retro_vfs_remove_file,
   retro_vfs_create_directory,
   retro_vfs_remove_directory,
   retro_vfs_list_directory,
};
