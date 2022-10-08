private fun solveOne(a: List<Int>) : Long? {
    val s = a.sum().toLong()
    val imb = a.sumOf { it.toLong() * it.toLong() } - s * s
    return when {
        s == 0L && imb != 0L -> null
        s == 0L && imb == 0L -> 0
        imb % (2 * s) == 0L -> imb / (2 * s)
        else -> null
    }
}

private fun solve() {
    val (_, k) = readInts()
    val a = readInts()
    val ans = if (k == 1) {
        solveOne(a)?.let { listOf(it) }
    } else {
        val add = 1 - a.sum()
        solveOne(a + add)?.let { listOf(it, add.toLong()) }
    }
    if (ans == null) {
        println("IMPOSSIBLE")
    } else {
        println(ans.joinToString(" "))
    }
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