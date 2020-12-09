use std::borrow::Cow;
use std::path::Path;

fn main() {
    let path = Path::new("foo.txt");
    match path.to_string_lossy() {
        Cow::Borrowed(_str_ref) => println!("path is valid UTF-8"),
        Cow::Owned(_new_string) => println!("path is not valid UTF-8"),
    }
}
