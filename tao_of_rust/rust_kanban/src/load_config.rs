use serde_derive::Deserialize;
use std::fs;

#[derive(Deserialize, Debug)]
pub struct Config {
    state_column_index: i32,  //状态列索引
    state_queue: Vec<String>, //状态次序序列
}

pub fn load_config(path: &str) -> Config {
    let contents = fs::read_to_string(path).unwrap();
    let config_structure: Config = toml::from_str(&contents).unwrap();
    config_structure
}

impl Config {
    pub fn get_column_index(&self) -> i32 {
        self.state_column_index
    }

    pub fn get_state_queue(&self) -> Vec<String> {
        self.state_queue.clone()
    }
}
