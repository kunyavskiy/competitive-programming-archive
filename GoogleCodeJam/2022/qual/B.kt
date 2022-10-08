private fun solve() {
    val l1 = readInts().toIntArray()
    val l2 = readInts().toIntArray()
    val l3 = readInts().toIntArray()
    val mins = IntArray(l1.size) { minOf(l1[it], l2[it], l3[it]) }
    var total = 1000000
    if (mins.sum() < total) {
        println("IMPOSSIBLE")
        return
    }
    for (i in mins.indices) {
        mins[i] = minOf(mins[i], total)
        total -= mins[i]
    }
    println(mins.joinToString(" "))
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }