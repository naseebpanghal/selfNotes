You can print out variables as the makefile is read
$(info $$var is [${var}])


var := $(shell uname -m)
ifeq ($(findstring arm,$(var)),arm)
else ifeq ($(findstring aarch64,$(var)),aarch64)
else
endif
