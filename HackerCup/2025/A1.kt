import kotlin.math.absoluteValue

private fun solve() {
    readln()
    val a = readLongs()
    println(a.zipWithNext { x, y -> (y - x).absoluteValue }.maxOrNull() ?: 0L)
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