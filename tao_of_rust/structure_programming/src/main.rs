/*
#[derive(Debug, Copy, Clone)]
struct Book<'a> {
    name: &'a str,
    isbn: i32,
    version: i32,
}

#[derive(Debug)]
struct MoveBook {
    name: String,
    isbn: i32,
    version: i32,
}
 */

use std::fmt;

struct ColoredString {
    input: String,
    fgcolor: String,
    bgcolor: String,
}

trait Colorize {
    //关联常量
    const FG_RED: &'static str = "31";
    const BG_YELLOW: &'static str = "43";
    fn red(self) -> ColoredString;
    fn on_yellow(self) -> ColoredString;
}

impl Default for ColoredString {
    fn default() -> Self {
        ColoredString {
            input: String::default(),
            fgcolor: String::default(),
            bgcolor: String::default(),
        }
    }
}

impl Colorize for ColoredString {
    fn red(self) -> ColoredString {
        ColoredString {
            fgcolor: String::from(ColoredString::FG_RED),
            ..self
        }
    }

    fn on_yellow(self) -> ColoredString {
        ColoredString {
            bgcolor: String::from(ColoredString::BG_YELLOW),
            ..self
        }
    }
}

impl<'a> Colorize for &'a str {
    fn red(self) -> ColoredString {
        ColoredString {
            fgcolor: String::from(ColoredString::FG_RED),
            input: String::from(self),
            ..ColoredString::default()
        }
    }

    fn on_yellow(self) -> ColoredString {
        ColoredString {
            bgcolor: String::from(ColoredString::BG_YELLOW),
            input: String::from(self),
            ..ColoredString::default()
        }
    }
}

impl ColoredString {
    fn compute_style(&self) -> String {
        let mut res = String::from("\x1B[");
        let mut has_wrote = false;

        if !self.bgcolor.is_empty() {
            res.push_str(&self.bgcolor);
            has_wrote = true;
        }

        if !self.fgcolor.is_empty() {
            if has_wrote {
                res.push(';');
            }
            res.push_str(&self.fgcolor);
        }

        res.push('m');
        res
    }
}

impl fmt::Display for ColoredString {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut input = &self.input.clone();
        f.write_str(&self.compute_style());
        f.write_str(input);
        f.write_str("\x1B[0m");
        Ok(())
    }
}

fn main() {
    let hi_red = "Hello".red();
    println!("{}", hi_red);
    let hi_bkyellow = "Hello".on_yellow();
    println!("{}", hi_bkyellow);
    let hi_red_on_yellow = "Hello".red().on_yellow();
    println!("{}", hi_red_on_yellow);
    let hi_yellow_bak_red = "Hello".on_yellow().red();
    println!("{}", hi_yellow_bak_red);
    /*
    let book = Book {
        name: "The tao of rust",
        isbn: 20200220,
        version: 1,
    };
    println!("{:?}", book);
    let book2 = Book { version: 2, ..book };
    println!("{:?}", book);
    println!("{:?}", book2);

    let mvbook = MoveBook {
        name: "The tao de jing".to_string(),
        isbn: 199110,
        version: 0,
    };
    println!("{:?}", mvbook);
    let mvbook2 = MoveBook {
        version: 1,
        ..mvbook
    };
    println!("{:?}", mvbook2);
    //println!("{:?}", mvbook);
    */
}
