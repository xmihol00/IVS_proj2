
# IMPORTANT: this makefile primarily uses other Makefiles generated by cmake, if these Makefiles don't exist or compilation is
# unsuccessful, then cmake is invoked, all the necessary files are genrated and make is run again.
# explanation: make -s: silent mode (unnecessary log is not printed)
# expalnation: make -C: calls other Makefile in specified directory

# name of the main executable, of the calculator, to change the name just simply change 'PP_calc' to anything 
EXE_NAME = PP_calc

# suffix of the dynamic version of the calculator, to change it, just simply change 'dynamic' to anything
DYNAMIC_NAME_SUFF = dynamic

# the location of generated files
BUILD_DIR = ../build

# the name of the graphic layout file (do not change!)
GRAPHICS_FILE_NAME = grap.glade

# the location of the source files (do not change!)
SOURCE_DIR = source

.PHONY: all run clean test pack calc calc_dynamic calc_test profile doc dynamic installer_static
.PHONY: run_dynamic all_executables stddev stddev_run help help_exe installer_dynamic

# Compiles all executables. When compilation fails (i.e. build directory does not exits, build dependences are incorrect, ...), 
# the direcotry is created, cmake is invoked all necesssary files are generated and the compilation is run again. 
# The file with the graphics layout ($(GRAPHICS_FILE_NAME)) is copied to the directory, where the '$(EXE_NAME)' executable is generated, 
# as it is necessary for running the program.
# (in bash 'cp' offers switch '-u', which copies the file only when the file is changed)
all: all_executables

all_executables:
	@make -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. \
	&& make -s && cd - ;}; cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/
# or better (in bash): cp -u $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME)i $(BUILD_DIR)/bin/

# compiles and runs the $(EXE_NAME)ulator. When the compilation fails, the same procedur as above is used. File $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) is also copied
# to the directory with '$(EXE_NAME)' executable, as it is necessary tu run the program.
run:
	@cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/ || { mkdir $(BUILD_DIR); cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && cd - ; cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/ ; }; make run -s -C $(BUILD_DIR)
#or better (in bash): cp -u $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/

run_dynamic:
	@cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/ || { mkdir $(BUILD_DIR); cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && cd - ; cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/ ; }; make run_$(DYNAMIC_NAME_SUFF) -s -C $(BUILD_DIR)

#compiles and runs the tests. When the compilation fails, the same procedur as above is used.
test:
	@make test_ -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make test_ -s ; }

# compiles only those files, which are necessaru for running the $(EXE_NAME)ulator. When the compilation fails, 
# the same procedur as above is used.
calc:
	@make $(EXE_NAME) -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make $(EXE_NAME) -s && cd - ;}; cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/

# compiles only those files, which are necessaru for running the $(EXE_NAME)ulator with .so libraries. 
# When the compilation fails, the same procedur as above is used.
calc_dynamic:
	@make $(EXE_NAME)_$(DYNAMIC_NAME_SUFF) -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make $(EXE_NAME)_$(DYNAMIC_NAME_SUFF) -s && cd - ;}; cp $(SOURCE_DIR)/$(GRAPHICS_FILE_NAME) $(BUILD_DIR)/bin/

# compiles only those files, which are necessary for running the tests. When the compilation fails, 
# the same procedur as above is used.
calc_test:
	@make $(EXE_NAME)_test -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	 -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make $(EXE_NAME)_test -s ; }

# compiles only those files, which are necessary for running the stddev. When the compilation fails, 
# the same procedur as above is used.
stddev:
	@make stddev -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make stddev -s ; }

# compiles the stdddev program with compiler flags needed for profiling. When the compilation fails, 
# the same procedur as above is used.
profile:
	@make stddev_profile -s -C $(BUILD_DIR) || { mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && cmake -DPROJ_NAME=$(EXE_NAME) \
	-DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && make stddev_profile -s ; }

# compiles and runs the stddev program, variable FILE has to be specified in the command line.
stddev_run: stddev
	@$(BUILD_DIR)/bin/stddev <$(FILE)

# creates the installer for the static version
installer_static:
	@cd installation/ ; sed -i 's/^Exec=.*/Exec=$(EXE_NAME)/g' PP_calc.desktop; sed -i 's/^Name=.*/Name=$(EXE_NAME)/g' PP_calc.desktop; \
	mv -f *_uninstaller $(EXE_NAME)_uninstaller; \
	sed -i 's/^sudo dpkg.*/sudo dpkg -r $(EXE_NAME)/g' $(EXE_NAME)_uninstaller; cd .. ; \
	mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && { rm CMakeCache.txt 2>/dev/null;\
	cmake -DINSTALLATION=ON -DSTATIC_INSTALLATION=ON -DPROJ_NAME=$(EXE_NAME) -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && \
	cpack; mv -f $(EXE_NAME)-1.0.0-Linux.deb ../../install/; }

# creates the installer for the static version
installer_dynamic:
	@cd installation/ ; sed -i 's/^Exec=.*/Exec=$(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' PP_calc.desktop; sed -i 's/^Name=.*/Name=$(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' PP_calc.desktop; \
	mv -f *_uninstaller $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)_uninstaller; \
	sed -i 's/^sudo dpkg.*/sudo dpkg -r $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)_uninstaller; cd .. ; \
	mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && { rm CMakeCache.txt 2>/dev/null;\
	cmake -DINSTALLATION=ON -DSTATIC_INSTALLATION=OFF -DPROJ_NAME=$(EXE_NAME) -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && \
	cpack; mv -f $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)-1.0.0-Linux.deb ../../install/; }

