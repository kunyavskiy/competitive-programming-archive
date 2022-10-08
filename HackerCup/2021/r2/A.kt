import kotlin.math.*

private fun solve() {
    val (n_, m) = readInts()
    val n = n_ + 1
    val P = List(n) { readInts().withIndex().groupBy({ it.value }, { it.index }).mapValues { it.value.size }.toMutableMap() }
    val totalChanges = P.zipWithNext().sumOf {
        ((it.first.keys.toList() + it.second.keys.toList()).distinct().map { type ->
            abs(it.first.getOrDefault(type, 0) - it.second.getOrDefault(type, 0))
        }.sumOf { it.toLong()  } / 2L)
    }
    val zeroChanges = P[0].keys.sumOf { type ->
        var unchanged = P[0][type]!!
        for (cur in P.zipWithNext()) {
            val change = cur.first.getOrDefault(type, 0) - cur.second.getOrDefault(type, 0)
            if (change > 0) {
                unchanged -= change
            }
        }
        maxOf(unchanged, 0)
    }
    println(totalChanges - m + zeroChanges)
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