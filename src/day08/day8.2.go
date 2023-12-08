package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func lcm(a, b int) int {
	return a * b / gcd(a, b)
}

func findLCM(numbers []int) int {
	result := numbers[0]
	for i := 1; i < len(numbers); i++ {
		result = lcm(result, numbers[i])
	}
	return result
}

func processWithCondition(current string, dataMap map[string]string, rules string) int {
	count := 0
	if road, ok := dataMap[current]; ok {
		for !strings.HasSuffix(current, "Z") {
			for i := 0; i < len(rules); i++ {
				parts := strings.Split(road, ", ")
				if rules[i] == 'L' && len(parts) > 0 {
					current = parts[0]
				} else if len(parts) > 1 {
					current = parts[1]
				}
				count++
				road = dataMap[current]
			}
		}
	}
	return count
}

func main() {
	file, err := os.Open("day08.txt")
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

	list := []string{}
	for key := range dataMap {
		if strings.Contains(key, "A") {
			list = append(list, key)
		}
	}

	sort.Strings(list)
	counts := make([]int, 6)
	for i := 0; i < len(counts); i++ {
		counts[i] = processWithCondition(list[i], dataMap, rules)
	}

	result := findLCM(counts)
	fmt.Println(result)

}
