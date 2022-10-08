private fun solve() : Boolean {
    val (n, kk) = readInts()
    val k = if (n == 2) kk % 2 else kk
    val a = readInts()
    val b = readInts()
    val c = (a + listOf(-1) + b + b).toIntArray()

    val p = IntArray(c.size) { -1 }

    p[0] = 0

    for (i in 1 until p.size) {
        var j = p[i - 1]
        while (j != 0 && c[j] != c[i]) {
            j = p[j - 1]
        }
        if (c[j] == c[i]) j++
        p[i] = j
    }
    return when (k) {
        0 -> p[2 * n] == n
        1 -> p.drop(2 * n + 1).dropLast(1).any { it == n }
        else -> p.any { it == n }
    }
}

fun main() {
    repeat(readInt()) {
        println("Case #${it + 1}: " + if (solve()) "YES" else "NO")
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }