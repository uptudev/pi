use std::io::Write;

pub fn query(prompt: &String, buffer: &mut String) {
    print!("{}", prompt);
    std::io::stdout().flush().expect("Error flushing buffer");
    std::io::stdin()
        .read_line(buffer)
        .expect("Failed to read input to buffer");
}
