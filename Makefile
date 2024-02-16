.SILENT: all install clean
CC?=gcc
CXX?=g++
AR?=ar
CFLAGS=-Os -Wall -Wextra -Wformat-security -Werror
SECURITY_FLAGS=-Wstack-protector -Wstack-protector --param ssp-buffer-size=4 \
	       --param ssp-buffer-size=4 -fstack-protector-strong \
	       -fstack-clash-protection -pie -fPIE -D_FORTIFY_SOURCE=2

all: virtual_controller.c model_map.cpp model_map.h
	$(CXX) -c -std=c++11 $(CFLAGS) $(SECURITY_FLAGS) model_map.cpp -o model_map.o
	$(AR) -rcs libmodel_map.a model_map.o
	$(CC) -std=gnu11 $(CFLAGS) $(SECURITY_FLAGS) virtual_controller.c -L. -lmodel_map -lstdc++ -o virtual_controller

install:
	strip --strip-unneeded virtual_controller
	cp virtual_controller /sbin/virtual_controller

clean:
	rm -f virtual_controller model_map.o libmodel_map.a
