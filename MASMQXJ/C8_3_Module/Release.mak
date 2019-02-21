################################################################################
# File  : Release.mak
# Desc  :
#   Release config makefile
################################################################################

AFLAGS = /D"__NDEBUG__"
CXXFLAGS = /O2 /Oi /D "NDEBUG" /Gy
LDFLAGS = /INCREMENTAL:NO /OPT:REF /OPT:ICF
