NAME				=	fingerprintmatcher

#
#	Php.ini directories
#
#	In the past, PHP used a single php.ini configuration file. Today, most
#	PHP installations use a conf.d directory that holds a set of config files,
#	one for each extension.
#
#   for cli     -->  /etc/php/7.0/cli/conf.d
#   for apache  -->  /etc/php/7.0/apache2/conf.d

INI_DIR_cli			    =	/etc/php/7.0/apache2/conf.d
INI_DIR_apache2			=	/etc/php/7.0/cli/conf.d
INI_DIR_fpm             =   /etc/php/7.0/fpm/config.d

#
#	The extension dirs
#
#	This is normally a directory like /usr/lib/php5/20121221 (based on the 
#	PHP version that you use. We make use of the command line 'php-config' 
#	instruction to find out what the extension directory is, you can override
#	this with a different fixed directory
#

EXTENSION_DIR		=	$(shell php-config --extension-dir)


#
#	The name of the extension and the name of the .ini file
#
#	These two variables are based on the name of the extension. We simply add
#	a certain extension to them (.so or .ini)
#

EXTENSION 			=	${NAME}.so
INI 				=	${NAME}.ini


#
#	Compiler
#   The GNU C++ compiler is used.
#

COMPILER			=	g++
LINKER				=	g++

#
#	Compiler and linker flags
#
#	This variable holds the flags that are passed to the compiler. 
#   We link to our original c++ library 
#   here we tell the compiler to link our library
#

COMPILER_FLAGS		=	-Wall -c -O2 -std=c++11 -fpic -o 
LINKER_FLAGS		=	-shared
LINKER_DEPENDENCIES	=	-lphpcpp -L. -l:./OpticalFingerVerifyUbuntu14_64.so -L:${EXTENSION_DIR}


#
#	Command to remove files, copy files and create directories.
#
#	I've never encountered a *nix environment in which these commands do not work. 
#	So you can probably leave this as it is
#

RM					=	rm -f
CP					=	cp -f
MKDIR				=	mkdir -p


#
#	All source files are simply all *.cpp files found in the current directory
#
#	A builtin Makefile macro is used to scan the current directory and find 
#	all source files. The object files are all compiled versions of the source
#	file, with the .cpp extension being replaced by .o.
#

SOURCES				=	$(wildcard *.cpp)
OBJECTS				=	$(SOURCES:%.cpp=%.o)


#
#	From here the build instructions start
#

all:					${OBJECTS} ${EXTENSION}

${EXTENSION}:			${OBJECTS}
						${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
						${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR_cli}
						${CP} ${INI} ${INI_DIR_apache2}
		
installs:		
						${CP} ${EXTENSION} ${EXTENSION_DIR}
						${CP} ${INI} ${INI_DIR_cli}
						${CP} ${INI} ${INI_DIR_fpm}
		

clean:
						${RM} ${EXTENSION} ${OBJECTS}

