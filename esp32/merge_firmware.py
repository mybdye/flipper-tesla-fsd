# merge_firmware.py — PlatformIO post-build extra_script.
#
# After each ESP32 build, emit firmware-merged.bin: one full-flash image
# (bootloader + partition table + boot_app0 + application) starting at offset 0,
# so a blank board can be written in a single step by ESP Web Tools / esptool.
# The app-only firmware.bin is still emitted for the in-device OTA updater.
Import("env")
import os

# Bootloader offset differs by chip: 0x1000 on the original ESP32, 0x0 on the
# newer parts (their ROM loads the bootloader from the start of flash).
_BOOTLOADER_OFFSET = {
    "esp32":   "0x1000",
    "esp32s2": "0x1000",
    "esp32s3": "0x0",
    "esp32c3": "0x0",
    "esp32c6": "0x0",
}


def merge_firmware(source, target, env):
    board = env.BoardConfig()
    build_dir = env.subst("$BUILD_DIR")
    mcu = env.subst("$BOARD_MCU")  # esp32 / esp32s3 / ...
    platform = env.PioPlatform()

    bootloader = os.path.join(build_dir, "bootloader.bin")
    partitions = os.path.join(build_dir, "partitions.bin")
    app = os.path.join(build_dir, "firmware.bin")
    boot_app0 = os.path.join(
        platform.get_package_dir("framework-arduinoespressif32") or "",
        "tools", "partitions", "boot_app0.bin")
    merged = os.path.join(build_dir, "firmware-merged.bin")

    python = env.subst("$PYTHONEXE")
    esptool = os.path.join(
        platform.get_package_dir("tool-esptoolpy") or "", "esptool.py")

    boot_off = _BOOTLOADER_OFFSET.get(mcu, "0x1000")
    flash_mode = board.get("build.flash_mode", "dio")
    # build.f_flash looks like "40000000L" -> "40m".
    f_flash = str(board.get("build.f_flash", "40000000L")).rstrip("L")
    try:
        flash_freq = "%dm" % (int(f_flash) // 1000000)
    except ValueError:
        flash_freq = "40m"
    flash_size = board.get("upload.flash_size", "4MB")

    # Standard Arduino-ESP32 layout: partitions @ 0x8000, boot_app0 @ 0xe000,
    # app @ 0x10000 (true for min_spiffs / default_8MB / default_16MB).
    cmd = (
        '"%s" "%s" --chip %s merge_bin -o "%s" '
        '--flash_mode %s --flash_freq %s --flash_size %s '
        '%s "%s" 0x8000 "%s" 0xe000 "%s" 0x10000 "%s"' % (
            python, esptool, mcu, merged,
            flash_mode, flash_freq, flash_size,
            boot_off, bootloader, partitions, boot_app0, app))
    print("[merge] building full-flash image -> %s" % merged)
    env.Execute(cmd)


# Run after the application .bin is produced.
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", merge_firmware)
