use std::io::Write;
use colored::*;

pub fn title() {
    println!("{}", "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑".black().dimmed());
    println!(
        "{}{}{}{}{}", 
        "│ ".black().dimmed(), 
        "Project Initializer".bold().underline(), 
        " by".normal(), 
        " uptu".bold().cyan(), 
        " │".black().dimmed());
    println!("{}", "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙".black().dimmed());
    println!("{}", "Please ensure you are in the correct directory and branch before proceeding.".bold().red());
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned();
    println!("{}{}","CWD: ".purple().dimmed(), cwd.purple());
}

pub fn query<'a>(prompt: &String, buffer: &'a mut String) -> &'a str {
    print!("{}", prompt);
    std::io::stdout().flush().expect("Error flushing buffer");
    std::io::stdin()
        .read_line(buffer)
        .expect("Failed to read input to buffer");
    return buffer.trim();
}

pub fn check_directory(buffer: &mut String) {
    let prompt = format!(
        "{} ({}/{}): ", 
        "Proceed?".yellow(),
        "Y".bold().green(),
        "N".red());
    let response = query(&prompt, buffer);

    match response {
        "y" | "Y" | "" => println!(""),
        "n" | "N" => return,
        _ => {
            buffer.clear();
            check_directory(buffer);
        },
    }
}

fn list_languages(buffer: &mut String) {
    println!("{}",
        "rust\njs\nts\nreact\nvue\nsvelte\n"
        .blue()
        .dimmed());
    get_language(buffer);
}

pub fn get_language(buffer: &mut String) {
    buffer.clear();
    let prompt = format!(
        "{} {} {} {}{}{}: ",
        "What".yellow(),
        "language".cyan().bold(),
        "is this project for?".yellow(),
        "(type '".dimmed().black(),
        "ls".purple(),
        "' for a list)".dimmed().black());

    let response = query(&prompt, buffer).to_lowercase();
    match response.as_str() {
        "ls" => list_languages(buffer),
        "rust" => rust_init(buffer),
        "js" => js_init(buffer),
        "ts" => ts_init(buffer),
        "react" => react_init(buffer),
        "vue" => vue_init(buffer),
        "svelte" => svelte_init(buffer),
        _ => {},
    }
}

fn get_project_name(buffer: &mut String) -> String {
    buffer.clear();
    let prompt = format!(
        "{}{}: ",
        "Please enter the ".yellow(), 
        "project name".cyan().bold());
    query(&prompt, buffer).to_string()
}

fn get_is_lib(buffer: &mut String) -> String {
    buffer.clear();
    let prompt = format!(
        "{} {} {} {} {}: ",
        "Is this a".yellow(),
        "binary".cyan().bold(),
        "or".yellow(),
        "library".cyan().bold(),
        "project?".yellow());
    let response = query(&prompt, buffer);
    match response {
        "b" | "bin" | "binary" => "--bin".to_string(),
        "l" | "lib" | "library" => "--lib".to_string(),
        _ => get_is_lib(buffer),
    }
}

fn rust_init(buffer: &mut String) {
    let proj_name = get_project_name(buffer);
    let is_lib = get_is_lib(buffer);
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

fn js_init(buffer: &mut String) {
    todo!("JavaScript init script needed");
}

fn ts_init(buffer: &mut String) {
    todo!("TypeScript init script needed");
}

fn react_init(buffer: &mut String) {
    todo!("React init script needed");
}

fn vue_init(buffer: &mut String) {
    todo!("Vue init script needed");
}

fn svelte_init(buffer: &mut String) {
    todo!("Svelte init script needed");
}
