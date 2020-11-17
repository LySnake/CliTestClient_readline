# This is the Makefile for the examples subdirectory of readline. -*- text -*-
#
# Copyright (C) 1994 Free Software Foundation, Inc.

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CFLAGS  = -g -I. -Ilib/readline -DREADLINE_LIBRARY
LDFLAGS = -g -Llib/readline

.c.o:
	$(CC) $(CFLAGS) -c $<
.cpp.o:
	$(CXX) $(CFLAGS)  --std=c++11 -c $<
all: test


test: main.o ReadlineWrap.o  CommandList.o utils.o Command.o
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ main.o Command.o ReadlineWrap.o CommandList.o utils.o  -lreadline -ltermcap  -pthread 

# threadPrint.o: threadPrint.cpp
main.o: main.cpp
ReadlineWrap.o: ReadlineWrap.cpp
CommandList.o: CommandList.cpp
utils.o: utils.cpp
Command.o: Command.cpp


clean:
	rm *.o