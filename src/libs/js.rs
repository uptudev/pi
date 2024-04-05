use std::io::Write;

use colored::Colorize;
use crate::libs::base::{gen_readme, git_init};

pub fn init(proj_name: &String, framework: Option<Framework>) {
    let runtime = get_runtime();
    if runtime.is_none() {
        eprintln!("{}:\n{}",
                  "Error".bright_red().bold(),
                  "No valid JavaScript runtime found.");
        return;
    }
    let runtime = runtime.unwrap();
    let runtime_str = runtime.as_str();
    let mut runtime_chars: Vec<_> = runtime_str.chars().collect();
    runtime_chars[0] = runtime_chars[0].to_uppercase().nth(0).unwrap();
    let runtime_title: String = runtime_chars.into_iter().collect();
    let error_str = format!("Error initializing {} project", runtime_title);
    let create_str = format!("Creating {} project", runtime_title);

    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned() + "/" + proj_name;
    println!(
        "{}{}{}{}{}\x1b[90m", 
        create_str.purple().dimmed(), 
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

    if let Some(framework) = framework {
        match framework {
            Framework::REACT => {
                std::process::Command::new(runtime_str)
                    .args(["init", "react-app", "."])
                    .output()
                    .expect(&error_str);
            }
            Framework::VUE => {
                std::process::Command::new(runtime_str)
                    .args(["create", "vue@latest", "."])
                    .output()
                    .expect(&error_str);
            }
            Framework::SVELTE => {
                std::process::Command::new(runtime_str)
                    .args(["create", "svelte-app", "."])
                    .output()
                    .expect(&error_str);
            }
            Framework::TS => {
                if runtime == Runtime::BUN {
                    std::process::Command::new("bun")
                        .args(["init", "-y", "."])
                        .output()
                        .expect(&error_str);
                } else {
                    std::process::Command::new("npm")
                        .args(["install", "--save-dev", "typescript"])
                        .output()
                        .expect(&error_str);
                    std::process::Command::new("npx")
                        .args(["tsc", "--init"])
                        .output()
                        .expect(&error_str);
                    gen_ts();
                }
            }
        }
    } else {
        if runtime == Runtime::BUN {
            println!("Enter `index.js` to make a JavaScript project in Bun.");
            std::process::Command::new("bun")
                .args(["init", "."])
                .output()
                .expect(&error_str);
        } else {
            std::process::Command::new(runtime_str)
                .args(["init", "-y"])
                .output()
                .expect(&error_str);
        }
    }
    let readme_path = std::path::Path::new("./README.md");
    gen_readme(&proj_name, &readme_path).unwrap();
    git_init();
    println!("{}", "Done!".green().bold());
}

fn gen_ts() {
    let index_path = std::path::Path::new("./index.ts");
    let mut index_file = std::fs::File::create(index_path)
        .expect("Error creating index.ts");
    index_file.write_all(b"console.log('Hello, world!');");
}

pub fn get_runtime() -> Option<Runtime> {
    let handle = std::process::Command::new("bun")
        .arg("--version")
        .stdout(std::process::Stdio::null())
        .spawn();

    match handle {
        Ok(_) => Some(Runtime::BUN),
        Err(_) => {
            let handle = std::process::Command::new("npm")
                .arg("--version")
                .stdout(std::process::Stdio::null())
                .spawn();
            match handle {
                Ok(_) => Some(Runtime::NODE),
                Err(_) => None,
            }
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Runtime {
    BUN,
    NODE,
}

impl Runtime {
    pub fn as_str(&self) -> &str {
        match self {
            Runtime::BUN => "bun",
            Runtime::NODE => "node",
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Framework {
    REACT,
    VUE,
    SVELTE,
    TS,
}

impl Framework {
    pub fn init_command(&self) -> &str {
        match self {
            Framework::REACT => "react",
            Framework::VUE => "vue",
            Framework::SVELTE => "svelte",
            Framework::TS => "typescript",
        }
    }
}

