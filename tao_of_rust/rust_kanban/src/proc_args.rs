use structopt::StructOpt;

#[derive(Debug, StructOpt)]
pub struct Opt {
    #[structopt(
        short = "c",
        long = "config",
        default_value = "~/.fastfile.toml",
        help = "the config file path"
    )]
    config: String,

    #[structopt(
        short = "n",
        long = "filename",
        default_value = "cpp",
        help = "the default file name you want to send of download"
    )]
    filename: String,
}
