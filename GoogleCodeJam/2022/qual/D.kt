private fun solve() {
    val n = readInt()
    val f = (listOf(0) + readInts()).toIntArray()
    val p = (listOf(-1) + readInts()).toIntArray()
    val g = p.indices.groupBy { p[it] }
    val d1 = LongArray(n+1) { 0 }
    val d2 = LongArray(n+1) { 0 }
    for (i in n downTo 0) {
        val sons = g[i] ?: emptyList()
        val sum = sons.sumOf { d1[it] }
        val min = sons.minOfOrNull { d1[it] - d2[it] } ?: 0
        d1[i] = sum + maxOf(0, f[i] - min)
        d2[i] = sum - min
    }
    println(d1[0])
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