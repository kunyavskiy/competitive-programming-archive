private fun solve() {
    val s = readLn().map { it.code - 'A'.code }
    val INF = Int.MAX_VALUE / 2
    val ALPHA = 26
    val a = Array(ALPHA) { i ->
        Array(ALPHA) { j ->
            if (i == j) 0 else INF
        }
    }
    repeat(readInt()) {
        val (c1, c2) = readLn().toCharArray()
        a[c1 - 'A'][c2 - 'A'] = 1
    }
    for (k in 0 until ALPHA) {
        for (i in 0 until ALPHA) {
            for (j in 0 until ALPHA) {
                a[i][j] = minOf(a[i][j], a[i][k] + a[k][j])
            }
        }
    }

    val ans = (0 until ALPHA)
        .filter { d -> s.none { a[it][d] >= INF } }
        .minOfOrNull { d -> s.sumOf { a[it][d] } }
        ?: -1
    println(ans)
}

private fun Char.isVowel() = "AEIOU".contains(this)


fun main() {
    repeat (readInt()) {
        print("Case #${it+1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }