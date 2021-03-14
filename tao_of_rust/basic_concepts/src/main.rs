Const MAX_LEN: u32 = 1000_000;

fn get_type<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn just_another_function() {
    println!("just another function!");
}

fn main() {
    just_another_function();
    /*
    //mut and const, then shadowing
    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;
    println!("Now, the value of x is: {}", x);

    println!("The const is {}", MAX_LEN);


    let wish_word :&'static str = "I wish my country will become stronger!";
    println!("the wish word is: {}", wish_word);

    //rust data types
    let mut y :u8 = 10;
    //y = y + 1000;

    let x = 2.0;
    get_type(&x);

    let c = 'c';
    get_type(&c);

    //rust compound values
    let tuple = (100, 2.0, "this is end");
    get_type(&tuple);

    let arr = [1,2,3,4];
    get_type(&arr);
    */
}
