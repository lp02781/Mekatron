# for Opengl
 
CCGL=g++
GL_CFLAGS = -O2 -DSHM -DHZ=100
XLIBS = -lXext -lXmu -lXi -lX11
GL_LIBS =  
#GL_LIBS =  -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib  #gak jalan di opengl 2.x 
CYG_OpenGL = -I/usr/include/opengl -lglut -lglu -lGL #-lcygipc
LINUX_OpenGL =  -lglut -lGLU -lGL -lm $(XLIBS) 
GL_LIBS += $(CYG_OpenGL) -lm 

INC_FILES= $(wildcard *.cpp) $(wildcard *.o)


INC_FILES= $(wildcard *.cpp) $(wildcard *.o)

all: planar

planar: planargl.c 
	$(CCGL) $(GL_CFLAGS) $^ $(LINUX_OpenGL) -o $@ 

clean:
	rm -rf *.exe planar
