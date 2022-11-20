private fun solve() {
    val n = readInt()
    val a = List(n) { readLn() }
    for (i in 0 until n) {
        val lst = (0 until n).filter { it == i || a[it][i] == '1' }.map { it + 1 }
        println("${lst.size} ${lst.joinToString(" ")}")
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