use colored::*;
use crate::libs::base::{query, get_project_name};

fn get_is_lib(buffer: &mut String, mag: &str) -> String {
    buffer.clear();
    let prompt = format!(
        "{} {} {} {} {}: ",
        "Is this a".yellow(),
        "binary".cyan().bold(),
        "or".yellow(),
        "library".cyan().bold(),
        "project?".yellow());
    let response = query(&prompt, buffer, mag);
    match response.as_str() {
        "b" | "bin" | "binary" => "--bin".to_string(),
        "l" | "lib" | "library" => "--lib".to_string(),
        _ => get_is_lib(buffer, mag),
    }
}

pub fn init(buffer: &mut String, mag: &str) {
    let proj_name = get_project_name(buffer, mag);
    let is_lib = get_is_lib(buffer, mag);
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned();
    println!(
        "{}{}{}{}{}", 
        "Creating Rust project ".purple().dimmed(), 
        proj_name.purple().bold(), 
        " in ".purple().dimmed(), 
        cwd.purple(), 
        "...".purple().dimmed());
    let mut handle = std::process::Command::new("cargo")
        .args(["new", &*proj_name, &*is_lib, "--quiet"])
        .spawn()
        .expect("Error spawning child process.");
    let exit_status = handle.wait().unwrap();
    if exit_status.success() {
        println!("{}", "Done!".green().bold());
    }
}

