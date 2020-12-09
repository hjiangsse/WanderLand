//use std::rc::Rc;

/*
#[derive(Debug, Copy, Clone)]
struct StudentWithCopy<'a> {
    Name: &'a str,
    InsCod: u32,
}

impl<'a> StudentWithCopy<'a> {
    fn new(name: &'a str, inscod: u32) -> StudentWithCopy<'a> {
        StudentWithCopy {
            Name: name,
            InsCod: inscod,
        }
    }
}


#[derive(Debug)]
struct StudentWithOutCopy<'a> {
    Name: &'a str,
    InsCod: u32,
}

impl<'a> StudentWithOutCopy<'a> {
    fn new(name: &'a str, inscod: u32) -> StudentWithOutCopy<'a> {
        StudentWithOutCopy {
            Name: name,
            InsCod: inscod,
        }
    }
}

#[derive(Debug)]
struct Foo<'a> {
    x: u32,
    y: Cell<StudentWithCopy<'a>>,
}
*/

//use std::cell::Cell;
//use std::cell::RefCell;
use std::borrow::Cow;

fn abs_all(input: &mut Cow<[i32]>) {
    for i in 0..input.len() {
        let v = input[i];
        if v < 0 {
            input.to_mut()[i] = -v;
        }
    }
}

fn abs_sum(ns: &[i32]) -> i32 {
    let mut lst = Cow::from(ns);
    abs_all(&mut lst);
    lst.iter().fold(0, |acc, &n| acc + n)
}

fn main() {
    let s1 = [1, 2, 3];
    let mut i1 = Cow::from(&s1[..]);
    abs_all(&mut i1);
    println!("IN: {:?}", s1);
    println!("OUT: {:?}", i1);

    let s2 = [1, 2, 3, -45, 5];
    let mut i2 = Cow::from(&s2[..]);
    abs_all(&mut i2);
    println!("IN: {:?}", s2);
    println!("OUT: {:?}", i2);

    let mut v1 = Cow::from(vec![1, 2, -3, 4]);
    abs_all(&mut v1);
    println!("IN/OUT: {:?}", v1);

    /*
    let x = Box::new("hello, smart pointer");
    let y = x;
    println!("{:?}", x);

    let w = Box::new(10);
    let v = *w;
    println!("{:?}", v);
    println!("{:?}", w);

    let q = Box::new("hjiang".to_string());
    let p = *q;
    println!("{:?}", p);
    println!("{:?}", q);
     */

    /*
    let x = Box::new(StudentWithCopy::new("hjiang", 1));
    println!("{:?}", x);
    let y = *x;
    println!("{:?}", y);
    println!("{:?}", x);

    let w = Box::new(StudentWithOutCopy::new("zhangxiang", 2));
    println!("{:?}", w);
    let v = *w;
    println!("{:?}", v);
    println!("{:?}", w);
     */

    /*
    let x = Rc::new(StudentWithCopy::new("hjiang", 1));
    println!("{:?}", x);
    let y = x;
    println!("{:?}", y);
     */

    /*
    let x = Rc::new(45);
    let y1 = x.clone();
    let y2 = x.clone();
    println!("{:?}", Rc::strong_count(&x));
    let w = Rc::downgrade(&x);
    println!("{:?}", Rc::weak_count(&x));
    println!("{}", 100 - *x);
    println! {"{:?}", w};
     */

    /*
    let foo = Foo {
        x: 1,
        y: Cell::new(StudentWithOutCopy::new("hjiang", 1)),
    };
    println!("{}", foo.x);
    println!("{}", foo.y.get());
    */
    //foo.y.set(100);
    //println!("{}", foo.y.get());

    /*
    let bar = Foo {
        x: 2,
        y: Cell::new(StudentWithCopy::new("zhangjiang", 2)),
    };
    println!("{}", bar.x);
    println!("{:?}", bar.y.get());
    bar.y.set(StudentWithCopy::new("liming", 3));
    println!("{:?}", bar);
     */

    /*
    let x = RefCell::new(vec![1, 2, 3, 4]);
    println!("{:?}", x);
    println!("{:?}", x.borrow());

    x.borrow_mut().push(5);
    println!("{:?}", x);
    println!("{:?}", x.borrow());

    x.borrow_mut().push(10);
    println!("{:?}", x);
    println!("{:?}", x.borrow());
    */
}
