# Dirty expression that appends `index.html` to Markdown links which end with
# slash (/). This is required for offline documentation. Web browser won't load
# `index.html` without the aid of HTTP.
s/\(\[[[:alnum:][:blank:]\/.:_@#-]*\]([[:alnum:]\/.:_@#-]*\/\)\()\)/\1index.html\2/g

# Blacklist CuteHMI autolinks (confused with CuteHMI namespace). It should not
# replace strings like "CuteHMI::Class" or "CuteHMI.Component".
s/\bCuteHMI[[:punct:]]*[[:space:]]/%&/g
s/\bCuteHMI[[:punct:]]*$/%&/g

