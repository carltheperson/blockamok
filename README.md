<h1 align="center">Blockamok</h1>

# Compiling

Linking the SDL_2 library can be a bit of a challenge. I recommend you find out yourself how to do that for your system. Here is what worked on my mac with `homebrew`:

brew install sdl2
brew install sdl2_ttf
brew install pkg-config

````

```sh
gcc src/*.c $(sdl2-config --cflags --libs) -o blockamok && ./blockamok
gcc src/**/*.c  -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 -o blockamok
````

Get compiler flags pkg-config --cflags --libs SDL2_ttf

# Running

```sh
./blockamok
```

# VS Code note

A quick way to give VS Code knowledge of the SDL library is this (for my mac):

```sh
mkdir include && cp /opt/homebrew/include/SDL2/* ./include/
cp /opt/homebrew/opt/sdl_ttf/include/SDL/* ./include/
```

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

gcc src/\*.c `sdl2-configs --cflags --libs` -I/opt/homebrew/opt/sdl_ttf/include/SDL -lSDL2_ttf -o blockamok && ./blockamok

gcc src/\*_/_.c -D_THREAD_SAFE -I/opt/homebrew/include/SDL2 -I/opt/homebrew/Cellar/harfbuzz/5.3.1/include/harfbuzz -I/opt/homebrew/Cellar/graphite2/1.3.14/include -I/opt/homebrew/Cellar/glib/2.74.0/include/glib-2.0 -I/opt/homebrew/Cellar/glib/2.74.0/lib/glib-2.0/include -I/opt/homebrew/opt/gettext/include -I/opt/homebrew/Cellar/pcre2/10.40/include -I/opt/homebrew/opt/freetype/include/freetype2 -I/opt/homebrew/include -I/opt/homebrew/include/SDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.20.1/lib -L/opt/homebrew/lib -lSDL2_ttf -lSDL2 -o blockamok
