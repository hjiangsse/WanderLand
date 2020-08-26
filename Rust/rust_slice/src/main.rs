fn main() {
    let s = String::from("hello world");
    let w = &s[5..];
    println!("the world is: {}", String::from(w));
    println!("the first index of the word: {}", find_first_word_end_index(&s));
}

fn find_first_word_end_index(s: &String) -> usize {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i
        }
    }

    s.len()
}
