use colored::*;
use crate::libs::base::{gen_readme, git_init};

pub fn init(proj_name: &String) {
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned() + "/" + proj_name;
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

    let target_dir = std::path::Path::new(&cwd);
    std::env::set_current_dir(target_dir)
        .expect("Couldnt change directories.");

    std::process::Command::new("zig")
        .arg("init")
        .output()
        .expect("Error spawning child process.");
    let readme_path = std::path::Path::new("./README.md");
    gen_readme(&proj_name, &readme_path).unwrap();
    git_init();
    println!("{}", "Done!".green().bold());
}
