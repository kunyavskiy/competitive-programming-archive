private fun solve() {
    val n = readInt()
    val s = readLn()
    val one = s[0]
    val zero = if (s[0] == '.') '-' else '.'
    repeat(n - 1) {
        println(it.toString(2).padStart(10, '0').replace('0', zero).replace('1', one))
    }
}

fun main() {
    repeat(readInt()) {
        println("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }