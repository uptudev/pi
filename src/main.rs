mod libs;
use libs::base::{gen_help_template, start};
use clap::builder::styling::{AnsiColor, Effects, Styles};
use clap::Parser;

/* Argument parsing */

/// Help text styling
fn styles() -> Styles {
    Styles::styled()
        .header(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .usage(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .literal(AnsiColor::BrightBlue.on_default())
        .placeholder(AnsiColor::Green.on_default())
}

/// The about and author strings for --help
const ABOUT: &'static str = "\x1b[0;1;95;4mPi\x1b[0m is a CLI \x1b[94mproject initializer\x1b[0m which uses per-language build tools to create project directories populated with a full project template.";
const AUTHOR: &'static str = "by \x1b[0;93muptu\x1b[0m <\x1b[33muptu@uptu.dev\x1b[0m>";

#[derive(Parser, Debug)]
#[command(                      // This preprocessor block deals mostly with the styling of --help
    version,                    // enables `-v` and `--version` to print the version
    about = ABOUT,              // the project about text const goes here
    author = AUTHOR,            // the above author text const goes here
    styles = styles(),          // uses `styles()` fn to format most of the output
    long_about = None,          // the long version of `-h`, `--help` has no special text
    next_line_help = true,      // option help info is given on a new line
    help_template = gen_help_template()
)]
/// The arguments to be pushed to the rest of the program
struct Args {
    /// Name of the project
    #[arg(
        name = "NAME",          // the text to put in the placeholder in the help text
        short = 'n',            // the short version of the arg flag (i.e. `-n` here)
        long = "name",          // the long version of the arg flag (i.e. `--name` here)
        verbatim_doc_comment    // speeds up preprocessing of the doc comment above
    )]
    name: Option<String>,

    /// Target language of the project
    #[arg(
        name = "LANGUAGE",      // see above for field documentation
        short = 'l', 
        long = "lang", 
        verbatim_doc_comment
    )]
    lang: Option<String>,
}


fn main() {
    let args = Args::parse();
    start(args.name, args.lang);
}
