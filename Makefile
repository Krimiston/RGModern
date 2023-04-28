# -----------------------------------------------
# packages settings
# -----------------------------------------------
include ./ext/settings.txt

# -----------------------------------------------
# UUID and PASSWORDS
# -----------------------------------------------
UUID ?= $(shell uuidgen | cut -c-32)
PASSWORD := $(shell uuidgen | sha256sum | cut -d' ' -f1)
RGM_VERSION ?= $(shell git tag --list | tail -1)*
RGM_FULLVERSION = $(RGM_VERSION) ($(shell date +%F) revision $(shell find ./src -type f | sort | xargs -n 1 cat | md5sum | cut -c-10))

system := $(shell uname | cut -d'-' -f1)

path_thirdparty := \
	./third_party/centurion/src \
	./third_party/concurrentqueue \
	./third_party/incbin \
	./third_party/readerwriterqueue \
	./third_party/xorstr/include \
	./third_party/ruby$(RUBY_M_VERSION)/include

path_script := ./src/script
deps := ./ext/deps.mk
Script := ./src/script ./src/config.ini
Data ?= ./Project1/Data
libgch := ./src/lib/lib.hpp.gch
slient := 1>/dev/null
zip_embeded := ./embeded.zip
zip_publish := ./publish_v$(RGM_VERSION).zip
zip_temp_add := 7z a -tzip -mx9 -p'$(PASSWORD)' $(zip_embeded) $(slient)
zip_publish_add := 7z a -tzip $(zip_publish) $(slient)

# -----------------------------------------------
# include and link path
# -----------------------------------------------
path_include = $(MSYSTEM_PREFIX)/include
path_lib = $(MSYSTEM_PREFIX)/lib
path_include += $(path_thirdparty) ./src

cc = $(MSYSTEM_PREFIX)/bin/g++
cflags = -std=c++20 -pipe -fstack-protector-strong -MMD -MP -static -Wall -Wextra
ifeq ($(system), MINGW64_NT)
	cflags +=
else
	cflags += -m32 -mfma
endif

cflags += -DRGM_FULLVERSION="\"$(RGM_FULLVERSION)\""
cflags += -DCC_VERSION="\"$(shell $(cc) --version | head -n1)\""
cflags += -DRUBY_EXPORT -DZIP_STATIC

# build mode
# 0 = debug    -> debug.exe
# 1 = develop  -> main.exe
# 2 = standard -> Game.exe
# 3 = encrypt  -> Gamew.exe
cflags_debug    = -DRGM_BUILDMODE=0 -Og -g -DDEBUG
cflags_develop  = -DRGM_BUILDMODE=1 -s -O3
cflags_standard = -DRGM_BUILDMODE=2 -s -O3 -DPASSWORD="\"$(PASSWORD)\""
cflags_encrypt  = -DRGM_BUILDMODE=3 -s -O3 -DPASSWORD="\"$(PASSWORD)\"" -mwindows

clibs = icon.o
libs = pthread stdc++
libs_dynamic =
# -----------------------------------------------
# ruby static library
# -----------------------------------------------
path_lib += ./third_party/ruby$(RUBY_M_VERSION)/lib
ifeq ($(system), MINGW64_NT)
	libs += x64-ucrt-ruby$(RUBY_M_VERSION)0-static
else
	libs += msvcrt-ruby$(RUBY_M_VERSION)0-static
endif
libs += gmp zip uuid shell32 ws2_32 iphlpapi imagehlp bcrypt

# -----------------------------------------------
# SDL2 static library
# -----------------------------------------------
path_include += $(MSYSTEM_PREFIX)/include/SDL2
libs_dynamic += mingw32 SDL2main SDL2 SDL2_ttf SDL2_image SDL2_mixer
libs += dinput8 setupapi advapi32 version oleaut32 ole32 imm32 winmm user32 m
libs += harfbuzz freetype bz2 brotlidec png z graphite2 intl rpcrt4 brotlicommon dwrite usp10
libs += tiff webp jpeg jbig lzma deflate zstd lerc jxl hwy sharpyuv
libs += flac mpg123 vorbisfile opusfile ogg vorbis opus gdi32 shlwapi

# -----------------------------------------------
# opengl
# -----------------------------------------------
libs += opengl32 d3dx9

# -----------------------------------------------
# ruby static extension
# -----------------------------------------------
libs += :fiddle.a :zlib.a
libs += ffi

