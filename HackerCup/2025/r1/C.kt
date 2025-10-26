private fun solve() {
    val n = readInt()
    val a = readInts()
        .runningFold(0, Int::xor)
        .groupBy { it }
    var ans = (1..n).sumOf { it * 1L * (n - it + 1)}
    for ((_, pos) in a) {
        ans -= (1..pos.size).sumOf { it * 1L * (pos.size - it)}
    }
    println(ans)
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