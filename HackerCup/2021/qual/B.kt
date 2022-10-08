private fun solve() {
    val n = readInt()
    val a = Array(n) { readLn() }
    val hwins = (0 until n)
        .filter { x -> (0 until n).none { a[x][it] == 'O' } }
        .map { x -> (0 until n).count { a[x][it] == '.' } }
    val vwins = (0 until n)
        .filter { y -> (0 until n).none { a[it][y] == 'O' } }
        .map { y -> (0 until n).count { a[it][y] == '.' } }
    val wins = hwins + vwins
    val min = wins.minOrNull() ?: return println("Impossible")
    val duplicate = if (min != 1) {
        0
    } else {
        (0 until n)
            .filter { x -> (0 until n).none { a[x][it] == 'O' } }
            .mapNotNull { x -> (0 until n).singleOrNull { a[x][it] == '.' }?.let { x to it } }
            .filter { (x, y) -> (0 until n).none { a[it][y] == 'O' } }
            .count { (x, y) -> (0 until n).singleOrNull { a[it][y] == '.' } == x }
    }
    println("$min ${wins.count { it == min } - duplicate}")
}

fun main() {
    repeat (readInt()) {
        print("Case #${it+1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }