fn main() {
    let mut s1 = String::from("Hello References");
    let len = cal_str_length(&s1);
    println!("the length of s1: {}", len);
    println!("now you can also use the string: {}", s1);

    append_tail(&mut s1);
    println!("now the new string is: {}", s1);

    let ref1 = &s1;
    let ref2 = &s1;
    let ref3 = &mut s1;

    println!("len1: {}", cal_str_length(ref1));
    println!("len2: {}", cal_str_length(ref2));

    let dangle_ref = dangle();
}

fn cal_str_length(s: &String) -> usize {
    s.len()
}

fn append_tail(s: &mut String) {
    s.push_str(" tail");
}

fn dangle() -> &String {
    let s = String::from("google");
    &s
}
