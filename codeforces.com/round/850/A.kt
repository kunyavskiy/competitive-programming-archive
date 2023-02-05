private fun solve() {
    readInt()
    val a = readInts()
    var ans = 0L
    var cur = 1L
    for (i in a.sorted()) {
        if (i >= cur) {
            ans += i - cur
            cur++
        }
    }
    println(ans)
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