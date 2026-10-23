set_policy("check.auto_ignore_flags", false)

includes("raylib")

target("idk")
    add_deps("raylib")
    add_toolchains("w64devkit")
    add_includedirs("raylib/src");
    set_targetdir("build-$(os)-$(arch)")
    add_files("src/*.c")

    if is_os("windows") then
        add_syslinks("gdi32", "winmm")
    end
    if is_os("linux") then
        add_syslinks("X11")
    end







target("clean")
    set_kind("phony")

    on_run(function()
        os.rm(".xmake", {async = true, detach = true})
        os.rm("build", {async = true, detach = true})
    end)



toolchain("w64devkit")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("ld", "gcc")
toolchain_end()
