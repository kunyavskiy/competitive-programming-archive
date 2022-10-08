
private fun solve() {
    val (n, m, a, b) = readInts()
    val ret = Array(n) { x ->
        Array(m) { y ->
            when {
                x == 0 && y == 0     -> a - (n + m - 2)
                x == 0 && y == m - 1 -> b - (n + m - 2)
                else                 -> 1
            }.takeIf { it > 0 } ?: return println("Impossible")
        }
    }
    println("Possible")
    println(ret.joinToString("\n") { it.joinToString(" ") })
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