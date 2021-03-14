mod lib;

fn main() {
    let mut st = lib::Student {
        name: String::from("this is a student!"),
        number: 10,
    };
    println!("{:?}", st);
    st.name = String::from("that is a student!");
    println!("{:?}", st);
}
