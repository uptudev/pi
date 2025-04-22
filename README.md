# Pi 

A CLI project initialization tool written in C.

## Table of Contents

* [Installation](#installation)
* [Dependencies](#dependencies)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)

## Installation
Feel free to use a pre-built binary from the releases page. For building from
source, you will need a C compiler, CMake, and build system (GNU Make, Ninja,
etc) of some kind to build this project. CMake will automatically determine
which compiler and build system to use.

Linux users can use the `build.sh` script to streamline the process.

Run the following commands to build the project from scratch:

```bash
# Clone the repository to `./pi` and change current directory.
git clone https://github.com/uptudev/pi.git
cd ./pi

# Run the CMake configuration process, generating build files.
cmake .

# Build the executable
cmake --build . --config Release

# (Optional) install the executable to your system path
cmake --install .
```

This will build the executable with the filename `pi` on UNIX-like systems, and
`pi.exe` on Windows. You can now build projects with the binary.

## Dependencies

This tool uses various build tools and package managers to initialize projects.
The following dependencies are required at runtime for the following languages
to work:

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

The dependencies will be slowly removed from this list if I implement their
behaviour natively. Most of the dependencies enable complex initialization
processes that are not easily replicated in C via argument passing, so they
are used to streamline the process and are unlikely to be removed.

## Usage

The base initializer is run simply via `pi`, but if the project name and
language are given, this can streamline the initialization process.

```bash
pi
pi <project_name>
pi <project_name> <language>
pi <project_name> <language> -- [passthrough_args]
pi -l <language> -n <project_name> -- [passthrough_args]
```

Any arguments omitted will be prompted for by the program. The `--` is used to
separate the passthrough arguments from the program arguments; passthrough
arguments are passed directly to the subsequently-routed initialization script.

For instance, if you want to initialize a bare-bones Node.js project in `./my_project`,
you can run the following command:

```bash
pi my_project node -- -y
```

To create a new Svelte project with Bun, you can run the following command:

```bash
pi -l bun -- svelte@latest
```

which will query the user for a project name before creating the project through
the Svelte initialization script.


## Contributing

This shouldn't really need too much in terms of collaboration, but feel free to
send in a pull request if you have a feature you feel that I should add! I'm
always open to adding languages and frameworks to the project initializer, as it
has little overhead and is a good way to learn about new technologies.

## License

This code is licensed under the [MIT License](https://github.com/uptudev/pi/blob/main/LICENSE).
