private fun solve() {
    val (n, x, p) = readLongs()
    for (i in 1L .. minOf(3 * n, p)) {
        if ((x + i * (i + 1) / 2) % n == 0L) {
            println("YES")
            return
        }
    }
    println("NO")
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }