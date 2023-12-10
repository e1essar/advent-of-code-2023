using System;

namespace Day06 {
    class Program {
        static void Main() {
            var input = File.ReadAllText("day06.txt");
            var strings = input.Trim().Split("\n").Select(s => s.TrimEnd()).ToArray();
            var time = long.Parse(strings[0].Split(':')[1].Replace(" ", ""));
            var distance = long.Parse(strings[1].Split(':')[1].Replace(" ", ""));
            long result = 0;

            for (long holdTime = 1; holdTime < time; holdTime++)
                if ((time - holdTime) * holdTime > distance)
                    result++;

            Console.WriteLine(result);
        }
    }
}
