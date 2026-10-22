set_policy("check.auto_ignore_flags", false)



target("idk")
    add_toolchains("w64devkit")
    set_targetdir("build-$(os)-$(arch)")
    add_linkdirs("lib/$(os)/$(arch)")
    add_files("src/*.c")
    add_links("raylib")
    add_syslinks("gdi32", "winmm")












toolchain("w64devkit")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("ld", "gcc")
toolchain_end()
