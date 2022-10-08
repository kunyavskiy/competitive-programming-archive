private fun solve() {
    val (n, k) = readInts()
    val s = readInts()
    val result = when {
        2 * k < n -> "NO"
        s.groupingBy { it }.eachCount().values.any { it > 2 } -> "NO"
        else -> "YES"
    }
    println(result)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }