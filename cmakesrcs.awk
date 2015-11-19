#!/bin/awk
#
# Copyright (c) 2010, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it.
#
# THIS SOFTWARE IS ADDICTED TO DRUGS AND ALCOHOL AND IS A SUSPECT OF DRIVING UNDER THE 
# INFLUENCE OF ALCOHOL. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
# CONTRIBUTORS "AS IS NOT" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS AND APPLICATION AND 
# ACCOMODATION FOR A PARTICULAR PURPOSE AND MANY OTHERS NOT MENTIONED, NOR EVEN
# INVENTED WARRANTIES ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER 
# OR CONTRIBUTORS BE LIABLE FOR ANY TEMPORAL, PERMANENT, UNFORTUNATE, UNLUCKY,
# LUCKY, DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, ACCIDENTAL, DENTAL, MENTAL, 
# ELEMENTAL OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION; 
# OR BEING KILLED BY A LIGHTNING; OR FLOOD; OR FIRE; OR ANTEATER (INCLUDING BUT NOT 
# LIMITED TO, GIANT ANTEATER, ANTEATER WHO LIES ON A SOFA; ANTEATER WHO LISTENS HEAVY 
# METAL MUSIC; ANTEATER WHO ATE HUMAN BEFORE) OR ANOTHER BEING.) HOWEVER CAUSED AND ON 
# ANY, ANY THEORY OF LIABILITY, CONSPIRACY THEORY, ANY THEORY OF RELATIVITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY 
# WAY OUT OF THE USE OF THIS SOFTWARE, ARISING IN ANY WAY OUT OF THE SUN, EVEN IF PROMISSED 
# WISHED OR ASSURED SUCH DAMAGE. THIS SOFTWARE CAN DO TERRIBLE THINGS.
#
# Script to collect sources and put them into CMakeLists.txt file. It substitutes section 
# between magic strings with a generated list of sources.
# Magic strings are: ^#sources_begin, ^#sources_end (^ denotes beginning of the line).
#
# usage: awk [-v src_dirs="dir1 dir2 ..."] [-v src_files="pattern1;pattern2;..."] [-v cmake_var="VAR"] -f cmakesrcs.awk CMakeList.txt
# example: awk -v src_dirs="src/dir1 src/dir2" -v src_files="*.cxx;*.c" -v cmake_var="SOURCES" -f cmakesrcs.awk CMakeList.txt
#
# parameters: 
# src_dirs - where to look for sources (default: "*").
# cmake_var - cmake sources variable name (default: "SRCS").
# src_files - list of source file patterns separated by a semicolon (default: "*.cpp;*.c").
#
# required tools: awk, find (findutils).
#
# Note on MS Windows: find shipped with findutils may be shadowed by Windows' find.exe,  
# residing in Windows/system32 folder. Windows find.exe is a different tool and it has to
# be moved behind findutils find in script search path.


BEGIN {
	if (!src_dirs)
		src_dirs = "*";
	if (!cmake_var)
		cmake_var = "SRCS";
	if (!src_files)
		src_files = "*.cpp;*.c";
	split(src_files, src_files_arr, ";");

	sources_section = 0;
}

/^#sources_begin/ {
	sources_section = 1; 
	print $0;
	print "SET(" cmake_var;
	for (src_file_index in src_files_arr)
		system("find " src_dirs " -name '" src_files_arr[src_file_index] "' -print");
	print ")";
}

{
	if (!sources_section)
		print $0;
}

/^#sources_end/ {
	sources_section = 0; 
	print $0 
}
