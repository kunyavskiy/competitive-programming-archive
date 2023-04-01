private fun solve() {
    val q = readInt()

    // f(a, b) = n ->
    // 1. (a - b) * (n - 2) + a < h
    // 2. (a - b) * (n - 1) + a >= h

    var l = 0L
    var r = Long.MAX_VALUE

    val ans = LongArray(q)

    repeat(q) {
        val d = readLongs()
        val (t, a, b) = d
        val min = (maxOf(l - a, 0) + a - b - 1) / (a - b) + 1
        val max = (maxOf(r - a, 0) + a - b - 1) / (a - b) + 1
        //println("$a $b -> $min..$max")
        ans[it] = if (t == 2L) {
            if (min == max) min else -1
        } else {
            val n = d[3]
            if (n in min..max) {
                if (n != 1L) {
                    l = maxOf(l, (a - b) * (n - 2) + a + 1)
                }
                r = minOf(r, (a - b) * (n - 1) + a)
                1
            } else {
                0
            }
        }
    }
    println(ans.joinToString(" "))
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