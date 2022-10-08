private fun solve() {
    val (r, c) = readInts()
    println(List(r * 2+1) { i ->
        List(c * 2+1) { j ->
            when {
                i < 2 && j < 2 -> '.'
                i % 2 == 0 && j % 2 == 0 -> '+'
                i % 2 == 0 -> '-'
                j % 2 == 0 -> '|'
                else -> '.'
            }
        }.joinToString("")
    }.joinToString("\n"))
}

fun main() {
    repeat(readInt()) {
        println("Case #${it + 1}:")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }