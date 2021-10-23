############################################################
# Author		: Mahmoud Karam
# Version		: 1
# Date 			: 12 Aug 2021
# Description	: makefile for automatic documentation of doxygen & Latex:
#					* Build doxygen html files
#					* Build PDF version
#					* move these generated files to a corresponding 
#						directory defined in DOC_DIR variable below
############################################################
# Host Configurations
SHELL 	= cmd
RM		= del /s /q
RMDIR 	= rmdir /s /q

# Target files Configurations
OUTPUT_PDF_NAME	= SW_Documentation
DOC_DIR 		= Documentation
HTML_DIR		= html
LATEX_DIR		= latex
# To not delete any of the following directories, comment it.
#TO_REMOVE_DIRS 	+= ${HTML_DIR}
TO_REMOVE_DIRS 	+= ${LATEX_DIR}

#  Building Rules
all	: clean

	@echo Generating: html and Latex versions ...
	@doxygen
	@echo Finished generating: html and Latex versions

	@echo Generating: PDF version ...
	@latex\make
	@echo Finished generating: PDF version

	@echo Organising generated files in directory: ${DOC_DIR} ...
	@-mkdir	${DOC_DIR}\${HTML_DIR} ${DOC_DIR}\${LATEX_DIR}
	@copy "latex\refman.pdf" "${DOC_DIR}\${OUTPUT_PDF_NAME}.pdf"
	@xcopy ${HTML_DIR} ${DOC_DIR}\${HTML_DIR}
	@xcopy latex ${DOC_DIR}\${LATEX_DIR}
	${RMDIR} latex html
	cd ${DOC_DIR} && ${RMDIR} ${TO_REMOVE_DIRS}
	@echo Finished organising generated files in directory: ${DOC_DIR}

clean :
	@-${RMDIR} ${DOC_DIR}

# Phony targets
.PHONY	: clean all