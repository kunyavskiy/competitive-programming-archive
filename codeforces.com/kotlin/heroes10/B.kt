fun main() {
    repeat(readInt()) {
        val (k, m) = readInts()
        println(maxOf(0, 2 * k - (m % (3 * k))))
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }