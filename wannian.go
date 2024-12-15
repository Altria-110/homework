package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

// 判断是否为闰年
func isLeapYear(y int) bool {
	return (y%4 == 0 && y%100 != 0) || (y%400 == 0)
}

// 计算从元年到给定日期的天数
func daysFromEpoch(y, m, d int) int {
	day := 0

	for i := 1; i < y; i++ {
		if isLeapYear(i) {
			day += 366
		} else {
			day += 365
		}
	}

	mday := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if isLeapYear(y) {
		mday[1] = 29
	}

	for i := 0; i < m-1; i++ {
		day += mday[i]
	}
	day += d

	return day
}

// 获取给定年和月的天数
func daysInMonth(y, m int) int {
	mday := []int{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if isLeapYear(y) {
		mday[1] = 29
	}
	return mday[m-1]
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("请输入年份: ")
	yStr, _ := reader.ReadString('\n')
	y, _ := strconv.Atoi(yStr[:len(yStr)-1]) // 去掉换行符

	for m := 1; m < 13; m++ {
		day := daysFromEpoch(y, m, 1)
		weekday := day % 7
		week := []string{"sun", "mon", "tue", "wed", "thu", "fri", "sat"}

		fmt.Printf("             %d\n", m)
		fmt.Printf("%s %s %s %s %s %s %s\n", week[0], week[1], week[2], week[3], week[4], week[5], week[6])

		for x := 0; x < weekday; x++ {
			fmt.Print("    ")
		}

		dayInMonth := daysInMonth(y, m)
		for i := 1; i <= dayInMonth; i++ {
			fmt.Printf("%4d", i)
			if (i+weekday-1)%7 == 6 || i == dayInMonth {
				fmt.Println()
			}
		}
	}
}
