# Pi 

A CLI project initialization tool written in C.

## Table of Contents

* [Installation](#installation)
* [Dependencies](#dependencies)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)

## Installation

You will need a C compiler of some kind (or a pre-built binary from the releases page) to build this project. The current make system supports Clang, GCC, and Zig, but you can use your own compiler (in place of `cc`) with the command `cc -I include src/**/* src/pi.c -o pi` in the base directory.

To make it easier, a simplified configure/make system is provided. Simply run the following commands to build the project from scratch:

```bash
# Clone the repository to `./pi` and change current directory.
git clone https://github.com/uptudev/pi.git
cd ./pi

# Run the configure script and make the project.
./configure
make
```

This will build the executable with the filename `pi` on UNIX-like systems, and `pi.exe` on Windows. Move this file to your `PATH`, and you can build projects with the `pi` command. 

If you want to install the binary to your system on Linux or BSD, you can run the following command, which will install the binary to `/usr/local/bin` by default. If you want to install it to a different location, you can change the `INSTALL_DIR` variable in the `Makefile` before running the following command:

```bash
sudo make install
```

*For local installation, (`INSTALL_DIR:=~/.local/bin`), `sudo` is unnecessary*.

## Dependencies

This tool uses various build tools and package managers to initialize projects. The following dependencies are required for the following languages to work:

* C/C++: *No runtime dependencies*.
* Go: [Go](https://golang.org/)
* Haskell: [Cabal](https://www.haskell.org/cabal/)/[Stack](https://docs.haskellstack.org/en/stable/)
* JS/TS: [Node.js](https://nodejs.org/)/[Bun](https://bun.sh/)
* Lua: *No runtime dependencies*.
* OCaml: [Dune](https://dune.build/)
* Ruby: [Rubygems](https://rubygems.org/)
* Rust: [Cargo](https://doc.rust-lang.org/cargo/)
* V: [V](https://vlang.io/)
* Zig: [Zig](https://ziglang.org/)

Once all languages have been implemented, the dependencies will be slowly removed from this list if I implement their behaviour natively. Most of the dependencies enable complex initialization processes that are not easily replicated in C via argument passing, so they are used to streamline the process and are unlikely to be removed.

## Usage

The base initializer is run simply via `pi`, but if the project name and language are given, this can streamline the initialization process.

```bash
pi
pi <project_name>
pi <project_name> <language>
pi <project_name> <language> -- [passthrough_args]
pi -l <language> -n <project_name> -- [passthrough_args]
```

Any arguments omitted will be prompted for by the program. The `--` is used to separate the passthrough arguments from the program arguments; passthrough arguments are passed directly to the subsequently-routed initialization script.

For instance, if you want to initialize a bare-bones Node.js project in `./my_project`,
you can run the following command:

```bash
pi my_project node -- -y
```

To create a new Svelte project with Bun, you can run the following command:

```bash
pi -l bun -- svelte@latest
```

, which will query the user for a project name before creating the project through the svelte initialization script.


## Contributing

This shouldn't really need too much in terms of collaboration, but feel free to send in a pull request if you have a feature you feel that I should add! I'm always open to adding languages and frameworks to the project initializer, as it has little overhead and is a good way to learn about new technologies.

## License

This code is licensed under the [MIT License](https://github.com/uptudev/pi/blob/main/LICENSE).
