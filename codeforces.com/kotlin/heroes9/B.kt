fun main() {
    repeat(readInt()) {
        val s = readln().toCharArray()
        val firstMinus = s.indexOfFirst { it == '-' }
        val lastPlus = s.indexOfLast { it == '+' }
        val ans = if (firstMinus != -1 && lastPlus != -1 && firstMinus < lastPlus) {
            s[firstMinus] = '+'
            s[lastPlus] = '-'
            "${firstMinus+1} ${lastPlus+1}"
        } else {
            "1 1"
        }
        println(if (s.runningFold(0) { acc, c -> acc + (if (c == '+') 1 else -1) }.min() < 0) {
            -1
        } else {
            ans
        })
    }
}

private fun readInt() = readln().toInt()