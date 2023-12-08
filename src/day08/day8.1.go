package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("C:\\Users\\Igor\\Desktop\\text.txt")
	if err != nil {
		fmt.Println("Open Error:", err)
		return
	}
	defer file.Close()

	rules := ""
	dataMap := make(map[string]string)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, "=")
		if len(parts) != 2 {
			rules += line
			continue
		}

		key := strings.Trim(parts[0], " \t\n\r\x0B'\"(),")
		value := strings.Trim(parts[1], " \t\n\r\x0B'\"(),")
		dataMap[key] = value
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Read Error:", err)
		return
	}

	count := 0
	current := "AAA"

	if road, ok := dataMap[current]; ok {
		for current != "ZZZ" {
			for i := 0; i < len(rules); i++ {
				parts := strings.Split(road, ", ")
				if rules[i] == 'L' {
					if len(parts) > 0 {
						current = parts[0]
					}
				} else {
					if len(parts) > 1 {
						current = parts[1]
					}
				}
				count++
				road = dataMap[current]
			}
		}
	}

	fmt.Println(count)
}
