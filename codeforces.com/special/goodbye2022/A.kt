private fun solve() {
    val (n, m) = readInts()
    val a = readLongs()
    val b = readLongs()

    println(b.last() + (a + b.dropLast(1)).sorted().takeLast(n - 1).sum())
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