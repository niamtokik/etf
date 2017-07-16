######################################################################
#
# Copyright (c) 2017 Mathieu Kerjouan <contact@steepath.eu>
#
# Permission to  use, copy, modify,  and distribute this  software for
# any purpose with or without fee is hereby granted, provided that the
# above  copyright notice  and this  permission notice  appear in  all
# copies.
#
# THE  SOFTWARE IS  PROVIDED  "AS  IS" AND  THE  AUTHOR DISCLAIMS  ALL
# WARRANTIES  WITH  REGARD  TO  THIS SOFTWARE  INCLUDING  ALL  IMPLIED
# WARRANTIES OF  MERCHANTABILITY AND  FITNESS. IN  NO EVENT  SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY  DAMAGES WHATSOEVER RESULTING FROM LOSS  OF USE, DATA
# OR PROFITS,  WHETHER IN AN  ACTION OF CONTRACT, NEGLIGENCE  OR OTHER
# TORTIOUS ACTION,  ARISING OUT OF  OR IN  CONNECTION WITH THE  USE OR
# PERFORMANCE OF THIS SOFTWARE.
#
#
# -------------------------------------------------------------------
#
# GNU Makefile
#
######################################################################
TARGETS := atom.c binary.c list.c map.c number.c string.c tuple.c
TARGETS += dynamic.c version.c
BUILD_DIR := _build

# Erlang library path
# usually in /usr/local/lib/erlang or /usr/lib/erlang
# you can set this value when make is called.
ERLANG_PATH ?= /usr/lib/erlang
ERLANG_LIBRARY := ${ERLANG_PATH}/usr/lib
ERLANG_INCLUDE := ${ERLANG_PATH}/usr/include
ERLANG_OBJECTS := ei

# foreach libraries, includes and dynamic libraries
CC_PLIB = $(foreach plib, $(ERLANG_LIBRARY), -L$(plib))
CC_PINC = $(foreach pinc, $(ERLANG_INCLUDE), -I$(pinc))
CC_LIBS = $(foreach obj, $(ERLANG_OBJECTS), -l$(obj))

# General GCC options
CC_OPTS = -Wall -g
CC_OPTS += $(CC_PLIB) $(CC_PINC)
CC = cc $(CC_OPTS)

help:
	@echo "Usage: make build TARGET=source.c"

$(BUILD_DIR):
	mkdir -p $@

clean:
	-rm $(BUILD_DIR)/*

build: $(BUILD_DIR)
ifdef TARGET
	@echo "==> Build $(TARGET) in $(BUILD_DIR)/$(basename $(TARGET))"
	$(CC) $(TARGET) -o $(BUILD_DIR)/$(basename $(TARGET)) $(CC_LIBS)
else
	@echo "Please set TARGET variable first"
endif

