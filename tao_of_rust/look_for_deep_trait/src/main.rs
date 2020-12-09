/*
trait Add<RHS, Output> {
    fn my_add(self, rhs: RHS) -> Output;
}

impl Add<i32, i32> for i32 {
    fn my_add(self, rhs: i32) -> i32 {
        (self + rhs) as i32
    }
}

impl Add<u32, i32> for u32 {
    fn my_add(self, rhs: u32) -> i32 {
        (self + rhs) as i32
    }
}
 */

//try reload add trait for integer
/*
trait Add<RHS = Self> {
    type Output;
    fn add(self, rhs: RHS) -> Self::Output;
}

impl Add<u64> for u32 {
    type Output = u64;
    fn add(self, other: u64) -> Self::Output {
        (self as u64) + other
    }
}
*/

use std::ops::Add;
//implement add trait for user defined type
/*
#[derive(Debug)]
struct Color {
    red: u32,
    green: u32,
    blue: u32,
}

impl Add for Color {
    type Output = Color;
    fn add(self, other: Color) -> Self::Output {
        Color {
            red: self.red + other.red,
            green: self.green + other.green,
            blue: self.blue + other.blue,
        }
    }
}

impl Color {
    fn new(r: u32, g: u32, b: u32) -> Self {
        Color {
            red: r,
            green: g,
            blue: b,
        }
    }
}
*/

//trait inheritence
trait Fly {
    fn get_fly(&self, dist: u32) {
        println!("I believe i can fly {} kms away!", dist);
    }
}

trait Jump {
    fn get_jump(&self, high: u32) {
        println!("I believe i can jump {} meters high!", high);
    }
}

trait Sing: Fly + Jump {
    fn get_sing(&self, songs: u32) {
        println!(
            "i can jump and fly, i will sing {} songs for this world!",
            songs
        );
    }
}

struct LarkBird {}

impl Fly for LarkBird {}
impl Jump for LarkBird {}
impl Sing for LarkBird {}

fn main() {
    let larkbird = LarkBird {};
    larkbird.get_sing(10);
    /*
    let color_a = Color::new(1, 2, 3);
    let color_b = Color::new(4, 5, 6);
    let color_c = color_a + color_b;
    println!("now color_c is {:?}", color_c);
    */
    /*
    let a = 1u32;
    let b = 2u64;
    println!("{}", a.add(b));
    assert_eq!(3u64, a.add(b));
    */
    /*
    let (a, b, c, d) = (1i32, 2i32, 3u32, 4u32);
    let x = a.my_add(b);
    let y = c.my_add(d);
    println!("x is {}", x);
    println!("y is {}", y);

    let a = "Hello";
    let b = " hjiang";
    let c = a.to_string() + b;
    println!("{:?}", c);
    */
}
