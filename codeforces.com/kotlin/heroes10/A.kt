fun main() {
    val ans = IntArray(101) { Int.MAX_VALUE }
    ans[0] = 0
    for (i in ans.indices) {
        for ((d, c) in listOf(1 to 1, 3 to 0, 5 to 0)) {
            if (i + d in ans.indices) ans[i + d] = minOf(ans[i + d], ans[i] + c)
        }
    }
    repeat(readInt()) {
        println(ans[readInt()])
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }