use std::fs::File;
use std::io::{self, BufRead};

fn main() {
    let file_path = "day11.txt";

    let file = match File::open(&file_path) {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Open Error: {}", e);
            return;
        }
    };

    let mut galaxy: Vec<Vec<char>> = Vec::new();

    for line in io::BufReader::new(file).lines() {
        let row: Vec<char> = line.unwrap().chars().collect();
        galaxy.push(row);
    }

    for col_index in (0..galaxy[0].len()).rev() {
        if (0..galaxy.len()).all(|row_index| galaxy[row_index][col_index] == '.') {
            for row in &mut galaxy {
                row.insert(col_index, '.');
            }
        }
    }

    for row_index in (0..galaxy.len()).rev() {
        if galaxy[row_index].iter().all(|c| *c == '.') {
            galaxy.insert(row_index, vec!['.'; galaxy[0].len()]);
        }
    }

    let mut coordinates = Vec::new();

    for (row_index, row) in galaxy.iter().enumerate() {
        for (col_index, c) in row.iter().enumerate() {
            if *c == '#' {
                coordinates.push((col_index, row_index));
            }
        }
    }

    let mut sum = 0;
    for i in 0..coordinates.len() {
        let galaxy1 = coordinates[i];
        for galaxy2 in coordinates.iter().skip(i + 1) {
            let horizontal = (galaxy1.0 as isize - galaxy2.0 as isize).abs();
            let vertical = (galaxy1.1 as isize - galaxy2.1 as isize).abs();
            sum += horizontal + vertical;
        }
    }

    println!("{}", sum);
}
