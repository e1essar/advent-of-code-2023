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

    let expansion = 1000000 - 1;

    let mut coordinates = Vec::new();

    for (row_index, row) in galaxy.iter().enumerate() {
        for (col_index, c) in row.iter().enumerate() {
            if *c == '#' {
                coordinates.push((col_index, row_index));
            }
        }
    }

    for x in (0..galaxy[0].len()).rev() {
        let extend_count = (0..x)
            .filter(|x| galaxy.iter().all(|row| row[*x] == '.'))
            .count();

        coordinates
            .iter_mut()
            .filter(|(x_, _)| *x_ == x)
            .for_each(|(x, _)| *x += expansion * extend_count);
    }

    for y in (0..galaxy.len()).rev() {
        let extend_count = (0..y)
            .filter(|y| galaxy[*y].iter().all(|c| *c == '.'))
            .count();

        coordinates
            .iter_mut()
            .filter(|(_, y_)| *y_ == y)
            .for_each(|(_, y)| *y += expansion * extend_count);
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