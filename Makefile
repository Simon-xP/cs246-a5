########## Variables ##########

CXX = g++-11                                 # compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD -IVisuals -IGame # compiler flags, include dirs
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}} # makefile name

SRC_DIRS = . Visuals Game                   # source directories
SOURCES = $(wildcard $(addsuffix /*.cc, $(SRC_DIRS))) # source files (*.cc) in all dirs
OBJECTS = ${SOURCES:.cc=.o}                 # object files forming executable
DEPENDS = ${OBJECTS:.o=.d}                  # substitute ".o" with ".d"
EXEC = watan                                # executable name

########## Targets ##########

.PHONY : clean                              # not file names

${EXEC} : ${OBJECTS}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11        # additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}               # OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}                         # include *.d files containing program dependences

clean :                                     # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}