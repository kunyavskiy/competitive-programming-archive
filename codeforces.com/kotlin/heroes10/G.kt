import kotlin.math.abs
import kotlin.math.sign

fun main() {
    readInts()
    val x = readInts()
    val h = readInts()
    val ord = buildList {
        for (i in x.indices.sortedBy { x[it] }) {
            while (isNotEmpty() && h[i] - h[last()] >= x[i] - x[last()]) {
                removeLast()
            }
            if (isEmpty() || h[last()] - h[i] <= x[i] - x[last()]) {
                add(i)
            }
        }
    }.map { x[it] to h[it] }

    fun nextAfter(pos: Int) = ord.binarySearch { (x, _) -> if (x >= pos) 1 else -1 }.inv()
    fun coverBy(idx: Int, pos: Int) = ord.getOrNull(idx)?.let { (x, h) -> maxOf(0, abs(x - pos) - h) } ?: Int.MAX_VALUE
    fun cover(pos: Int): Int {
        val a = nextAfter(pos)
        return minOf(coverBy(a - 1, pos), coverBy(a, pos))
    }

    fun cover2(l: Int, r: Int): Int {
        val a = nextAfter((l + r) / 2)
        return minOf(maxOf(coverBy(a, l), coverBy(a, r)), maxOf(coverBy(a - 1, l), coverBy(a - 1, r)))
    }

    val ans = List(readInt()) {
        val (l, r) = readInts()
        minOf(
            cover(l) + cover(r),
            cover2(l, r)
        )
    }
    println(ans.joinToString(" "))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }