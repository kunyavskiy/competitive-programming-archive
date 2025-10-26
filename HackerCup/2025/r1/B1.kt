private fun solve() {
    val (n, a, b) = readInts()
    println((List(2*n-1) { 1 } + listOf(b)).joinToString(" "))
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }