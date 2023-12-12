use std::fs::File;
use std::io::{self, BufRead};

fn main() {
    let file_path = "day12.txt";

    let file = File::open(&file_path).unwrap();
    let mut ans = 0;

    for line in io::BufReader::new(file).lines() {
        if let Ok(row) = line {
            let mut parts = row.split_whitespace();

            if let Some(template_part) = parts.next() {
                let template: Vec<char> = format!("{}.", template_part.to_string()).chars().collect();
                let amount_part = parts.next().unwrap_or("");
                let mut amount: Vec<i32> = amount_part.split(',').map(|s| s.parse().unwrap()).collect();

                let n = template.len();
                let m = amount.len();
                amount.insert(0, 0);
                let mut dp = vec![vec![0; m + 1]; n + 1];
                dp[0][0] = 1;

                for i in 1..=n {
                    for j in 0..=m {
                        if template[i-1] != '#' {
                            dp[i][j] += dp[i - 1][j];
                        }

                        if j > 0 && template[i - 1] != '.' {
                            if i + amount[j] as usize > n
                                || template
                                    .iter()
                                    .skip(i - 1)
                                    .take(amount[j] as usize)
                                    .any(|&c| c == '.')
                                || template[i - 1 + amount[j] as usize] == '#'
                                { continue; } 
                            
                            dp[i + amount[j] as usize][j] += dp[i - 1][j - 1];
                        }
                    }
                    
                }
                ans += dp[n][m];
            }
        }
    }
    println!("{}", ans);
}
