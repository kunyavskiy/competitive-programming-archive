private fun getDistances(n: Int) : LongArray {
    val p = readInts().map { it - 1 }
    val sizes = IntArray(n) { 1 }
    for (i in 0 until n - 1) {
        sizes[p[i]] += sizes[i]
    }
    val d = LongArray(n) { 0 }
    d[n - 1] = sizes.sumOf { it.toLong() } - n.toLong()
    for (i in n - 2 downTo 0) {
        d[i] = d[p[i]] - sizes[i] + (n - sizes[i])
    }
    return d
}

private fun solve() {
    val (w, e, c) = readInts()
    val d1 = getDistances(w)
    val d2 = getDistances(e)
    val ans = d1.sum() + d2.sum()
    val opts = (w + e).toLong() * (w + e - 1).toLong()
    val result = List(c) {
        val (u, v) = readInts()
        val s = ans + 2 * d1[u - 1] * e + 2 * d2[v - 1] * w + 2 * w.toLong() * e.toLong()
        s.toDouble() / opts
    }
    println(result.joinToString(" ") { "%.10f".format(it) })
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }