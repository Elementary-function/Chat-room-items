CC := gcc
CFLAGS := -Wall -O3
Libs = -lsqlite3
Target := server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += chat login regist super_user user_list trans_file main
AllObjs := $(addsuffix /src/*.o,$(Modules))

