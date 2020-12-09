/*
pub fn temp() -> i32 {
    return 1;
}

fn jazzbizz(val: i32) -> String {
    if val % 15 == 0 {
        "jazzbizz".to_string()
    } else if val % 3 == 0 {
        "jazz".to_string()
    } else if val % 5 == 0 {
        "bizz".to_string()
    } else {
        val.to_string()
    }
}

fn sum(a: i32, b: i32) -> i32 {
    a + b
}

fn product(a: i32, b: i32) -> i32 {
    a * b
}

fn math(op: fn(i32, i32) -> i32, x: i32, y: i32) -> i32 {
    op(x, y)
}

const fn init_len() -> usize {
    5
}

fn two_times_impl() -> impl Fn(i32) -> i32 {
    let i = 2;
    move |j| j * i
}
 */

fn main() {
    //println!("Hello, world!");
    //let x = &temp();
    /*
    assert_eq!(jazzbizz(15), "jazzbizz".to_string());
    assert_eq!(jazzbizz(3), "jazz".to_string());
    assert_eq!(jazzbizz(5), "bizz".to_string());
    assert_eq!(jazzbizz(13), 13.to_string());

    assert_eq!(math(sum, 1, 2), 3);
    assert_eq!(math(product, 1, 2), 2);

    let arr = vec![1, init_len()];
    println!("{:?}", arr);

    let out = 42;
    fn add(x: i32, y: i32) -> i32 {
        x + y
    }

    let closure_annotated = |x: i32, y: i32| x + y + out;
    let closure_infered = |x, y| x + y + out;
    let i = 1;
    let j = 2;
    println!("{}", add(i, j));
    println!("{}", closure_annotated(i, j));
    println!("{}", closure_infered(i, j));

    let result = two_times_impl();
    println!("{}", result(10));

    let n = 13;
    let big_n = if n < 10 && n > -10 { 10 * n } else { n / 2 };
    println!("big_n is {}", big_n);

    for n in 1..101 {
        if n % 15 == 0 {
            println!("fuzzbizz");
        } else if n % 3 == 0 {
            println!("fuzz");
        } else if n % 5 == 0 {
            println!("jazz");
        } else {
            println!("{}", n);
        }
    }

    let y = while_true(5);
    assert_eq!(y, 6);
     */

    /*
    let mut x = 1;
    loop {
        if x > 10 {
            break;
        }
        x = x + 1;
        println!("now the x is {}", x);
    }
     */

    /*
    let i = get_user_input_number();
    match i {
        0 => println!("The tao is emerging from NULL"),
        1..=3 => println!("heavn, earth, human"),
        5 | 7 | 13 => println!("Wash away your bad luck!"),
        _ => println!("Stop the world"),
    }

    if let 100 = i {
        println!("You are really a lucky baby!");
    }
     */

    /*
    let mut v = vec![1, 2, 3, 4];
    loop {
        match v.pop() {
            Some(x) => println!("The top of the vector is {}", x),
            None => {
                println!("The road is finished!");
                break;
            }
        }
    }

    println!("Use while let:");
    let mut w = vec![1, 2, 3, 4];
    while let Some(x) = w.pop() {
        println!("{}", x);
    }

    println!("true as {}", true as u32);
    println!("false as {}", false as u32);

    println!("{}", std::f32::MAX);
    println!("{}", std::f32::MIN);

    println!("{}", std::f64::MAX);
    println!("{}", std::f64::MIN);

    println!("{}", std::u32::MAX);
    println!("{}", '%' as u32);

    println!("{:?}", std::ops::Range { start: 1, end: 5 });

    for i in (1..=101) {
        println!("{}", i);
    }

    println!("Test slice:");
    let arr: [i32; 5] = [1, 2, 3, 4, 5];
     */

    /*
    let word: &'static str = "一首不朽的诗歌";
    println!("Tell the truth: {}", word);

    let ptr = word.as_ptr();
    let len = word.len();jius
    println!("The length of the word: {}", len);
    let s = unsafe {
        let slice = std::slice::from_raw_parts(ptr, len);
        std::str::from_utf8(slice)
    };
    println!("{}", s.unwrap());
     */

    /*
    test_raw_pointer();

    let x = (1, 2);
    println!("{:?}", x);
     */
    /*
    let x = Empty;
    println!("{:p}", &x);
    let y = x;
    println!("{:p}", &y);
    let z = Empty;
    println!("{:p}", &z);
    */
}

//struct Empty;
/*
fn while_true(x: i32) -> i32 {
    while true {
        return x + 1;
    }
    x
}
 */

/*
fn get_user_input_number() -> i32 {
    let mut buffer = String::new();
    std::io::stdin().read_line(&mut buffer).expect("Failed");
    buffer.trim().parse::<i32>().unwrap()
}
*/

/*
fn test_raw_pointer() {
    let mut x = 10;
    let ptr_x = &mut x as *mut i32;
    let y = Box::new(20);
    let ptr_y = &*y as *const i32;
    unsafe {
        *ptr_x += *ptr_y;
    }
    println!("After the raw pointer usage: {}", x);
}
*/
