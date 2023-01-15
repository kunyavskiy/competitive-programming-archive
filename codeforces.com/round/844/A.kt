import kotlin.math.*

private fun solve() {
    val (w, d, h) = readInts()
    val (a, b, f, g) = readInts()
    println(h +
    listOf(
        a + f + abs(b - g),
        2 * w - a - f + abs(b - g),
        abs(a - f) + b + g,
        abs(a - f) + 2 * d - b - g
    ).min())
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }