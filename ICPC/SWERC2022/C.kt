fun main() {
    val n = readInt()
    val s = readLn()
    println((n until s.length).runningFold(
        s.substring(0, n).count { it == 'W' }
    ) { acc, i ->
        acc + (if (s[i] == 'W') 1 else 0) - (if (s[i - n] == 'W') 1 else 0)
    }.maxOrNull()!!)
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }