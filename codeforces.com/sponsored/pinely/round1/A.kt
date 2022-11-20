private fun solve() {
    val (n, a, b) = readInts()
    if (a + b >= n - 1 && (a != n || b != n)) {
        println("No")
    } else {
        println("Yes")
    }
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