private val ans = mutableMapOf<Int, List<Int>>()
private fun precalc(s: Int, l: List<Int>, prod: Int, lim: Int) {
    if (s == 0) {
        if ((ans[prod]?.size ?: Int.MAX_VALUE) > l.size) {
            ans[prod] = l
        }
        return
    }
    if (s < lim || prod > 1_000_000_000 / lim) return
    precalc(s, l, prod, lim + 1)
    precalc(s - lim, l + lim, prod * lim, lim)
}

private fun solve() {
    val p = readInt()
    println(ans[p]?.let { "${it.size} ${it.joinToString(" ")}" } ?: "-1")
}

fun main() {
    precalc(41, emptyList(), 1, 1)
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }