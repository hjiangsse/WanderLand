struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

struct Color(i32, i32, i32);

fn main() {
    let mut user1 = User {
        email: String::from("redmagic039@gmail.com.cn"),
        username: String::from("hjiang"),
        active: true,
        sign_in_count: 100,
    };

    user1.email = String::from("hjiang@sse.com.cn");

    tell_user_message(&user1);

    let user2 = build_user(String::from("cjshi@sse.com.cn"), String::from("cjshi"));
    tell_user_message(&user2);

    let user3 = User {
        email: String::from("ytsheng@sse.com.cn"),
        username: String::from("ytsheng"),
        ..user2
    };
    tell_user_message(&user3);

    let red = Color(255, 0, 0);
    tell_color(&red);
}

fn build_user(email: String, username: String) -> User {
    User {
        email,
        username,
        active: true,
        sign_in_count: 1,
    }
}

//tell color
fn tell_color(color: &Color) {
    println!("red: {}", color.0);
    println!("green: {}", color.1);
    println!("blue: {}", color.2);
}

//tell the messages of a user
fn tell_user_message(user: &User) {
    println!("User Name: {}", user.username);
    println!("User Email: {}", user.email);
    println!("User SignCount: {}", user.sign_in_count);
    println!("User IsActive: {}", user.active);
}
