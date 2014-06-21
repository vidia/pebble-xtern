#include "pebble_app_info.h"
#include "src/resource_ids.auto.h"

const PebbleAppInfo __pbl_app_info __attribute__ ((section (".pbl_header"))) = {
  .header = "PBLAPP",
  .struct_version = { APP_INFO_CURRENT_STRUCT_VERSION_MAJOR, APP_INFO_CURRENT_STRUCT_VERSION_MINOR },
  .sdk_version = { APP_INFO_CURRENT_SDK_VERSION_MAJOR, APP_INFO_CURRENT_SDK_VERSION_MINOR },
  .app_version = { 1, 0 },
  .load_size = 0xb6b6,
  .offset = 0xb6b6b6b6,
  .crc = 0xb6b6b6b6,
  .name = "XTERN",
  .company = "KeepFlying",
  .icon_resource_id = DEFAULT_MENU_ICON,
  .sym_table_addr = 0xA7A7A7A7,
  .flags = APP_INFO_WATCH_FACE,
  .num_reloc_entries = 0xdeadcafe,
  .uuid = { 0xD6, 0x1D, 0x61, 0xEA, 0xA0, 0x29, 0x42, 0xF3, 0xAD, 0x6A, 0x55, 0xB2, 0x82, 0x36, 0x9C, 0xF7 },
  .virtual_size = 0xb6b6
};
