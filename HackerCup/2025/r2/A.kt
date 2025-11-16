private fun solve() : Boolean {
    val (n, m) = readLongs()
    if (n < m) return false
    // x  m, x <= m - 2
    if (n <= 2 * m - 2) return true
    return n % 2 == 0L
}

fun main() {
    repeat(readInt()) {
        println("Case #${it + 1}: ${if (solve()) "YES" else "NO"}")
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }