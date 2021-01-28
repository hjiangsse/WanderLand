use calamine::{open_workbook, Error, RangeDeserializerBuilder, Reader, Xlsx};

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

fn main() {
    example();
}
