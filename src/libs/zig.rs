use colored::*;
use crate::libs::base::{query, gen_readme};

pub fn init(buffer: &mut String, mag: &str, proj_name: &String) {
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned();
    println!(
        "{}{}{}{}{}\x1b[90m", 
        "Creating Zig project ".purple().dimmed(), 
        proj_name.purple().bold(), 
        " in ".purple().dimmed(), 
        cwd.purple(), 
        "...".purple().dimmed());

    let mut handle = std::process::Command::new("mkdir")
        .arg(proj_name)
        .spawn()
        .expect("Error spawning child process.");
    let exit_status = handle.wait().unwrap();
    if !exit_status.success() {
        panic!("Couldn't make file.");
    }

    let mut handle = std::process::Command::new("cd")
        .arg("./".to_string() + proj_name)
        .spawn()
        .expect("Error spawning child process.");
    let exit_status = handle.wait().unwrap();
    if !exit_status.success() {
        panic!("Couldn't change directories.");
    }
    let mut handle = std::process::Command::new("zig")
        .arg("init")
        .spawn()
        .expect("Error spawning child process.");
    let exit_status = handle.wait().unwrap();
    let proj_dir = format!("./{}", proj_name);
    let readme_dir = proj_dir + "/README.md";
    let readme_path = std::path::Path::new(&readme_dir);
    println!("\x1b[0m");
    gen_readme(&proj_name, &readme_path).unwrap();
    if exit_status.success() {
        println!("{}", "Done!".green().bold());
    }
}


