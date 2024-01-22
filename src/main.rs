mod libs;

use libs::*;

fn main() {
    let mut buffer = String::new();
    title();
    check_directory(&mut buffer);
    get_language(&mut buffer);
}
