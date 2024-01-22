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

    match &*(*buffer).trim() { // this line is disgusting
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

    let response = query(&prompt, buffer);
    match response {
        "ls" => list_languages(buffer),
        _ => {},
    }
}
