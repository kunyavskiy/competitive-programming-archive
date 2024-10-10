private fun solve() {
    val data = List(readInt()) { readInts() }
    val lf = data.withIndex().maxOf { (it.index + 1).toDouble() / it.value[1] }
    val rg = data.withIndex().minOf { (it.index + 1).toDouble() / it.value[0] }
    println(if (lf > rg) {
        -1
    } else {
        "%.10f".format(lf)
    })
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