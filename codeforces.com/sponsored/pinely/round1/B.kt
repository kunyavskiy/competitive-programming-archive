private fun solve() {
    val n = readInt()
    val a = readInts()
    if (a.distinct().size > 2) {
        println(n)
    } else {
        println(n / 2 + 1)
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