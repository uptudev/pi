use std::io::Write;
use colored::*;
use std::{io::stdout, process::Command};
use crate::libs::{
    rust,
    js,
    react,
    svelte,
    ts,
    vue,
};

pub fn start() {
    let mag_colour_code = get_trailing_char();
    let _ = 
        Command::new("clear")
        .status();
    let mut buffer = String::new();
    title();
    check_directory(&mut buffer, &mag_colour_code);
    get_language(&mut buffer, &mag_colour_code);
    stdout()
        .flush()
        .expect("Error flushing stdout.");
}

/// prints the title
pub fn title() {
    println!("{}", "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑".black().dimmed());
    println!(
        "{} {} {} {} {}", 
        "│".black().dimmed(), 
        "Project Initializer".bold().underline(), 
        "by".normal(), 
        "uptu".bold().cyan(), 
        "│".black().dimmed());
    println!("{}", "┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙".black().dimmed());
    println!("{}", "Please ensure you are in the correct directory and branch before proceeding.".bold().red());
    let cwd = std::env::current_dir()
        .expect("Error getting CWD")
        .as_path()
        .as_os_str()
        .to_str()
        .unwrap()
        .to_owned();
    println!("{} {}","CWD:".purple().dimmed(), cwd.purple());
}

/// queries the user with a prompt, returning an owned String
pub fn query(prompt: &String, buffer: &mut String, mag: &str) -> String {
    print!("{}{}", prompt, mag);
    std::io::stdout().flush().expect("Error flushing buffer");
    std::io::stdin()
        .read_line(buffer)
        .expect("Failed to read input to buffer");
    return buffer.trim().to_owned();
}

/// Gets system magenta colour code via tput
pub fn get_trailing_char() -> String {
    let mut magenta_res = std::process::Command::new("tput");
    magenta_res.args(["setaf", "5"]);
    let res = magenta_res.output().unwrap();
    String::from_utf8(res.stdout).unwrap()
}

/// queries the user to proceed after listing CWD
pub fn check_directory(buffer: &mut String, mag: &str) {
    let prompt = format!(
        "{} ({}/{}): ", 
        "Proceed?".yellow(),
        "Y".bold().green(),
        "N".red());

    let response = query(&prompt, buffer, mag);
    match response.as_str() {
        "y" | "Y" | "" => println!(""),
        "n" | "N" => clear_exit(),
        _ => {
            buffer.clear();
            println!(
                "{}; please enter {} or {}.", 
                "Invalid response".bold().red(), 
                "Y".bold().green(), 
                "N".bold().red());
            check_directory(buffer, mag);
        },
    }
}

fn clear_exit() {
    let _ = 
        std::process::Command::new("clear")
        .status();
    std::process::exit(0);
}

/// helper fn for get_language; handles queried response
fn route_response(buffer: &mut String, response: String, mag: &str) {
    match response.as_str() {
        "ls" => list_languages(buffer, mag),
        "rust" => rust::init(buffer, mag),
        "js" => js::init(buffer),
        "ts" => ts::init(buffer),
        "react" => react::init(buffer),
        "vue" => vue::init(buffer),
        "svelte" => svelte::init(buffer),
        _ => {
            buffer.clear();
            println!(
                "{}; please enter a valid language.\n{} {} {}", 
                "Invalid response".bold().red(), 
                "(or type".black().dimmed(),
                "ls".purple(),
                "to list all valid languages)".black().dimmed());
            get_language(buffer, mag);
        },
    }
}

/// query user for the project language, then run the corresponding language_init() function
pub fn get_language(buffer: &mut String, mag: &str) {
    buffer.clear();
    let prompt = format!(
        "{} {} {}: ",
        "What".yellow(),
        "language".cyan().bold(),
        "is this project for?".yellow());

    let response = query(&prompt, buffer, mag).to_lowercase();
    route_response(buffer, response, mag);
}

/// called when 'ls' is given as a response to `get_language()`
fn list_languages(buffer: &mut String, mag: &str) {
    println!("{}",
        "rust\njs\nts\nreact\nvue\nsvelte\n"
        .blue()
        .dimmed());
    get_language(buffer, mag);
}

/// queries user for project name, returns an owned string
pub fn get_project_name(buffer: &mut String, mag: &str) -> String {
    buffer.clear();
    let prompt = format!(
        "{}{}: ",
        "Please enter the ".yellow(), 
        "project name".cyan().bold());
    query(&prompt, buffer, mag).to_string()
}

