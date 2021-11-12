CXXFLAGS = /nologo /W3 /Zi /EHsc /TP /D "WIN32" /D "WIN64" /D "_CONSOLE" /D "_UNICODE" /D "NDEBUG" /I. /O2 /Oi /GL /Gy /MD
LDFLAGS = /NOLOGO /SUBSYSTEM:CONSOLE /DEBUG /DYNAMICBASE /NXCOMPAT /INCREMENTAL:NO /OPT:REF /OPT:ICF /LTCG
CPPFILES = bench_iostream.cpp
OBJS = bin\$(CPPFILES:.cpp=.obj)
TARGET = bin\$(CPPFILES:.cpp=.exe)
INTS = bin\$(CPPFILES:.cpp=.pdb) bin\vc*.pdb $(TARGET).manifest

all: pre-build $(TARGET) post-build

pre-build:
    @if not exist bin mkdir bin && echo mkdir bin

post-build: $(TARGET) $(TARGET).manifest
    mt -nologo -manifest $(TARGET).manifest -outputresource:$(TARGET)

$(TARGET): $(OBJS)
    link $(LDFLAGS) /OUT:"$@" $(OBJS)

.cpp{bin\}.obj:
    cl $(CXXFLAGS) /c /Fo"bin\\" /Fd"bin\\" "$<"

clean:
    del /a /q $(TARGET) $(OBJS) $(INTS) >NUL 2>&1
