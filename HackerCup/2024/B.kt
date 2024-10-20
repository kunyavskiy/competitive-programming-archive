private fun solve() {
    readln()
    val a = Array(6) { readln() }
    val dirs = listOf(1 to 0, 0 to 1, 1 to 1, 1 to -1)
    fun wins(c: Char) = buildList {
        for (i in a.indices) {
            for (j in a[i].indices) {
                for ((dx, dy) in dirs) {
                    val cand = (0 until 4).map { i + dx * it to j + dy * it }
                    if (cand.all { a.getOrNull(it.first)?.getOrNull(it.second) == c }) {
                        add(cand)
                    }
                }
            }
        }
    }
    fun earlier(a: List<Pair<Int, Int>>, b: List<Pair<Int, Int>>) : Boolean {
        return a.all { (xa, ya) -> b.any { (xb, yb) -> xa > xb && ya == yb} }
    }
    val F = wins('F')
    val S = wins('C')
    println(when {
        F.isEmpty() && S.isEmpty() -> "0"
        F.all { f -> S.any { s -> earlier(s, f) }} -> "C"
        S.all { s -> F.any { f -> earlier(f, s) }} -> "F"
        else -> "?"
    })
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }