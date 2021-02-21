mod load_config;
mod proc_args;

use calamine::{open_workbook, Error, RangeDeserializer, RangeDeserializerBuilder, Reader, Xlsx};
XS
fn example() -> Result<(), Error> {
    let path = format!("test.xlsx");
    let mut workbook: Xlsx<_> = open_workbook(path)?;
    let range = workbook
        .worksheet_range("Sheet1")
        .ok_or(Error::Msg("Cannot find 'Sheet1'"))??;

    let mut iter = RangeDeserializerBuilder::new().from_range(&range)?;

    if let Some(result) = iter.next() {
        let (label, value1, value2): (String, f64, f64) = result?;
        println!("{:?}", label);
        println!("{:?}", value1);
        println!("{:?}", value2);
        if label.eq("导航") {
            println!("This is a test!");
        }
    }

    if let Some(result1) = iter.next() {
        let (label, value1, value2): (String, f64, f64) = result1?;
        println!("{:?}", label);
        println!("{:?}", value1);
        println!("{:?}", value2);
        Ok(())
    } else {
        Err(From::from("expected at least one record but got none"))
    }
}

fn get_workbook_range_iter(xlsx_file: &str) /* RangeDeserializer*/
{
    let path = format!("test.xlsx");
    let mut workbook: Xlsx<_> = open_workbook(path).unwrap();
    let range = workbook.worksheet_range("Sheet1").unwrap().unwrap();
}

fn main() {
    //let opt = Opt::from_args();
    //example();
    let conf = load_config::load_config("./conf/rust_kanban.toml");
    println!("{:?}", conf);

    let opt = proc_args::Opt::from_args();
    println!("{:?}", opt);
}
