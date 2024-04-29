mod libs;
use libs::base::start;
use clap::builder::styling::{AnsiColor, Effects, Styles};
use clap::Parser;

/* Argument parsing */

fn styles() -> Styles {
    Styles::styled()
        .header(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .usage(AnsiColor::Yellow.on_default() | Effects::BOLD)
        .literal(AnsiColor::BrightBlue.on_default())
        .placeholder(AnsiColor::Green.on_default())
}

fn gen_help_template() -> String {
    const VER_LEN: usize = env!("CARGO_PKG_VERSION").len() - 5;
    const BASE: &'static str = "\
\x1b[0;90m┍━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┑
│\x1b[1;4;96m{name} v{version}\x1b[0m {author}\x1b[0;90m│
┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┙\x1b[0m
{before-help}
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

const ABOUT: &'static str = "\x1b[0;1;95;4mPi\x1b[0m is a CLI \x1b[94mproject initializer\x1b[0m which uses per-language build tools to create project directories populated with a full project template.";
const AUTHOR: &'static str = "by \x1b[0;93muptu\x1b[0m <\x1b[33muptu@uptu.dev\x1b[0m>";

#[derive(Parser, Debug)]
#[command(
    version,                    // enables `-v` and `--version` to print the version
    about = ABOUT,
    author = AUTHOR,
    styles = styles(),
    long_about = None,          // the long version of `-h`, `--help` has no special text
    next_line_help = true,      // option help info is given on a new line
    help_template = gen_help_template()
)]
struct Args {
    /// Name of the project
    #[arg(
        name = "NAME",
        short = 'n',
        long = "name",
        verbatim_doc_comment    // speeds up preprocessing of the doc comment above
    )]
    name: Option<String>,
    /// Target language of the project
    #[arg(
        name = "LANGUAGE",
        short = 'l', 
        long = "lang", 
        verbatim_doc_comment
    )]
    lang: Option<String>,
}

/* Entry point */

fn main() {
    let args = Args::parse();
    start(args.name, args.lang);
}
