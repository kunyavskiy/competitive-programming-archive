private fun solve() {
    val n = readInt()
    val a = readInts().reversed()
    val b = readInts().reversed()
    var ptr = 0
    println(n - (0..a.size).first {
        while (ptr < n && b.getOrNull(it) != a[ptr]) ptr++
        ptr == n
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