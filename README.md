<h1 align="center">Blockamok</h1>

# Compiling

Linking the SDL_2 library can be a bit of a challenge. I recommend you find out yourself how to do that for your system. Here is what worked on my mac with `homebrew`:

```sh
brew install sdl2
```

```sh
gcc src/**/*.c  -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 -o blockamok
```

# Running

```sh
./blockamok
```

# VS Code note

A quick way to give VS Code knowledge of the SDL library is this:

```sh
mkdir include && cp /opt/homebrew/include/SDL2/* ./include/
```

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