# installs the static version of the calculator
install_static:
	@cd installation/ ; sed -i 's/^Exec=.*/Exec=$(EXE_NAME)/g' PP_calc.desktop; sed -i 's/^Name=.*/Name=$(EXE_NAME)/g' PP_calc.desktop; \
	mv -f *_uninstaller $(EXE_NAME)_uninstaller; \
	sed -i 's/^sudo dpkg.*/sudo dpkg -r $(EXE_NAME)/g' $(EXE_NAME)_uninstaller; cd .. ; \
	mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && { rm CMakeCache.txt 2>/dev/null;\
	cmake -DINSTALLATION=ON -DSTATIC_INSTALLATION=ON -DPROJ_NAME=$(EXE_NAME) -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && \
	cpack && sudo dpkg -i ./$(EXE_NAME)-1.0.0-Linux.deb; rm $(EXE_NAME)-1.0.0-Linux.deb; }

# installs the dynamic version of the calculator
install_dynamic:
	@cd installation/ ; sed -i 's/^Exec=.*/Exec=$(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' PP_calc.desktop; sed -i 's/^Name=.*/Name=$(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' PP_calc.desktop; \
	mv -f *_uninstaller $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)_uninstaller; \
	sed -i 's/^sudo dpkg.*/sudo dpkg -r $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)/g' $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)_uninstaller; cd .. ; \
	mkdir $(BUILD_DIR) 2>/dev/null; cd $(BUILD_DIR) && { rm CMakeCache.txt 2>/dev/null;\
	cmake -DINSTALLATION=ON -DSTATIC_INSTALLATION=OFF -DPROJ_NAME=$(EXE_NAME) -DPROJ_NAME_DYNAMIC_SUFF=$(DYNAMIC_NAME_SUFF) .. && \
	cpack && sudo dpkg -i ./$(EXE_NAME)_$(DYNAMIC_NAME_SUFF)-1.0.0-Linux.deb; rm $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)-1.0.0-Linux.deb; }

# uninstalls the currently installed version
uninstall:
	@$(EXE_NAME)_uninstaller || $(EXE_NAME)_$(DYNAMIC_NAME_SUFF)_uninstaller

# packs the project directory
pack: clean
	@cd ../../ ; zip -r xfolty17_xmihol00_xsokol15.zip *

# generates the project documentation
doc:
	doxygen Doxyfile && cd ../../doc/latex && make && mv refman.pdf ../documentation.pdf

# cleans all unnecessary files (i.e. the whole build directory, as it can be generated)
clean:
	@rm -r $(BUILD_DIR)/ 2>/dev/null || echo "Some files could not be removed."

clean_exe:
	@make clean -s -C $(BUILD_DIR)

# list of possible commands
help:
	@echo "Use:  'make' or 'make all'              to compile all the source codes."
	@echo "Use:  'make run'                        to compile and run the calculaotor."
	@echo "Use:  'make run_dynamic'                to compile and run the calculaotor with .so library."
	@echo "Use:  'make test'                       to compile and run the tests of the calculator and math library."
	@echo "Use:  'make calc'                       to compile the source codes necessary for running the calcualtor."
	@echo "Use:  'make calc_dynamic'               to compile the source codes necessary for running the calcualtor with .so library."
	@echo "Use:  'make calc_test'                  to compile the source codes necessary for running the tests."
	@echo "Use:  'make stddev'                     to compile the source codes necessary for running the stddev program."
	@echo "Use:  'make profile'                    to compile the source codes with compiler flags necessary for profiling of program sttdev."
	@echo "Use:  'make stddev_run FILE=your_file'  to compile and run the stddev program with input from 'your_file'."
	@echo "Use:  'make pack'                       to compress the project to a .zip file."
	@echo "Use:  'make doc'                        to generate project doumentation."
	@echo "Use:  'make installer_static'           to compile the source codes and create the installer of the static version."
	@echo "Use:  'make installer_dynamic'          to compile the source codes and create the installer of the dynamic version."
	@echo "Use:  'make install_static'             to install the static version of the calculator to your computer."
	@echo "Use:  'make install_dynamic'            to install the dynamic version of the calculator to your computer."
	@echo "Use:  'make uninstall'                  to uninstall the currently installed version of the calculator from your computer."
	@echo "Use:  'make clean'                      to remove all unnecessary files."
	@echo "Use:  'make clean_exe'                  to remove all executable files, that can be recompiled."

help_exe:
	@echo "Use:  'make' or 'make all'              to compile all the source codes."
	@echo "Use:  'make calc'                       to compile the source codes necessary for running the calcualtor."
	@echo "Use:  'make calc_dynamic'               to compile the source codes necessary for running the calcualtor with .so library."
	@echo "Use:  'make calc_test'                  to compile the source codes necessary for running the tests."
	@echo "Use:  'make stddev'                     to compile the source codes necessary for running the stddev program."
	@echo "Use:  'make profile'                    to compile the source codes with compiler flags necessary for profiling of program sttdev."
	@echo "Use:  'make installer_static'           to compile the source codes and create the installer of the static version."
	@echo "Use:  'make installer_dynamic'          to compile the source codes and create the installer of the dynamic version."
