#[allow(dead_code)]
enum Dynasty {
    Han(String),
    Jin(String),
    Tang(String),
    Song(String),
    Yuan(String),
    Ming(String),
    Qing(String),
}

fn get_dynasty_period(dynasty: Dynasty) -> (String, i32, i32) {
    match dynasty {
        Dynasty::Han(creator) => (creator, -202, 220),
        Dynasty::Jin(creator) => (creator, 226, 420),
        Dynasty::Tang(creator) => (creator, 618, 907),
        Dynasty::Song(creator) => (creator, 960, 1279),
        Dynasty::Yuan(creator) => (creator, 1271, 1368),
        Dynasty::Ming(creator) => (creator, 1368, 1644),
        Dynasty::Qing(creator) => (creator, 1636, 1912),
    }
}

fn plus_one(x: Option<u32>) -> Option<u32> {
    match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}

fn main() {
    let something_hansome = Some("handsome");
    let something_number = Some(5);
    let num_plus_one = plus_one(something_number);
    let absent_number: Option<u32> = None;

    println!("{:?}", something_hansome);
    println!("{:?}", something_number);
    println!("{:?}", absent_number);
    println!("{:?}", num_plus_one);
    println!("{:?}", plus_one(absent_number));

    if let Some(7) = num_plus_one {
        println!("six!");
    } else {
        println!("seven!");
    }

    let val: i32 = 10;
    match val {
        1 => println!("This is the one!"),
        2 => println!("This is the second!"),
        3 => println!("This is the third!"),
        _ => println!("You are out of space!"),
    }

    let tang_period = get_dynasty_period(Dynasty::Tang(String::from("Li Yuan")));
    println!("Tang(creator: {}): Start({}) -- End({})",
             tang_period.0, tang_period.1, tang_period.2);
    let yuan_period = get_dynasty_period(Dynasty::Yuan(String::from("Hu bilie")));
    println!("Yuan(creator: {}): Start({}) -- End({})",
             yuan_period.0, yuan_period.1, yuan_period.2);
}
