###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy
#
# DESCRIPTION:	    Makefile for the Dynamic Array abstract type.
#
# CREATED:	    04/16/2018
#
# LAST EDITED:	    04/21/2018
###

CC=gcc
OBJS += darray.o
ifeq ($(MAKECMDGOALS),debug)
	CFLAGS = -g -Wall -O0 -Wall -Wextra -pedantic \
		-D CONFIG_DEBUG_DARRAY -D CONFIG_TEST_LOG \
		-I Singly-Linked-List/
	OBJS += test.o
else
	CFLAGS = -Wall -Wextra -pedantic -O3 -I Singly-Linked-List
endif

.PHONY: debug clean

darray: $(OBJS)

debug: darray

clean:
	rm -rf *.dSYM
	rm -f *.o
	rm -f darray
	rm -f log.txt

###############################################################################
