#[derive(Debug, Copy, Clone)]
struct Test {
    a: i32,
    b: u64,
}

fn main() {
    let x = Test { a: 10, b: 20 };
    let y = x;
    println!("{:?}", x);
}
