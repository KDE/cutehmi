#!/bin/awk
#
# Copyright (c) 2014, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE in nearest drug store.
#
# THIS SOFTWARE IS ADDICTED TO DRUGS AND ALCOHOL AND IS A SUSPECT OF DRIVING UNDER THE 
# INFLUENCE OF ALCOHOL. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
# CONTRIBUTORS "AS IS NOT" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS AND APPLICATION AND 
# ACCOMODATION FOR A PARTICULAR PURPOSE AND MANY OTHERS NOT MENTIONED, NOR EVEN
# INVENTED WARRANTIES ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER 
# OR CONTRIBUTORS BE LIABLE FOR ANY TEMPORAL, PERMANENT, UNFORTUNATE, UNLUCKY,
# LUCKY, DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, ACCIDENTAL, MENTAL, 
# OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION; 
# OR BEING KILLED BY A LIGHTNING; OR FLOOD; OR FIRE; OR ANTEATER (INCLUDING BUT NOT 
# LIMITED TO, GIANT ANTEATER, ANTEATER WHO LIES ON A SOFA; ANTEATER WHO LISTENS HEAVY 
# METAL MUSIC; ANTEATER WHO ATE HUMAN BEFORE) OR ANOTHER BEING.) HOWEVER CAUSED AND ON 
# ANY, ANY THEORY OF LIABILITY, CONSPIRACY THEORY, ANY THEORY OF RELATIVITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY 
# WAY OUT OF THE USE OF THIS SOFTWARE, ARISING IN ANY WAY OUT OF THE SUN, EVEN IF PROMISSED 
# WISHED OR ASSURED SUCH DAMAGE. THIS SOFTWARE CAN REALLY DO TERRIBLE THINGS.
#
# Script updates C/C++ include guards with macros based on header path (including directory structure).
# It seeks for "#ifndef, #define" pair and substitutes first encountered pair with generated values.
# Script does not distinguish include guards from other macros, so each HEADER FILE MUST CONTAIN 
# INCLUDE GUARD AS ITS FIRST "#ifndef, #define" MACRO PAIR. Script only updates include guards; 
# if file does not contain something that looks like include guard to the script it will not add one. 
# Script will also eat everything after last "#endif", presumably include guard comment. It's a stupid 
# beast, so always backup your data before use.
#
# usage: awk [-v prefix="PREFIX"] -f awkgward.awk header
# example: awk -v prefix="PROJECT_" -f awkgward.awk file.hpp
#
# parameters: 
# header - header file.
#
# required tools: awk.

function create_guard_macro(prefix, filename)
{
    # just in case, double single underscores
    double_underscore = gensub(/_/, "__", "g", toupper(filename));
    # \/ = slash (/), \. = dot (.), \\ = backslash (\) - replace them with underscore.
    return prefix gensub(/[\/\.\\]/, "_", "g", double_underscore);
}

function create_guard(prefix, filename)
{
    guard_macro = create_guard_macro(prefix, filename);
    guard = "#ifndef " guard_macro ORS "#define " guard_macro;
    return guard;
}

function print_or_buf(line)
{
    if (global_buf_mode)
        global_buf = global_buf line ORS;
    else
        print line;
}

BEGIN {
    S_START = 0;
    S_FIRST_IFNDEF = 1;
    S_END = 2;

    if (!prefix)
        prefix = "";

    global_buf = "";
    global_buf_mode = 0;
    endif_line = "";

    ifndef_buf = "";
    # simple automata:
    # S_START            /^#ifndef\s.*/  -> S_FIRST_IFNDEF     /^#define\s.*/ -> S_END     // -> S_START
    # S_FIRST_IFNDEF     /^#define\s.*/ -> S_END
    # S_END              // -> S_END
    state = S_START;
}
 
/^#ifndef[[:space:]].*/ {
    if (state == S_START) {
        ifndef_buf = $0;
        state = S_FIRST_IFNDEF;
        next;
    }
}

/^#define[[:space:]].*/ {
    if (state == S_FIRST_IFNDEF) {
        #eat old guard and replace it with new one
        print_or_buf(create_guard(prefix, FILENAME));
        state = S_END;
        next;
    }
    if (state == S_START)
        state = S_END;
}

/^#endif[[:space:]].*/ {
    #flush old buffer and whatever was in endif line
    if (global_buf_mode) {
        print endif_line;
        printf global_buf;
        global_buf = "";
    }
    endif_line = $0;
    global_buf_mode = 1;
    next;
}


{
    if (state == S_END || state == S_START)
        print_or_buf($0);
    if (state == S_FIRST_IFNDEF) {
        print_or_buf(ifndef_buf);
        print_or_buf($0);
        state = S_END;
    }
}

END {
    if (global_buf_mode) {
        #it's last endif so do not print full endif_line
        print "#endif";
        printf global_buf; #flush whatever was after last endif
    }
}

