SHELL = /bin/sh


OBJDIR := .obj
DEPDIR := .dep
SRCDIR := 

CPP_SOURCES = 	ttsDemo.cpp \
	lib/piper/src/cpp/piper.cpp \
	lib/piper/piperclass.cpp
	
C_SOURCES =	

CFLAGS = -Wl,--no-as-needed -fexceptions -fpermissive -fopenmp -pthread -O3 -mcpu=cortex-a72 -mtune=cortex-a72 -Wno-psabi

CC = g++
INCLUDES = -I/opt/vc/include \
	-I./lib/piper/lib \
	-I./include \
	-I./lib/piper/include \
	-I./lib/piper \
	-I/usr/local/lib/piper
	
LIBS =-lpthread \
	-lfmt \
	-lspdlog \
	-lespeak-ng \
	-lonnxruntime \
	-lpiper_phonemize \
	-lasound \

SLIBS=

DEPFLAGS = -MT $@ -MMD -MP -MF  $(DEPDIR)/$*.d 

SOURCES=$(CPP_SOURCES) $(C_SOURCES)
OBJECTS=$(CPP_SOURCES:.cpp=.o) $(C_SOURCES:.c=.o)

mkdirs = $(shell mkdir -p   $(DEPDIR)/$(dir $(path)) $(OBJDIR)/$(dir $(path)))
$(foreach path,$(SOURCES),$(mkdirs))

POBJECTS= $(addprefix $(OBJDIR)/, $(OBJECTS))

PRG=ttsDemo

all: $(PRG)
$(PRG):$(POBJECTS)
	$(CC) -std=c++17 -Wl,--no-as-needed -o $@ $(POBJECTS) $(LIBS)  $(SLIBS) 
$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC) -std=c++17 $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d 
	$(CC) -std=c++17 $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

DEPFILES =  $(C_SOURCES:%.c=%.d)
DEPFILES +=  $(CPP_SOURCES:%.cpp=%.d)
PDEPFILES= $(addprefix $(DEPDIR)/, $(DEPFILES))
$(PDEPFILES):
include $(wildcard $(PDEPFILES))

clean:
	-rm -f $(POBJECTS) $(PDEPFILES) $(PRG) $(OBJDIR)/*.o $(DEPDIR)/*.d