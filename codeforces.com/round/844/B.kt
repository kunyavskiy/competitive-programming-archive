private fun solve() {
    val n = readInt()
    val a = readInts().sorted().toIntArray()
    println((0..n).count {
        (it == 0 || a[it - 1] < it) && (it == n || a[it] > it)
    })
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