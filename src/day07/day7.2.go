package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

type Hand struct {
	Bid         int
	Combination string
}

var orderMap = map[rune]int{
	'A': 1, 'K': 2, 'Q': 3, 'J': 15, 'T': 5,
	'9': 6, '8': 7, '7': 8, '6': 9, '5': 10,
	'4': 11, '3': 12, '2': 13,
}

func compareStrings(s1, s2 string) bool {
	for idx := 0; idx < len(s1); idx++ {
		order1 := orderMap[rune(s1[idx])]
		order2 := orderMap[rune(s2[idx])]

		if order1 != order2 {
			return order1 < order2
		}
	}
	return false
}

func sortHandsList(handList []string) {
	sort.Slice(handList, func(i, j int) bool {
		return compareStrings(handList[i], handList[j])
	})
}

func defineCombination(hand string) string {
	unique := make(map[rune]int)
	cuts := make([]int, 0)

	for _, card := range hand {
		unique[card]++
	}

	for _, count := range unique {
		cuts = append(cuts, count)
	}

	sort.Ints(cuts)

	if len(unique) == 1 {
		return "Five Cards"
	}

	if cuts[0] == 1 && cuts[1] == 4 {
		if strings.ContainsRune(hand, 'J') {
			return "Five Cards"
		} else {
			return "Four of a Kind"
		}
	}

	if cuts[0] == 2 && cuts[1] == 3 {
		if strings.ContainsRune(hand, 'J') {
			return "Five Cards"
		} else {
			return "Full House"
		}
	}

	if cuts[0] == 1 && cuts[1] == 1 && cuts[2] == 3 {
		if strings.ContainsRune(hand, 'J') {
			return "Four of a Kind"
		} else {
			return "Three of a Kind"
		}
	}

	if cuts[0] == 1 && cuts[1] == 2 && cuts[2] == 2 {
		if strings.ContainsRune(hand, 'J') && strings.Count(hand, "J") == 2 {
			return "Four of a Kind"
		} else if strings.ContainsRune(hand, 'J') && strings.Count(hand, "J") == 1 {
			return "Full House"
		} else {
			return "Two Pair"
		}
	}

	if cuts[0] == 1 && cuts[1] == 1 && cuts[2] == 1 && cuts[3] == 2 {
		if strings.ContainsRune(hand, 'J') {
			return "Three of a Kind"
		} else {
			return "One Pair"
		}
	}

	if len(unique) == 5 {
		if strings.ContainsRune(hand, 'J') {
			return "One Pair"
		} else {
			return "High Card"
		}
	}

	return " "
}

func reverseStringSlice(s []string) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}

func main() {
	handsMap := make(map[string]Hand)
	combinationMap := make(map[string][]string)

	file, err := os.Open("day07.txt")
	if err != nil {
		fmt.Println("Open Error:", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		if len(parts) == 2 {
			hand := parts[0]
			bid := parts[1]

			bidInt := 0
			fmt.Sscanf(bid, "%d", &bidInt)

			myHand := Hand{
				Bid:         bidInt,
				Combination: defineCombination(hand),
			}

			combinationMap[myHand.Combination] = append(combinationMap[myHand.Combination], hand)

			handsMap[hand] = myHand

		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Scan Error:", err)
		return
	}

	for _, hands := range combinationMap {
		sortHandsList(hands)
	}

	var allHands []string
	for _, combination := range []string{"Five Cards", "Four of a Kind", "Full House", "Three of a Kind", "Two Pair", "One Pair", "High Card"} {
		if hands, ok := combinationMap[combination]; ok {
			allHands = append(allHands, hands...)
		}
	}

	reverseStringSlice(allHands)

	totalResult := 0
	for index, hand := range allHands {
		totalResult += handsMap[hand].Bid * (index + 1)
	}

	fmt.Println(totalResult)

}
