private fun solve() {
    val (n, k, d, w) = readInts()
    val t = readInts()
    var iters = 0
    var ptr = 0
    while (ptr < n) {
        iters++
        val upto = t[ptr] + d + w
        val start = ptr
        while (ptr < n && ptr < start + k && t[ptr] <= upto) {
            ptr++
        }
    }
    println(iters)
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