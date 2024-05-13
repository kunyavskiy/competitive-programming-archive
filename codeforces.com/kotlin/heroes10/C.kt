fun main() {
    repeat(readInt()) {
        val (n, k) = readLongs()
        println(n - k.countTrailingZeroBits())
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }