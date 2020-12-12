mod front_of_house;

mod first_module {
    pub mod first_inner_module {
        pub enum Name {
            FirstName(String),
            SecondName(String),
        }
    }
}

mod second_module {
    pub mod second_inner_module {
        pub enum Name {
            FirstName(String),
            SecondName(String),
        }
    }
}

use first_module::first_inner_module::Name as FName;
use front_of_house::hosting;
use second_module::second_inner_module::Name as SName;

pub fn eat_at_restaurant() {
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();

    let ffname = FName::FirstName(String::from("jiang"));
    let fsname = FName::SecondName(String::from("heng"));
    let sfname = SName::FirstName(String::from("zhang"));
    let ssname = SName::SecondName(String::from("jiang"));
}
