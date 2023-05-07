#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp 					\
	   src/Texture.cpp 					\
	   src/Game.cpp 					\
	   src/Entity.cpp 					\
	   src/Map.cpp						\
	   src/Time.cpp						\
	   src/LevelsAttribute.cpp			\
	   src/Player.cpp					\


#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL2-2.26.3\include					\
				-IC:\SDL2-2.26.3\SDL2_image-2.6.3\include  	\
				-IC:\SDL2-2.26.3\SDL2_mixer-2.6.3\include	\
				-IC:\SDL2-2.26.3\SDL2_ttf-2.20.2\include	\


#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\SDL2-2.26.3\lib						\
				-LC:\SDL2-2.26.3\SDL2_image-2.6.3\lib		\
				-LC:\SDL2-2.26.3\SDL2_mixer-2.6.3\lib		\
				-LC:\SDL2-2.26.3\SDL2_ttf-2.20.2\lib		\

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -w


#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32		\
				-lSDL2main 		\
				-lSDL2 			\
				-lSDL2_image 	\
				-lSDL2_ttf 		\
				-lSDL2_mixer	\

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Restless_Syndrome.exe

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)