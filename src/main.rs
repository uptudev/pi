mod libs;
use libs::base::start;
use clap::builder::styling::{AnsiColor, Effects, Styles};
use clap::Parser;

/* Argument parsing */

/// Help text styling
fn styles() -> Styles {
    Styles::styled()
        .header(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .usage(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .literal(AnsiColor::Blue.on_default())
        .placeholder(AnsiColor::Green.on_default())
}

/// The --help string
const HELP: &'static str = "\x1b[0;1;95;4mPi\x1b[0m is a CLI \x1b[34mproject initializer\x1b[0m which uses per-language build tools to create project directories populated with a full project template.";

/// The arguments to be pushed to the rest of the program
#[derive(Parser, Debug)]
#[command(version, about = HELP, styles = styles(), long_about = None, next_line_help = true)]
struct Args {
    /// The name of the project
    #[arg(name = "NAME", short = 'n', long = "name", verbatim_doc_comment)]
    name: Option<String>,

    /// The target language of the project
    #[arg(name = "LANGUAGE", short = 'l', long = "lang", verbatim_doc_comment)]
    lang: Option<String>,
}


fn main() {
    let args = Args::parse();
    start(args.name, args.lang);
}
