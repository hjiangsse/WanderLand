use std::collections::HashMap;

fn main() {
    /*
    let mut scores = HashMap::new();

    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);

    //use collect to build HashMap
    let team_names = vec![String::from("Blue"), String::from("Yellow")];
    let team_scores = vec![10, 50];

    let mut names_to_scores: HashMap<_, _> = team_names
        .into_iter()
        .zip(team_scores.into_iter())
        .collect();
    */

    let mut hash_owner = HashMap::new();
    let field_name = String::from("hjiang");
    let field_age = String::from("30");
    hash_owner.insert(field_name, field_age);
    /*
    println!("now the field name: {}", field_name);
    println!("now the field age: {}", field_age);
     */

    let name = String::from("hjiang");
    let age = hash_owner.get(&name);
    if let Some(t) = age {
        println!("the name {}, age {}", name, t);
    }

    for (key, value) in &hash_owner {
        println!("key {}: value {}", key, value);
    }

    //change the the old value to a new value of the same key
    hash_owner.insert(String::from("hjiang"), String::from("29"));
    for (key, value) in &hash_owner {
        println!("key {}: value {}", key, value);
    }

    //not change the value if already exists
    let mut scores = HashMap::new();
    scores.insert(String::from("Tom"), 100);

    scores.entry(String::from("Jim")).or_insert(98);
    scores.entry(String::from("Tom")).or_insert(98);

    for (key, value) in &scores {
        println!("key {}: value {}", key, value);
    }
}
