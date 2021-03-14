use mysql::*;
use mysql::prelude::*;

#[derive(Debug)]
struct AccountItem {
    item_id: i32,
    item_content: Option<String>,
    item_cost: f64,
    item_datetime: Option<String>,
}

fn main()  {
    let mysql_url = "mysql://hjiang:jiang186212@localhost:3306/account_book";
    let _pool = Pool::new(mysql_url).unwrap();
    //Ok(())
}
