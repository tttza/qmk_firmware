VIA_ENABLE = yes
OLED_DRIVER_ENABLE = yes
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
WPM_ENABLE = yes
LTO_ENABLE = yes

SRC += twpair_on_jis.c
SRC += oled_render_slave.c
SRC += ./lib/logo_reader.c

EXTRAFLAGS += -flto
