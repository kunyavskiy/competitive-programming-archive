private fun solve() {
    readInt()
    val pos = readInts().sorted()
    val ans = if (pos.size == 5) {
        maxOf(
            (pos[4] + pos[3]) - (pos[2] + pos[0]),
            (pos[4] + pos[2]) - (pos[1] + pos[0]),
        )
    } else {
        pos.takeLast(2).sum() - pos.take(2).sum()
    }
    println("%.1f".format(ans / 2.0))
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