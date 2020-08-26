fn main() {
    let number = 3;
    if number < 5 {
        println!("condition is true!");
    } else {
        println!("condition is false!");
    }

    let arr = [1,2,4,3,5];
    for i in arr.iter() {
        println!("{}", i);
    }
}
