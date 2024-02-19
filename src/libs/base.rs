use std::io::Write;
use colored::*;
use std::{io::{stdout, Result}, process::Command, fs};
use crate::libs::{
    js, react, rust, svelte, ts, vue, zig
};

pub fn start(name: Option<String>, lang: Option<String>) {
    let mag_colour_code = get_trailing_char();
    let _ = 
        Command::new("clear")
        .status();
    let mut buffer = String::new();
    title();
    check_directory(&mut buffer, &mag_colour_code);

    // option destruction syntax is hot garbage ngl
    let proj_name = if let Some(n) = name { 
        n
    } else {
        get_project_name(&mut buffer, &mag_colour_code)
    };
    let lang = if let Some(l) = lang {
        l
    } else {
        get_language(&mut buffer, &mag_colour_code)
    };
    route_response(&mut buffer, lang, &mag_colour_code, &proj_name);
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
    println!("{}", "Please ensure you are in the parent directory of your intended project location before proceeding.".bold().red());
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
    buffer.trim().to_owned()
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
fn route_response(buffer: &mut String, response: String, mag: &str, proj_name: &String) {
    match response.as_str() {
        "ls" => list_languages(buffer, mag),
        "rust" => rust::init(buffer, mag, proj_name),
        "js" => js::init(buffer),
        "ts" => ts::init(buffer),
        "react" => react::init(buffer),
        "vue" => vue::init(buffer),
        "svelte" => svelte::init(buffer),
        "zig" => zig::init(buffer),
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
pub fn get_language(buffer: &mut String, mag: &str) -> String {
    buffer.clear();
    let prompt = format!(
        "{} {} {}: ",
        "What".yellow(),
        "language".cyan().bold(),
        "is this project for?".yellow());
    query(&prompt, buffer, mag).to_lowercase()
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

/// creates a README.md in the target directory in a useful format
pub fn gen_readme(proj_name: &String, dir: &std::path::Path) -> Result<()>{
    let mut base_readme: String = r#"# 

**[Short, memorable description of your project]**

## Table of Contents

* [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Additional Information](#additional-information)

## Installation

**Clearly describe how to install your project.** This may involve specifying dependencies, prerequisites, and build instructions. Use code blocks, links, and step-by-step guides for clarity.

## Usage

**Provide clear and concise instructions on how to use your project.** Explain its functionalities, features, and common use cases. Include examples, screenshots, or GIFs if helpful.

**Tips:**

* Break down instructions into logical steps.
* Use bullet points for succinct explanations.
* Consider creating a separate "Getting Started" guide for beginners.

## Contributing

**Outline your contribution guidelines.** Explain how users can contribute to your project, whether through code, bug reports, or documentation improvements. Specify preferred code style, pull request format, and testing procedures.

## License

**Specify the license under which your project is distributed.** Use clear and concise language, and link to the full license text in the `LICENSE` file.

## Additional Information

**Include any other relevant information you want to share.** This could be links to related projects, documentation, support channels, or your contact information.

**Remember:**

* Keep your README.md file concise and focused.
* Use clear headings, formatting, and visuals for readability.
* Update your README.md file regularly to reflect changes in your project.
"#.to_string();
    base_readme.insert_str(2, proj_name);
    let mut file = fs::File::create(dir)?;
    file.write_all(base_readme.as_bytes())
}

/// Builds a help template (because version number may change the length of the box needed)
pub fn gen_help_template() -> String {
    const VER_LEN: usize = env!("CARGO_PKG_VERSION").len() - 5;
    const BASE: &'static str = "\
{before-help}
\x1b[0;35m┍━━━━━━━━┑
│\x1b[1;95;4m{name}\x1b[0;95;4m {version}\x1b[0;35m│
┕━━━━━━━━┙\x1b[0m
{author-with-newline}
{about-with-newline}
{usage-heading} {usage}

{all-args}{after-help}
";

    let mut out = BASE.to_string();
    let mut i = VER_LEN;

    while i > 0 {
        out.insert(103 + (VER_LEN - i) * 3, '━');
        out.insert(24, '━');
        i -= 1;
    }

    out
}
