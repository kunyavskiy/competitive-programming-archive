fun best(a: List<Int>, k: Int): Long {
    val r = LongArray(4)
    var sum = 0L
    for (v in a) {
        sum += v
        r[0] = maxOf(r[0], -sum)
        r[1] = maxOf(r[1], r[0] + sum)
        r[2] = maxOf(r[2], r[1] - sum)
        r[3] = maxOf(r[3], r[2] + sum)
    }
    return r[2 * k - 1]
}

fun main() {
    repeat(readInt()) {
        readInt()
        val a = readInts()
        val b = readInts()
        val mins = a.zip(b).map { minOf(it.first, it.second) }
        val maxs = a.zip(b).map { maxOf(it.first, it.second) }
        println(maxOf(best(mins, 1) + best(maxs, 1), best(maxs, 2)))
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }