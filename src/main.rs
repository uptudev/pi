mod libs;

use libs::*;
use std::{io::Write, io::stdout, process::Command};

fn main() {
    let _ = 
        Command::new("clear")
        .status();
    let mut buffer = String::new();
    title();
    check_directory(&mut buffer);
    get_language(&mut buffer);
    stdout()
        .flush()
        .expect("Error flushing stdout.");
}
