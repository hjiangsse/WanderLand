/*
#[derive(Debug)]
struct Foo;

trait Bar {
    fn baz(&self);
}

impl Bar for Foo {
    fn baz(&self) {
        println!("{:?}", self);
    }
}

fn static_dispatch<T>(t: &T)
where
    T: Bar,
{
    t.baz();
}

//trait object
fn dynamic_dispatch(t: &dyn Bar) {
    println!("{:?}", std::mem::size_of::<&dyn Bar>());
    t.baz();
}
*/

use std::fmt::Debug;
pub trait Fly {
    fn fly(&self) -> bool;
}

#[derive(Debug)]
struct Duck;
#[derive(Debug)]
struct Pig;

impl Fly for Duck {
    fn fly(&self) -> bool {
        true
    }
}

impl Fly for Pig {
    fn fly(&self) -> bool {
        false
    }
}

fn fly_static(s: impl Fly + Debug) -> bool {
    s.fly()
}

fn can_fly(s: impl Fly + Debug) -> impl Fly {
    if s.fly() {
        println!("{:?} can fly", s);
    } else {
        println!("{:?} can not fly", s);
    }
    s
}

fn main() {
    let pig = Pig;
    println!("can a pig fly? -- {}", fly_static(pig));
    let duck = Duck;
    println!("can a duck fly? -- {}", fly_static(duck));

    let pig = Pig;
    let pig = can_fly(pig);
    let duck = Duck;
    let duck = can_fly(duck);
    /*
    let foo = Foo;
    static_dispatch(&foo);
    dynamic_dispatch(&foo);
    */
}
