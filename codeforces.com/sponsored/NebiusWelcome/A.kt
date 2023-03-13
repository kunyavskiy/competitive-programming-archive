import kotlin.math.*

private fun solve() {
    val (a, b) = readInts().map { abs(it) }
    println(2 * maxOf(a, b) - (if (a != b) 1 else 0))
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