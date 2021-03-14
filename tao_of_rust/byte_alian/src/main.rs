/*
struct A {
a: u8,
b: u32,
c: u16,
}
 */

use std::ops::Drop;

#[derive(Debug)]
struct S(i32);

impl Drop for S {
    fn drop(&mut self) {
        println!("drop {}", self.0);
    }
}

fn main() {
    let x = S(1);
    println!("create x: {:?}", x);
    {
        let y = S(2);
        println!("create y: {:?}", y);
        println!("exit inner scope: ");
    }
    println!("exit main");
    /*
    println!("{:?}", std::mem::size_of::<A>());
    let x: i32 = 10;
    println!("x is {}", x);

    let y: i32;
    if true {
        y = 1;
    } else {
        y = 2;
    }

    println!("Finally the y is {}", y);
     */

    /*
    let x: i32;
    let mut y = 0;
    loop {
        y += 1;
        if y > 3 {
            x = 2;
            break;
        }
    }
    println!("{}", x);
     */

    /*
    let x = 32;
    let mut y = Box::new(5);
    println!("{:p}", y);
    let x2 = x;
    let y2 = y;
    println!("{:p}", y2);
    y = Box::new(10);
    println!("{:p}", y);
     */
    /*
    let s = String::from("This is a string");
    println!("{}", s);
    */
}
