let version = "1.0.0-rc21"

let path =
  try (Sys.getenv "COCCINELLE_HOME")
  with Not_found->"/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/host/share/coccinelle"

let std_iso = ref (Filename.concat path "standard.iso")
let std_h   = ref (Filename.concat path "standard.h")

let dynlink_is_native = false
