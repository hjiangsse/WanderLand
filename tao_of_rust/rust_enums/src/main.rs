/*
#[derive(Debug)]
enum IpAddrKind {
    V4,
    V6,
}

struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

#[derive(Debug)]
enum FullIpAddr {
    V4(String),
    V6(String),
}

enum Message {
    Quit,
    Move{x: i32, y:i32},
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        match self {
            Message::Quit => { println!("Quick Quit...");},
            Message::Move{x, y} => {
                println!("Move to [x: {}, y: {}]", x, y);
            },
            Message::Write(s) => {
                println!("I will write: {}", s);
            },
            Message::ChangeColor(r,g,b) => {
                println!("change to red: {}", r);
                println!("change to blue: {}", b);
                println!("change to green: {}", g);
            },
        }
    }
}
*/

#[derive(Debug)]
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: &Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}

fn main() {
    let penny = Coin::Penny;
    let nickel = Coin::Nickel;
    let dime = Coin::Dime;
    let quarter = Coin::Quarter;
    println!("{:?} in cents: {}", penny, value_in_cents(&penny));
    println!("{:?} in cents: {}", nickel, value_in_cents(&nickel));
    println!("{:?} in cents: {}", dime, value_in_cents(&dime));
    println!("{:?} in cents: {}", quarter, value_in_cents(&quarter));
    /*
    let v4 = IpAddrKind::V4;
    let v6 = IpAddrKind::V6;
    println!("{:?}", v4);
    println!("{:?}", v6);
   
    let home = IpAddr{
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1"),
    };

    let work = IpAddr{
        kind: IpAddrKind::V6,
        address: String::from("::1"),
    };
     
    let homeAddr = FullIpAddr::V4(String::from("127.0.0.1"));
    let workAddr = FullIpAddr::V6(String::from("::1"));
    println!("homeAddr: {:?}", homeAddr);
    println!("homeAddr: {:?}", workAddr);
     
    let message1 = Message::ChangeColor(255,0,0);
    message1.call();
    
    let some_number= Some(5);
    let absent_number: Option<i32> = None;
    */
}
