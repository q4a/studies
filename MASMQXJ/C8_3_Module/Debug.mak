################################################################################
# File  : Debug.mak
# Desc  :
#   Debug config makefile
################################################################################

AFLAGS = /D"__DEBUG__"
CXXFLAGS = /Od /Gm /D "_DEBUG"
LDFLAGS = /INCREMENTAL:YES
