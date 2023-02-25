private fun solve() {
    readInt()
    val a = (readInts() + listOf(0, 1440)).sorted()
    val r = a.zipWithNext().sumOf { (l, r) -> (r - l) / 120 }
    if (r >= 2) println("YES") else println("NO")
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