/*
enum Void {}

struct Foo;

struct Baz {
    foo: Foo,
    qux: (),
    baz: [u8; 0],
}
 */

/*
fn foo() -> ! {
    loop {
        println!("This is just a string");
    }
}
*/

//enum Void {}

//generic function
fn little_copy<T>(x: T) -> T {
    x
}

//generic struct
struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T> {
    fn new(x: T, y: T) -> Self {
        Point { x: x, y: y }
    }
}

fn main() {
    println!("{}", little_copy(10));

    let pt = Point::new(10, 20);

    /*
    let x = "101";
    println!("{}", x.parse::<u32>().unwrap());

    let i = 10;
    println!("is i positive: {}", i.is_positive());
    */
    /*
    let res: Result<u32, Void> = Ok(10);
    if let Ok(num) = res {
        println!("The num is {}", num);
    }

    let i = if false { foo() } else { 100 };
    println!("The value of i is {}", i);

    let v = vec![(); 10];
    for i in v {
        println!("{:?}", i);
    }

    println!("{}", std::mem::size_of::<()>());
    println!("{}", std::mem::size_of::<Foo>());
    println!("{}", std::mem::size_of::<Baz>());
    println!("{}", std::mem::size_of::<Void>());
    println!("{}", std::mem::size_of::<[(); 10]>());

    let x = [(), (), ()];
    println!("{}", std::mem::size_of::<[(); 3]>());
    println!("size of variable x = {}", std::mem::size_of_val(&x));

    let y = [1, 2, 3];
    println!("size of variable x = {}", std::mem::size_of_val(&y));

    let str = "hello, small rust";
    let ptr = str.as_ptr();
    let len = str.len();
    println!("{:p}", ptr);
    println!("{}", len);

    let mut arr = [1, 2, 3, 4, 5];
    println!("The original array: {:?}", arr);
    reset_arr(arr);
    println!("The final array: {:?}", arr);
     */

    //reset_arr_by_ref(&arr);
    //println!("The finally array: {:?}", arr);
    /*
    {
        let mut_arr: &mut [u32] = &mut arr;
        reset_arr_by_ref(mut_arr);
    }
     */

    /*
    reset(&mut arr);
    println!("The finally array: {:?}", arr);

    println!("size 1: {}", std::mem::size_of::<&[u32; 5]>());
    println!("size 1: {}", std::mem::size_of::<&[u32]>());
    */
}

/*
fn reset_arr(mut arr: [u32; 5]) {
    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 3;
    arr[3] = 2;
    arr[4] = 1;
    println!("After reset: {:?}", arr);
}

fn reset_arr_by_ref(arr: &mut [u32]) {
    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 3;
    arr[3] = 2;
    arr[4] = 1;
    println!("After reset: {:?}", arr);
}

fn reset(arr: &mut [u32; 5]) {
    arr[0] = 5;
    arr[1] = 4;
    arr[2] = 3;
    arr[3] = 2;
    arr[4] = 1;
    println!("After reset: {:?}", arr);
}
*/
