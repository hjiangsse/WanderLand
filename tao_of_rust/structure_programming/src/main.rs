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

use std::convert::From;
use std::fmt;
use std::str::FromStr;
use std::string::String;

/*
struct ColoredString {
    input: String,
    fgcolor: String,
    bgcolor: String,
}*/

struct ColoredString {
    input: String,
    fgcolor: Option<Color>,
    bgcolor: Option<Color>,
}

enum Color {
    Red,
    Yellow,
    Blue,
}

impl Color {
    fn to_fg_str(&self) -> &str {
        match *self {
            Color::Red => "31",
            Color::Yellow => "33",
            Color::Blue => "34",
        }
    }

    fn to_bg_str(&self) -> &str {
        match *self {
            Color::Red => "41",
            Color::Yellow => "43",
            Color::Blue => "44",
        }
    }
}

impl<'a> From<&'a str> for Color {
    fn from(src: &str) -> Self {
        src.parse().unwrap_or(Color::Red)
    }
}

impl From<String> for Color {
    fn from(src: String) -> Self {
        src.parse().unwrap_or(Color::Red)
    }
}

impl FromStr for Color {
    type Err = ();
    fn from_str(src: &str) -> Result<Self, Self::Err> {
        let src = src.to_lowercase();
        match src.as_ref() {
            "red" => Ok(Color::Red),
            "yellow" => Ok(Color::Yellow),
            "blue" => Ok(Color::Blue),
            _ => Err(()),
        }
    }
}

trait Colorize {
    //关联常量
    const FG_RED: &'static str = "31";
    const BG_YELLOW: &'static str = "43";
    fn red(self) -> ColoredString;
    fn yellow(self) -> ColoredString;
    fn blue(self) -> ColoredString;
    fn color<S: Into<Color>>(self, color: S) -> ColoredString;
    fn on_red(self) -> ColoredString;
    fn on_yellow(self) -> ColoredString;
    fn on_blue(self) -> ColoredString;
    fn on_color<S: Into<Color>>(self, color: S) -> ColoredString;
}

impl Default for ColoredString {
    fn default() -> Self {
        ColoredString {
            input: String::default(),
            //fgcolor: String::default(),
            //bgcolor: String::default(),
            fgcolor: None,
            bgcolor: None,
        }
    }
}

impl Colorize for ColoredString {
    fn red(self) -> ColoredString {
        self.color(Color::Red)
    }

    fn yellow(self) -> ColoredString {
        self.color(Color::Yellow)
    }

    fn blue(self) -> ColoredString {
        self.color(Color::Blue)
    }

    fn color<S: Into<Color>>(self, color: S) -> ColoredString {
        ColoredString {
            fgcolor: Some(color.into()),
            ..self
        }
    }

    fn on_red(self) -> ColoredString {
        self.on_color(Color::Red)
    }

    fn on_yellow(self) -> ColoredString {
        self.on_color(Color::Yellow)
    }

    fn on_blue(self) -> ColoredString {
        self.on_color(Color::Blue)
    }

    fn on_color<S: Into<Color>>(self, color: S) -> ColoredString {
        ColoredString {
            bgcolor: Some(color.into()),
            ..self
        }
    }
}

impl<'a> Colorize for &'a str {
    /*
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
    */

    fn red(self) -> ColoredString {
        self.color(Color::Red)
    }

    fn yellow(self) -> ColoredString {
        self.color(Color::Yellow)
    }

    fn blue(self) -> ColoredString {
        self.color(Color::Blue)
    }

    fn color<S: Into<Color>>(self, color: S) -> ColoredString {
        ColoredString {
            fgcolor: Some(color.into()),
            input: String::from(self),
            ..ColoredString::default()
        }
    }

    fn on_red(self) -> ColoredString {
        self.on_color(Color::Red)
    }

    fn on_yellow(self) -> ColoredString {
        self.on_color(Color::Yellow)
    }

    fn on_blue(self) -> ColoredString {
        self.on_color(Color::Blue)
    }

    fn on_color<S: Into<Color>>(self, color: S) -> ColoredString {
        ColoredString {
            bgcolor: Some(color.into()),
            input: String::from(self),
            ..ColoredString::default()
        }
    }
}

impl ColoredString {
    fn compute_style(&self) -> String {
        let mut res = String::from("\x1B[");
        let mut has_wrote = false;

        /*
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
         */
        if let Some(ref bgcolor) = self.bgcolor {
            if has_wrote {
                res.push(';');
            }
            res.push_str(bgcolor.to_bg_str());
            has_wrote = true;
        }

        if let Some(ref fgcolor) = self.fgcolor {
            if has_wrote {
                res.push(';');
            }
            res.push_str(fgcolor.to_fg_str());
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
    let hi1 = "Hello".red();
    println!("{}", hi1);
    let hi2 = "Hello".red().on_blue();
    println!("{}", hi2);
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
