mod libs;

use libs::*;
use colored::*;

fn main() {
    let mut user_input = String::new();
    title();
    check_directory(&mut user_input);
}

fn title() {
    println!("{}", "┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑".black().dimmed());
    println!(
        "{}{}{}{}{}", 
        "│".black().dimmed(), 
        " Project Initializer".bold(), 
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
    println!("{}{}","CWD: ".dimmed(), cwd.purple());
}

fn check_directory(user_input_buffer: &mut String) {
    let prompt = format!(
        "{} ({}/{}): ", 
        "Proceed?".yellow(),
        "Y".bold().green(),
        "N".red());
    query(&prompt, user_input_buffer);

    match &*(*user_input_buffer).trim() { // this line is disgusting
        "y" | "Y" | "" => println!(""),
        "n" | "N" => return,
        _ => {
            user_input_buffer.clear();
            check_directory(user_input_buffer);
        },
    }
}
