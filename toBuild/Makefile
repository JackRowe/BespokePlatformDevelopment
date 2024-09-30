TARGET_NAME = sdl_display
CXX = g++
STRIP = strip
SDL_FLAGS = `sdl2-config --cflags`
LDLIBS = -lGLESv2 -lgbm -ldrm -ldl -lz -lpthread -lfreetype -lasound -lvorbisfile /usr/arm-linux-gnueabihf/lib_evercade/libSDL2_mixer.a /usr/arm-linux-gnueabihf/lib_evercade/libSDL2.a /usr/arm-linux-gnueabihf/lib_evercade/libSDL2_ttf.a /usr/arm-linux-gnueabihf/lib_evercade/libSDL2_image.a /usr/lib/arm-linux-gnueabihf/libpng16.a

SOURCES = $(shell find -name "*.cpp")

ifeq ($(DEBUG), 1)
	CXXFLAGS = -g -std=c++17 -I.
else
	CXXFLAGS = -O2 -std=c++17 -I.
endif

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET_NAME)
release: $(TARGET_NAME)
	$(CROSS_PREFIX)$(STRIP) $(TARGET_NAME)

$(TARGET_NAME) : $(OBJECTS)
	$(CROSS_PREFIX)$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OBJECTS) $(LDLIBS) -o $(TARGET_NAME)

%.o : %.cpp
	$(CROSS_PREFIX)$(CXX) $(CXXFLAGS) $(SDL_FLAGS) -c $< -o $@

clean:
	rm -f $(TARGET_NAME) $(shell find -name "*.o")

.PHONY: all clean release