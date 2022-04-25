############################################################
# Author		: Mahmoud Karam
# Version		: 2
# Description	: makefile for project structure and drivers creation:
#					<make -f project.mk driver NAME=yourDriverName>		--> creates a new driver with the name "yourDriverName"
#					<make -f project.mk project NAME=yourProjectName>	--> creates a new project with the name "yourProjectName"
############################################################

############################################################
#					Configurations
############################################################
# Host Configurations
SHELL 	= cmd
RM		= del /s /q
RMDIR	= rmdir /s /q
# Note: / is used with GCC as it's linux SW.
# Note: \ is used with Windows, So, if working on Linux,
#		assume changing \ to / in Windows commands or paths

# Name of the project to use with <make create>
NAME	= Test

# Files directories
SDIR	= src
HDIR	= include
LDIR	= lib

############################################################
#					Creating New Project
############################################################
#Create a project with name ${NAME}      
.PHONY: project         
project :
	@echo Creating project: ${NAME}
	mkdir	${NAME}
	mkdir 	${NAME}\${SDIR}				
	mkdir 	${NAME}\${HDIR}      	         	
	mkdir 	${NAME}\${LDIR}
	echo	int main (void){                >> ${NAME}\src\main.c
	echo		return 0;                   >> ${NAME}\src\main.c
	echo	}                               >> ${NAME}\src\main.c
	echo	Author: Mahmoud Karam           >> ${NAME}\readme.txt
	echo	E-mail: ma.karam272@gmail.com	>> ${NAME}\readme.txt
	echo	##############################	>> ${NAME}\readme.txt
	echo	${SDIR} folder has source files.	>> ${NAME}\readme.txt
	echo	${HDIR} folder has header files.	>> ${NAME}\readme.txt
	echo	${LDIR} folder has libraries files.	>> ${NAME}\readme.txt
	copy    makefile ${NAME}\makefile
	@echo Finished creating project: ${NAME}
	
############################################################
#					Creating New Driver
############################################################
#Create a driver with name ${NAME}      
.PHONY: driver         
driver :
	@echo Creating driver: ${NAME}
	mkdir	${NAME}
	echo	>> ${NAME}\${NAME}.c
	echo	>> ${NAME}\${NAME}.h
	echo	>> ${NAME}\${NAME}_cfg.c
	echo	>> ${NAME}\${NAME}_cfg.h
	echo	Author: Mahmoud Karam           >> ${NAME}\readme.txt
	echo	E-mail: ma.karam272@gmail.com	>> ${NAME}\readme.txt
	echo	##############################	>> ${NAME}\readme.txt
	echo	${NAME}.c has the static code program.    >> ${NAME}\readme.txt
	echo	${NAME}.h has the static code interfaces. >> ${NAME}\readme.txt
	echo	${NAME}_cfg.c has ${NAME} configurations. >> ${NAME}\readme.txt
	echo	${NAME}_cfg.h has ${NAME}_cfg.c interfaces to ${NAME}.c>> ${NAME}\readme.txt
	echo	#ifndef ${NAME}_H       > ${NAME}\${NAME}.h
	echo	#ifndef ${NAME}_CFG_H   > ${NAME}\${NAME}_cfg.h
	echo	#define ${NAME}_H       >> ${NAME}\${NAME}.h
	echo	#define ${NAME}_CFG_H   >> ${NAME}\${NAME}_cfg.h
	echo	#endif                  >> ${NAME}\${NAME}.h
	echo	#endif                  >> ${NAME}\${NAME}_cfg.h
	@echo Finished creating driver: ${NAME}
