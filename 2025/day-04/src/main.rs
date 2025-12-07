use std::{env, fs};

fn main() {
    let args: Vec<String> = env::args().collect();
    let file_path = &args[1];
    let contents = fs::read_to_string(file_path).expect("Should have been able to read the file");
    let total_length = contents.len();

    let row_length = contents.split('\n').next().map_or_else(|| 0, |e| e.len());
    if row_length == 0 {
        return;
    }
    println!("Row length: {row_length}");
    let mut total = 0;
    let mut as_chars = contents.chars();
    for i in 0..total_length {
        let col = i % row_length;
        let row = i / row_length;

        let c = as_chars.next().unwrap();
        if c == '@' && is_reachable(&contents, row_length, row as i32, col as i32) {
            total += 1;
        }
    }

    println!("Result part1: {total}");
}

fn is_reachable(contents: &String, row_size: usize, row: i32, column: i32) -> bool {
    let top_left = (row - 1, column - 1);
    let top_mid = (row, column - 1);
    let top_right = (row + 1, column - 1);
    let mid_left = (row - 1, column);
    let mid_right = (row + 1, column);
    let bot_left = (row - 1, column + 1);
    let bot_mid = (row - 1, column + 1);
    let bot_right = (row + 1, column + 1);

    let positions = [
        top_left, top_mid, top_right, mid_left, mid_right, bot_left, bot_mid, bot_right,
    ]
    .into_iter();

    positions
        .map(|(e_row, e_col)| is_valid(e_row, e_col, 0, row_size, contents))
        .filter(|&e| e)
        .fold(0, |acc, _| acc + 1)
        >= 4
}

fn is_valid(e_row: i32, e_col: i32, row_count: usize, row_size: usize, contents: &String) -> bool {
    if e_row < 0 || e_row > row_count as i32 {
        return false;
    }

    if e_col < 0 || e_col > row_size as i32 {
        return false;
    }

    let index = (e_col + row_size as i32 * e_row) as usize;
    let c = ({
        let this = contents.chars().nth(index);
        match this {
            Some(t) => (|c| c)(t),
            None => 'a',
        }
    });
    return c == '@';
}