# -----------------------------------------------
# set cflags
# -----------------------------------------------
cflags += $(addprefix -I,$(path_include))
cflags += $(addprefix -L,$(path_lib))

clibs_dynamic = $(clibs) -static -Wl,-Bdynamic $(addprefix -l,$(libs_dynamic)) -Wl,-Bstatic $(addprefix -l,$(libs))
clibs_static = $(clibs) $(addprefix -l,$(libs_dynamic)) $(addprefix -l,$(libs))
# -----------------------------------------------
# tasks
# -----------------------------------------------
-include main.d debug.d Game.d Gamew.d

.PHONY : all deps clean publish

all : main.exe

debug.exe : ./src/main.cpp Makefile icon.o
	@echo "compile $@"
	@rm -f $(libgch)
	@$(cc) $< -o $@ $(cflags) $(clibs_static) $(cflags_debug)

main.exe : ./src/main.cpp Makefile icon.o $(libgch)
	@echo "compile $@"
	@time $(cc) $< -o $@ $(cflags) $(clibs_static) $(cflags_develop)

Game.exe : ./src/main.cpp Makefile icon.o
	@echo "pack $(zip_embeded)"
	@rm -f $(zip_embeded)
	@$(zip_temp_add) $(Script)
	@echo "compile $@"
	@$(cc) $< -o $@ $(cflags) $(clibs_static) $(cflags_standard)
	@cp $@ ./Project1/

Gamew.exe : ./src/main.cpp Makefile icon.o
	@echo "pack $(zip_embeded)"
	@rm -f $(zip_embeded)
	@$(zip_temp_add) $(Data)
	@$(zip_temp_add) $(Script)
	@echo "compile $@"
	@$(cc) $< -o $@ $(cflags) $(clibs_static) $(cflags_encrypt)
	@echo "compress $@"
	@upx -q $@ $(slient)
	@cp $@ ./Project1/

main_win7.exe : ./src/main.cpp Makefile icon.o $(libgch)
	@echo "compile $@"
	@time $(cc) $< -o $@ $(cflags) $(clibs_dynamic) $(cflags_develop)

Game_win7.exe : ./src/main.cpp Makefile icon.o
	@echo "pack $(zip_embeded)"
	@rm -f $(zip_embeded)
	@$(zip_temp_add) $(Script)
	@echo "compile $@"
	@$(cc) $< -o $@ $(cflags) $(clibs_dynamic) $(cflags_standard)
	@cp $@ ./Project1/

Gamew_win7.exe : ./src/main.cpp Makefile icon.o
	@echo "pack $(zip_embeded)"
	@rm -f $(zip_embeded)
	@$(zip_temp_add) $(Data)
	@$(zip_temp_add) $(Script)
	@echo "compile $@"
	@$(cc) $< -o $@ $(cflags) $(clibs_dynamic) $(cflags_encrypt)
	@echo "compress $@"
	@upx -q $@ $(slient)
	@cp $@ ./Project1/

icon.o : ext/icon.rc ext/favicon.ico
	@echo "make icon"
	@windres -i $< -o $@ --input-format=rc --output-format=coff

clean :
	@rm -f debug.d main.d Game.d Gamew.d main_win7.d Game_win7.d Gamew_win7.d
	@rm -f debug.exe main.exe Game.exe Gamew.exe main_win7.exe Game_win7.exe Gamew_win7.exe
	@rm -f *.log *.png
	@rm -f $(zip_embeded) $(libgch)
	@rm -f config.ini icon.o
	@rm -f error.log

envs : $(deps)
	@make envs -f $(deps)

publish : main.exe Game.exe Gamew.exe Game_win7.exe Gamew_win7.exe
	@echo "pack $(zip_publish)"
	@rm -f $(zip_publish)
	@cp ./src/config.ini ./Project1/
	@rm -f ./Projec1/error.log
	@$(zip_publish_add) main.exe src SDL2*.dll Project1

misc.7z :
	wget -q https://7niu.gxmatmars.com/p1/RGModern/misc.7z

misc : misc.7z
	@7z x -y $^

$(libgch) : ./src/lib/lib.hpp
	@echo "compile $@"
	@g++ -x c++-header -c $< $(cflags) $(cflags_develop)

%.o : %.hpp
	@g++ -x c++-header -c -o /dev/null $< $(cflags)

headers :
	@find ./src/ -type f -name *.hpp | sed s/.hpp/.o/g | xargs -n 1 make 2> make.log