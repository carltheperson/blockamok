<h1 align="center">Blockamok</h1>

<p align="center">You accidentally fly your spaceship into a wormhole. To your shock, you find yourself in an alternate dimension filled with blocks. The throttle on your spaceship is broken and keeps increasing the speed. How far can you make it?</p>

# Installing dependencies

You need: `sdl2`, `sdl2_ttf`, and `pkg-config` (to generate compiler flags)

If you use Homebrew, you can run this:

```sh
make install_dependencies_mac
```

# Compiling

```sh
make compile
```

Note: If this fails, make sure that the following line generates a bunch of compiler flags: `pkg-config --cflags --libs SDL2_ttf`

# Running

```sh
make run
```

Or:

```sh
./blockamok
```

# VS Code note

A quick way to give VS Code knowledge of the SDL library is this (for my mac):

```sh
make satisfy_vscode_mac
```

This will add the dependencies to `./include`

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
