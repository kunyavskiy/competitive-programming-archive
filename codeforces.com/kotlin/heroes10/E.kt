private fun solve(): String {
    val (n, k) = readInts()
    var ans = listOf(n - 1, n)
    repeat(k - 1) {
        val min = ans.min()
        val prevStart = min - ans.size + 1
        if (prevStart <= 0) {
            return "-1"
        }
        ans = ans.zip(prevStart .. min).flatMap { (a, b) -> listOf(a, b) }.dropLast(1)
    }
    ans = (1 until ans.min()) + ans
    return ans.joinToString(" ")
}
fun main() {
    repeat(readInt()) {
        println(solve())
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }