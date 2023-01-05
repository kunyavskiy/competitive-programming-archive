private fun solve() : Boolean {
    val n = readInt()
    val a = readLongs()
    if (a.distinct().size != a.size) return false

    for (i in 2..n) {
        val counts = a.groupingBy { it % i }.eachCount()
        if (counts.size == i && counts.minOf { it.value } >= 2) return false
    }
    return true
}

fun main() {
    repeat(readInt()) {
        if (solve()) println("YES") else println("NO")
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }