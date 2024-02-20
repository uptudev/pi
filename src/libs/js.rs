use colored::Colorize;
use crate::libs::base::{gen_readme, git_init};

pub fn init(proj_name: &String) {
    let runtime = get_runtime();
    match runtime {
        Runtime::BUN => {
            init_bun(proj_name);
            let readme_path = std::path::Path::new("./README.md");
            gen_readme(&proj_name, &readme_path).unwrap();
            git_init();
            println!("{}", "Done!".green().bold());
        },
        Runtime::NODE => {
            init_node(proj_name);
            let readme_path = std::path::Path::new("./README.md");
            gen_readme(&proj_name, &readme_path).unwrap();
            git_init();
            println!("{}", "Done!".green().bold());
        },
        Runtime::NONE => {
            eprintln!("{}:\n{}",
                      "Error".bright_red().bold(),
                      "No valid JavaScript runtime found.");
        },
    }
}

fn init_bun(proj_name: &String) {
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned() + "/" + proj_name;
    println!(
        "{}{}{}{}{}\x1b[90m", 
        "Creating Bun project ".purple().dimmed(), 
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


    std::process::Command::new("bun")
        .args(["init", "-y"])
        .output()
        .expect("Error initializing bun project");
}

fn init_node(proj_name: &String) {
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned() + "/" + proj_name;
    println!(
        "{}{}{}{}{}\x1b[90m", 
        "Creating Node project ".purple().dimmed(), 
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


    std::process::Command::new("npm")
        .args(["init", "-y"])
        .output()
        .expect("Error initializing bun project");

}

fn get_runtime() -> Runtime {
    let handle = std::process::Command::new("bun")
        .arg("--version")
        .stdout(std::process::Stdio::null())
        .spawn();

    match handle {
        Ok(_) => Runtime::BUN,
        Err(_) => {
            let handle = std::process::Command::new("npm")
                .arg("--version")
                .stdout(std::process::Stdio::null())
                .spawn();
            match handle {
                Ok(_) => Runtime::NODE,
                Err(_) => Runtime::NONE,
            }
        }
    }
}

#[derive(Debug)]
enum Runtime {
    BUN,
    NODE,
    NONE,
}

