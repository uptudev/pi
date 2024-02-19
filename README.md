# pi 

A CLI project initializer written in Rust.

## Table of Contents

* [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Additional Information](#additional-information)

## Installation

[Install Rust](https://www.rust-lang.org/tools/install) if you haven't, then clone this repo and build using the following commands:

```bash
git clone https://github.com/uptudev/pi
cd ./pi
cargo build --release
```

This will build your executable in the `./target/release/` folder, with the filename `pi` on Unix-like systems, and `pi.exe` on Windows. Simply move this file to wherever your OS pulls binaries from, and you can build projects with the `pi` command.

## Usage

The base initializer is run simply via `pi`, but if the project name and language are given, this can streamline the initialization process.

## Contributing

This shouldn't really need too much in terms of collaboration, but feel free to send in a pull request if you have a feature you feel that I should add!

## License

This code is licensed under the [MIT License](https://github.com/uptudev/pi/blob/main/LICENSE).
