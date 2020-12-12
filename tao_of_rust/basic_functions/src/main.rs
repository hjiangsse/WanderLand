fn other_function(x :u32) {
    println!("The value of the parameter is: {}", x);
}

fn another_function(x :u32, y :u32) {
    println!("The value of the first parameter is: {}", x);
    println!("The value of the second parameter is: {}", y);
}

fn just_five() -> i32 {
    5
}

fn main() {
    other_function(10);
    another_function(10, 20);

    let x = 5;
    let y = {
        let x = 3;
        x + 1
    };
    println!("the value of y is: {}", y);

    println!("the return value of the just_five: {}", just_five());
}
